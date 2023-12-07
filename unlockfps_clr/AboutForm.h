#pragma once

namespace unlockfpsclr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AboutForm
	/// </summary>
	public ref class AboutForm : public Form
	{
	public:
		AboutForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AboutForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelTitle;
	private: System::Windows::Forms::LinkLabel^ linkLabelDescription;
	private: System::Windows::Forms::LinkLabel^ linkLabelSource;
	private: System::Windows::Forms::LinkLabel^ linkLabelIssues;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labelTitle = (gcnew System::Windows::Forms::Label());
			this->linkLabelDescription = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelSource = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabelIssues = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// labelTitle
			// 
			this->labelTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->labelTitle->Location = System::Drawing::Point(12, 9);
			this->labelTitle->Name = L"labelTitle";
			this->labelTitle->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
			this->labelTitle->Size = System::Drawing::Size(300, 36);
			this->labelTitle->TabIndex = 0;
			this->labelTitle->Text = L"Genshin FPS Unlocker\r\nv2.1.3\r\n";
			this->labelTitle->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// linkLabelDescription
			// 
			this->linkLabelDescription->LinkArea = System::Windows::Forms::LinkArea(92, 6);
			this->linkLabelDescription->Location = System::Drawing::Point(12, 45);
			this->linkLabelDescription->Name = L"linkLabelDescription";
			this->linkLabelDescription->Size = System::Drawing::Size(300, 20);
			this->linkLabelDescription->TabIndex = 1;
			this->linkLabelDescription->Text = L"This program is free and open source";
			this->linkLabelDescription->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->linkLabelDescription->UseCompatibleTextRendering = true;
			// 
			// linkLabelSource
			// 
			this->linkLabelSource->LinkArea = System::Windows::Forms::LinkArea(8, 46);
			this->linkLabelSource->Location = System::Drawing::Point(12, 65);
			this->linkLabelSource->Name = L"linkLabelSource";
			this->linkLabelSource->Size = System::Drawing::Size(300, 20);
			this->linkLabelSource->TabIndex = 2;
			this->linkLabelSource->TabStop = true;
			this->linkLabelSource->Text = L"Source: https://github.com/34736384/genshin-fps-unlock";
			this->linkLabelSource->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->linkLabelSource->UseCompatibleTextRendering = true;
			this->linkLabelSource->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutForm::linkLabelSource_LinkClicked);
			// 
			// linkLabelIssues
			// 
			this->linkLabelIssues->LinkArea = System::Windows::Forms::LinkArea(87, 53);
			this->linkLabelIssues->Location = System::Drawing::Point(12, 105);
			this->linkLabelIssues->Name = L"linkLabelIssues";
			this->linkLabelIssues->Size = System::Drawing::Size(300, 47);
			this->linkLabelIssues->TabIndex = 3;
			this->linkLabelIssues->TabStop = true;
			this->linkLabelIssues->Text = L"If you encounter any problems or have a suggestion\r\nGo ahead and submit an issue "
				L"at\r\n\r\nhttps://github.com/34736384/genshin-fps-unlock/issues";
			this->linkLabelIssues->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->linkLabelIssues->UseCompatibleTextRendering = true;
			this->linkLabelIssues->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutForm::linkLabelIssues_LinkClicked);
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(324, 171);
			this->Controls->Add(this->linkLabelIssues);
			this->Controls->Add(this->linkLabelSource);
			this->Controls->Add(this->linkLabelDescription);
			this->Controls->Add(this->labelTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"AboutForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"About";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: Void linkLabelSource_LinkClicked(Object^ sender, LinkLabelLinkClickedEventArgs^ e);
	private: Void linkLabelIssues_LinkClicked(Object^ sender, LinkLabelLinkClickedEventArgs^ e);
	};
}
