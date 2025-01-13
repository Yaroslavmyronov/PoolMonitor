#pragma once
#include "Funcs.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			
		}
	protected:
		
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ listView;
	protected:

	protected:
	private: System::Windows::Forms::ColumnHeader^ TagCol;
	private: System::Windows::Forms::ColumnHeader^ nameCol;
	private: System::Windows::Forms::ColumnHeader^ npa;
	private: System::Windows::Forms::ColumnHeader^ npf;
	private: System::Windows::Forms::ColumnHeader^ npd;
	private: System::Windows::Forms::ColumnHeader^ pa;
	private: System::Windows::Forms::ColumnHeader^ pf;
	private: System::Windows::Forms::ColumnHeader^ pd;
	private: System::Windows::Forms::Button^ updateBtn;
	private: System::Windows::Forms::Button^ aboutBtn;

	private:
		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->listView = (gcnew System::Windows::Forms::ListView());
			this->TagCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->nameCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->npa = (gcnew System::Windows::Forms::ColumnHeader());
			this->npf = (gcnew System::Windows::Forms::ColumnHeader());
			this->npd = (gcnew System::Windows::Forms::ColumnHeader());
			this->pa = (gcnew System::Windows::Forms::ColumnHeader());
			this->pf = (gcnew System::Windows::Forms::ColumnHeader());
			this->pd = (gcnew System::Windows::Forms::ColumnHeader());
			this->updateBtn = (gcnew System::Windows::Forms::Button());
			this->aboutBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			this->listView->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->listView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(8) {
				this->TagCol, this->nameCol,
					this->npa, this->npf, this->npd, this->pa, this->pf, this->pd
			});
			this->listView->ForeColor = System::Drawing::Color::White;
			this->listView->HideSelection = false;
			this->listView->Location = System::Drawing::Point(11, 46);
			this->listView->Margin = System::Windows::Forms::Padding(2);
			this->listView->Name = L"listView";
			this->listView->Size = System::Drawing::Size(1028, 437);
			this->listView->TabIndex = 0;
			this->listView->UseCompatibleStateImageBehavior = false;
			this->listView->View = System::Windows::Forms::View::Details;
			this->listView->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listView_SelectedIndexChanged);
			
			System::Drawing::Font^ headerFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point);
			this->TagCol->Text = L"Tег";
			
			this->nameCol->Text = L"Ім'я джерела";
			this->nameCol->Width = 105;
			
			this->npa->Text = L"Не пагіновані виділення";
			this->npa->Width = 140;
			
			this->npf->Text = L"Не пагіновані звільнення";
			this->npf->Width = 140;
			
			this->npd->Text = L"Не пагінована різниця";
			this->npd->Width = 140;
			
			this->pa->Text = L"Пагіновані виділення";
			this->pa->Width = 140;
			
			this->pf->Text = L"Пагіновані звільнення";
			this->pf->Width = 140;
			
			this->pd->Text = L"Пагінована різниця";
			this->pd->Width = 146;
			
			this->updateBtn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->updateBtn->FlatAppearance->BorderSize = 0;
			this->updateBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->updateBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->updateBtn->ForeColor = System::Drawing::Color::White;
			this->updateBtn->Location = System::Drawing::Point(919, 3);
			this->updateBtn->Margin = System::Windows::Forms::Padding(2);
			this->updateBtn->Name = L"updateBtn";
			this->updateBtn->Size = System::Drawing::Size(120, 39);
			this->updateBtn->TabIndex = 1;
			this->updateBtn->Text = L"Update";
			this->updateBtn->UseVisualStyleBackColor = false;
			this->updateBtn->Click += gcnew System::EventHandler(this, &Form1::updateBtn_Click);
			
			this->aboutBtn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->aboutBtn->FlatAppearance->BorderSize = 0;
			this->aboutBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->aboutBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->aboutBtn->ForeColor = System::Drawing::Color::White;
			this->aboutBtn->Location = System::Drawing::Point(795, 3);
			this->aboutBtn->Margin = System::Windows::Forms::Padding(2);
			this->aboutBtn->Name = L"aboutBtn";
			this->aboutBtn->Size = System::Drawing::Size(120, 39);
			this->aboutBtn->TabIndex = 2;
			this->aboutBtn->Text = L"About Me";
			this->aboutBtn->UseVisualStyleBackColor = false;
			this->aboutBtn->Click += gcnew System::EventHandler(this, &Form1::aboutBtn_Click);
			
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(25)));
			this->ClientSize = System::Drawing::Size(1048, 494);
			this->Controls->Add(this->aboutBtn);
			this->Controls->Add(this->updateBtn);
			this->Controls->Add(this->listView);
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximumSize = System::Drawing::Size(1064, 533);
			this->MinimumSize = System::Drawing::Size(1064, 533);
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"Monitor";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}

		void CreateViewList()
		{
			for (int i = 0; i < Tags.size(); i++)
			{
				auto& info = *Tags[i];
				System::String^ result = ConvertStringToString(info.Tag);
				System::String^ alloc = System::UInt32(info.TagInfo.PagedAllocs).ToString();
				System::String^ frees = System::UInt32(info.TagInfo.PagedFrees).ToString();
				System::String^ diff = System::UInt32(info.TagInfo.PagedAllocs - info.TagInfo.PagedFrees).ToString();
				System::String^ nAlloc = System::UInt32(info.TagInfo.NonPagedAllocs).ToString();
				System::String^ nFrees = System::UInt32(info.TagInfo.NonPagedFrees).ToString();
				System::String^ nDiff = System::UInt32(info.TagInfo.NonPagedAllocs - info.TagInfo.NonPagedFrees).ToString();
				System::String^ name = ConvertWStringToString(info.SourceName);


				ListViewItem^ item = gcnew ListViewItem(result);
				item->SubItems->Add(name);
				item->SubItems->Add(nAlloc);
				item->SubItems->Add(nFrees);
				item->SubItems->Add(nDiff);
				item->SubItems->Add(alloc);
				item->SubItems->Add(frees);
				item->SubItems->Add(diff);
				listView->Items->Add(item);
			}
		}

		void UpdateViewList()
		{
			for (int i = 0; i < listView->Items->Count; i++)
			{
				auto& info = *Tags[i];
				listView->Items[i]->SubItems[0]->Text = ConvertStringToString(info.Tag);
				listView->Items[i]->SubItems[1]->Text = ConvertWStringToString(info.SourceName);
				listView->Items[i]->SubItems[2]->Text = System::UInt32(info.TagInfo.NonPagedAllocs).ToString();
				listView->Items[i]->SubItems[3]->Text = System::UInt32(info.TagInfo.NonPagedFrees).ToString();
				listView->Items[i]->SubItems[4]->Text = System::UInt32(info.TagInfo.NonPagedAllocs - info.TagInfo.NonPagedFrees).ToString();
				listView->Items[i]->SubItems[5]->Text = System::UInt32(info.TagInfo.PagedAllocs).ToString();
				listView->Items[i]->SubItems[6]->Text = System::UInt32(info.TagInfo.PagedFrees).ToString();
				listView->Items[i]->SubItems[7]->Text = System::UInt32(info.TagInfo.PagedAllocs - info.TagInfo.PagedFrees).ToString();
				
			}
		}

#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		LoadTags();
		UpdateTags();
		CreateViewList();
	}
	private: System::Void updateBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		UpdateTags();
		UpdateViewList();
	}
	private: System::Void aboutBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("KIYKIY-23-2\nМиронов Я.В\nФронтенд розробник\nНавчаюся в ХНУРЕ", "Про мене");
	}
private: System::Void listView_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
