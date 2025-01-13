#pragma once
#include "pch.h"
#pragma once
#pragma comment(lib, "ntdll")

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;

enum class SystemInformationClass {
    SystemPoolTagInformation = 22,
};

struct SYSTEM_POOLTAG {
    union {
        UCHAR Tag[4];
        ULONG TagUlong;
    };
    ULONG PagedAllocs;
    ULONG PagedFrees;
    SIZE_T PagedUsed;
    ULONG NonPagedAllocs;
    ULONG NonPagedFrees;
    SIZE_T NonPagedUsed;
};

struct SYSTEM_POOLTAG_INFORMATION {
    ULONG Count;
    SYSTEM_POOLTAG TagInfo[1];
};

extern "C"
NTSTATUS NTAPI NtQuerySystemInformation(
    _In_ SystemInformationClass SystemInformationClass,
    _Out_writes_bytes_to_opt_(SystemInformationLength, *ReturnLength) PVOID SystemInformation,
    _In_ ULONG SystemInformationLength,
    _Out_opt_ PULONG ReturnLength
);

struct TagItems {
    SYSTEM_POOLTAG TagInfo;
    std::wstring SourceName;
    std::string Tag;
    int Index;
};

std::unordered_map<std::string, std::pair<std::wstring, std::wstring>> TagSource;
std::vector<std::shared_ptr<TagItems>> Tags;
std::unordered_map<ULONG, std::shared_ptr<TagItems>> TagsMap;
size_t TotalPaged = 0, TotalNonPaged = 0;
SYSTEM_POOLTAG_INFORMATION* m_PoolTags{ nullptr };

System::String^ ConvertStringToString(const std::string& str)
{
    return gcnew System::String(str.c_str());
}

System::String^ ConvertWStringToString(const std::wstring& wstr) {
    return gcnew System::String(wstr.c_str());
}


void AddTag(const SYSTEM_POOLTAG & info, int index) {
    char tag[5] = { 0 };
    ::CopyMemory(tag, &info.Tag, 4);
    auto item = std::make_shared<TagItems>();
    item->Tag = std::string(tag);

    item->TagInfo = info;
    item->Index = index;

    auto it = TagSource.find(item->Tag);
    if (it != TagSource.end()) {
        item->SourceName = it->second.first;
    }

    Tags.push_back(item);
    TagsMap.insert({ info.TagUlong, item });
}

void LoadTags() {
    std::ifstream inFile("tags.txt");

    if (!inFile.is_open()) {
        std::cerr << "Не вдалося знайти файл" << std::endl;
        return;
    }

    inFile.seekg(0, std::ios::end);
    std::streamsize fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    if (fileSize <= 0) {
        std::cerr << "Файл порожній" << std::endl;
        return;
    }

    std::vector<char> buffer(fileSize + 1);
    inFile.read(buffer.data(), fileSize);
    buffer[fileSize] = '\0';
    inFile.close();

    const char* data = buffer.data();
    const char* next = strchr(data, '\n');

    while (next) {
        if (strncmp(data, "//", 2) == 0 || _strnicmp(data, "rem", 3) == 0 ||
            strncmp(data, "\r\n", 2) == 0 || strncmp(data, "\n", 1) == 0) {
            data = next + 1;
            next = strchr(data, '\n');
            continue;
        }

        std::string tag(data, 4);
        auto dash1 = strchr(data, '-');
        if (!dash1) {
            data = next + 1;
            next = strchr(data, '\n');
            continue;
        }

        auto dash2 = strchr(dash1 + 1, '-');
        if (!dash2 || dash2 > next) {
            data = next + 1;
            next = strchr(data, '\n');
            continue;
        }

        std::string driverName(dash1 + 1, dash2);
        driverName.erase(driverName.find_last_not_of(" \n\r\t") + 1);
        std::wstring trimmedDriverName(driverName.begin(), driverName.end());

        std::string driverDesc(dash2 + 1, next);
        driverDesc.erase(driverDesc.find_last_not_of(" \n\r\t") + 1);
        std::wstring trimmedDriverDesc(driverDesc.begin(), driverDesc.end());

        TagSource.emplace(tag, std::make_pair(trimmedDriverName, trimmedDriverDesc));

        data = next + 1;
        next = strchr(data, '\n');
    }
}

void UpdateTags() {
    ULONG size = 1 << 22;  

    if (m_PoolTags == nullptr) {
        LoadTags();

        try {
           
            std::cout << "Спроба виділити " << size << "байт пам'яті для PoolTags." << std::endl;

            
            m_PoolTags = static_cast<SYSTEM_POOLTAG_INFORMATION*>(::VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
            
           
            if (m_PoolTags == nullptr) {
                std::cout << "Не вдалося виділити пам'ять для PoolTags" << std::endl;
                PostQuitMessage(1);  
                return;
            }
        }
        catch (const std::exception& e) {
           
            std::cout << "Сталася помилка під час виділення пам'яті: " << e.what() << std::endl;
            PostQuitMessage(1);  
            return;
        }
    }

    ULONG len;
    auto status = NtQuerySystemInformation(SystemInformationClass::SystemPoolTagInformation, m_PoolTags, size, &len);

    if (status) {
        std::cout << "Не вдалося отримати інформацію про систему" << std::endl;
        PostQuitMessage(1);  
        return;
    }

    
    auto count = m_PoolTags->Count;
    if (Tags.empty()) {
        Tags.reserve(count + 16);
        TagsMap.reserve(count + 16);

        for (decltype(count) i = 0; i < count; i++) {
            const auto& info = m_PoolTags->TagInfo[i];
            TotalPaged += info.PagedUsed;
            TotalNonPaged += info.NonPagedUsed;
            AddTag(info, i);
        }
    }
    else {
        int size = static_cast<int>(Tags.size());
        std::unordered_set<int> set;
        for (int i = 0; i < size; i++)
            set.insert(i);

        TotalPaged = TotalNonPaged = 0;
        for (decltype(count) i = 0; i < count; i++) {
            const auto& info = m_PoolTags->TagInfo[i];

            TotalPaged += info.PagedUsed;
            TotalNonPaged += info.NonPagedUsed;

            auto it = TagsMap.find(info.TagUlong);
            if (it == TagsMap.end()) {
                AddTag(info, i);
                count++;
            }
            else {
                auto& newinfo = it->second->TagInfo;

                it->second->TagInfo = info;
                it->second->Index = i;
                set.erase(i);
            }
        }

        int bias = 0;
        for (auto index : set) {
            int i = index - bias;
            count--;
            TagsMap.erase(Tags[i]->TagInfo.TagUlong);
            Tags.erase(Tags.begin() + i);
            bias++;
        }
    }
}

