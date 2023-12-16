#pragma once
#include "Settings.h"
#include "Managed.h"

namespace unlockfpsclr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SetupForm
	/// </summary>
	public ref class SetupForm : public Form
	{
	public:
		SetupForm(Settings^ settings)
		{
			InitializeComponent();

			this->settings = settings;
			this->FormClosing += gcnew FormClosingEventHandler(this, &SetupForm::OnFormClosing);
			this->Load += gcnew EventHandler(this, &SetupForm::OnLoad);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SetupForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Settings^ settings;
	private: BackgroundWorker^ backgroundWorker;
	private: System::Windows::Forms::Label^ labelResult;
	private: System::Windows::Forms::Label^ labelSelectInstance;
	private: System::Windows::Forms::ComboBox^ comboBoxSelectInst;
	private: System::Windows::Forms::Button^ btnBrowse;

	private: System::Windows::Forms::ToolTip^ ttPath;
	private: System::Windows::Forms::Button^ btnConfirm;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->labelResult = (gcnew System::Windows::Forms::Label());
			this->labelSelectInstance = (gcnew System::Windows::Forms::Label());
			this->comboBoxSelectInst = (gcnew System::Windows::Forms::ComboBox());
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->ttPath = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->btnConfirm = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labelResult
			// 
			this->labelResult->AutoSize = true;
			this->labelResult->ForeColor = System::Drawing::SystemColors::ControlText;
			this->labelResult->Location = System::Drawing::Point(13, 13);
			this->labelResult->Name = L"labelResult";
			this->labelResult->Size = System::Drawing::Size(59, 13);
			this->labelResult->TabIndex = 0;
			this->labelResult->Text = L"labelResult";
			// 
			// labelSelectInstance
			// 
			this->labelSelectInstance->AutoSize = true;
			this->labelSelectInstance->Location = System::Drawing::Point(13, 35);
			this->labelSelectInstance->Name = L"labelSelectInstance";
			this->labelSelectInstance->Size = System::Drawing::Size(37, 13);
			this->labelSelectInstance->TabIndex = 1;
			this->labelSelectInstance->Text = L"Select";
			// 
			// comboBoxSelectInst
			// 
			this->comboBoxSelectInst->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxSelectInst->FormattingEnabled = true;
			this->comboBoxSelectInst->Location = System::Drawing::Point(16, 51);
			this->comboBoxSelectInst->Name = L"comboBoxSelectInst";
			this->comboBoxSelectInst->Size = System::Drawing::Size(430, 21);
			this->comboBoxSelectInst->TabIndex = 2;
			this->comboBoxSelectInst->Visible = false;
			// 
			// btnBrowse
			// 
			this->btnBrowse->Location = System::Drawing::Point(16, 96);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(75, 23);
			this->btnBrowse->TabIndex = 3;
			this->btnBrowse->Text = L"Browse";
			this->btnBrowse->UseVisualStyleBackColor = true;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &SetupForm::btnBrowse_Click);
			// 
			// ttPath
			// 
			this->ttPath->AutoPopDelay = 5000;
			this->ttPath->InitialDelay = 2;
			this->ttPath->ReshowDelay = 100;
			// 
			// btnConfirm
			// 
			this->btnConfirm->Location = System::Drawing::Point(371, 96);
			this->btnConfirm->Name = L"btnConfirm";
			this->btnConfirm->Size = System::Drawing::Size(75, 23);
			this->btnConfirm->TabIndex = 5;
			this->btnConfirm->Text = L"Confirm";
			this->btnConfirm->UseVisualStyleBackColor = true;
			this->btnConfirm->Click += gcnew System::EventHandler(this, &SetupForm::btnConfirm_Click);
			// 
			// SetupForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(458, 131);
			this->Controls->Add(this->btnConfirm);
			this->Controls->Add(this->btnBrowse);
			this->Controls->Add(this->comboBoxSelectInst);
			this->Controls->Add(this->labelSelectInstance);
			this->Controls->Add(this->labelResult);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"SetupForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Setup";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);
	private: Void btnBrowse_Click(Object^ sender, EventArgs^ e);
	private: Void OnProcessFound(String^ processPath);
	private: Void OnDoWork(Object^ sender, DoWorkEventArgs^ e);
	private: Void OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e);
	private: Void OnLoad(Object^ sender, EventArgs^ e);
	private: Void btnConfirm_Click(System::Object^ sender, EventArgs^ e);
	};
}
