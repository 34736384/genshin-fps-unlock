#pragma once
#include "Settings.h"
#include "SetupForm.h"
#include "SettingsForm.h"
#include <algorithm>

namespace unlockfpsclr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			settings = Settings::Load();
			settingsForm = gcnew SettingsForm(settings);

			this->Load += gcnew EventHandler(this, &MainForm::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::OnFormClosing);
			this->Resize += gcnew EventHandler(this, &MainForm::OnResize);
			this->notifyIcon->DoubleClick += gcnew EventHandler(this, &MainForm::OnDoubleClick);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Settings^ settings;
	private: BackgroundWorker^ backgroundWorker;
	private: SettingsForm^ settingsForm;
	private: System::Windows::Forms::Button^ btnStartGame;
	private: System::Windows::Forms::CheckBox^ ckbAutoStart;
	private: System::Windows::Forms::ToolTip^ ttAutoStart;
	private: System::Windows::Forms::TrackBar^ tbFPS;
	private: System::Windows::Forms::Label^ labelFPS;

	private: System::Windows::Forms::NumericUpDown^ inputFPS;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ menuItemSettings;




	private: System::Windows::Forms::ToolTip^ ttGamePath;
	private: System::Windows::Forms::ToolStripMenuItem^ menuItemSetup;

	private: System::Windows::Forms::NotifyIcon^ notifyIcon;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuNotify;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuExit;
	private: System::Windows::Forms::ToolStripMenuItem^ menuItemAbout;














	private: System::ComponentModel::IContainer^ components;
	protected:

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
			this->btnStartGame = (gcnew System::Windows::Forms::Button());
			this->ckbAutoStart = (gcnew System::Windows::Forms::CheckBox());
			this->ttAutoStart = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->tbFPS = (gcnew System::Windows::Forms::TrackBar());
			this->labelFPS = (gcnew System::Windows::Forms::Label());
			this->inputFPS = (gcnew System::Windows::Forms::NumericUpDown());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemSettings = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemSetup = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ttGamePath = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuNotify = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripMenuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbFPS))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inputFPS))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->contextMenuNotify->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnStartGame
			// 
			this->btnStartGame->Location = System::Drawing::Point(197, 80);
			this->btnStartGame->Name = L"btnStartGame";
			this->btnStartGame->Size = System::Drawing::Size(75, 23);
			this->btnStartGame->TabIndex = 0;
			this->btnStartGame->TabStop = false;
			this->btnStartGame->Text = L"Start Game";
			this->btnStartGame->UseVisualStyleBackColor = true;
			this->btnStartGame->Click += gcnew System::EventHandler(this, &MainForm::btnStartGame_Click);
			// 
			// ckbAutoStart
			// 
			this->ckbAutoStart->AutoSize = true;
			this->ckbAutoStart->Location = System::Drawing::Point(15, 84);
			this->ckbAutoStart->Name = L"ckbAutoStart";
			this->ckbAutoStart->Size = System::Drawing::Size(144, 17);
			this->ckbAutoStart->TabIndex = 1;
			this->ckbAutoStart->TabStop = false;
			this->ckbAutoStart->Text = L"Start Game Automatically";
			this->ttAutoStart->SetToolTip(this->ckbAutoStart, L"This will take effect on subsequent launch");
			this->ckbAutoStart->UseVisualStyleBackColor = true;
			// 
			// ttAutoStart
			// 
			this->ttAutoStart->AutoPopDelay = 5000;
			this->ttAutoStart->InitialDelay = 1;
			this->ttAutoStart->ReshowDelay = 100;
			// 
			// tbFPS
			// 
			this->tbFPS->AutoSize = false;
			this->tbFPS->Cursor = System::Windows::Forms::Cursors::Hand;
			this->tbFPS->Location = System::Drawing::Point(15, 57);
			this->tbFPS->Maximum = 360;
			this->tbFPS->Minimum = 1;
			this->tbFPS->Name = L"tbFPS";
			this->tbFPS->Size = System::Drawing::Size(257, 21);
			this->tbFPS->TabIndex = 2;
			this->tbFPS->TabStop = false;
			this->tbFPS->TickStyle = System::Windows::Forms::TickStyle::None;
			this->tbFPS->Value = 120;
			// 
			// labelFPS
			// 
			this->labelFPS->AutoSize = true;
			this->labelFPS->Location = System::Drawing::Point(12, 33);
			this->labelFPS->Name = L"labelFPS";
			this->labelFPS->Size = System::Drawing::Size(33, 13);
			this->labelFPS->TabIndex = 3;
			this->labelFPS->Text = L"FPS: ";
			// 
			// inputFPS
			// 
			this->inputFPS->Location = System::Drawing::Point(48, 31);
			this->inputFPS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, 0 });
			this->inputFPS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->inputFPS->Name = L"inputFPS";
			this->inputFPS->Size = System::Drawing::Size(224, 20);
			this->inputFPS->TabIndex = 4;
			this->inputFPS->TabStop = false;
			this->inputFPS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(284, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem
			// 
			this->toolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->menuItemSettings,
					this->menuItemSetup, this->menuItemAbout
			});
			this->toolStripMenuItem->Name = L"toolStripMenuItem";
			this->toolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->toolStripMenuItem->Text = L"Options";
			// 
			// menuItemSettings
			// 
			this->menuItemSettings->Name = L"menuItemSettings";
			this->menuItemSettings->Size = System::Drawing::Size(116, 22);
			this->menuItemSettings->Text = L"Settings";
			this->menuItemSettings->Click += gcnew System::EventHandler(this, &MainForm::settingsMenuItem_Click);
			// 
			// menuItemSetup
			// 
			this->menuItemSetup->Name = L"menuItemSetup";
			this->menuItemSetup->Size = System::Drawing::Size(116, 22);
			this->menuItemSetup->Text = L"Setup";
			this->menuItemSetup->Click += gcnew System::EventHandler(this, &MainForm::setupMenuItem_Click);
			// 
			// menuItemAbout
			// 
			this->menuItemAbout->Name = L"menuItemAbout";
			this->menuItemAbout->Size = System::Drawing::Size(116, 22);
			this->menuItemAbout->Text = L"About";
			this->menuItemAbout->Click += gcnew System::EventHandler(this, &MainForm::menuItemAbout_Click);
			// 
			// ttGamePath
			// 
			this->ttGamePath->AutoPopDelay = 5000;
			this->ttGamePath->InitialDelay = 2;
			this->ttGamePath->ReshowDelay = 100;
			// 
			// notifyIcon
			// 
			this->notifyIcon->BalloonTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			this->notifyIcon->BalloonTipText = L"Minimized to tray";
			this->notifyIcon->BalloonTipTitle = L"FPS Unlocker";
			this->notifyIcon->ContextMenuStrip = this->contextMenuNotify;
			this->notifyIcon->Text = L"Hello";
			this->notifyIcon->Visible = true;
			// 
			// contextMenuNotify
			// 
			this->contextMenuNotify->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripMenuExit });
			this->contextMenuNotify->Name = L"contextMenuNotify";
			this->contextMenuNotify->ShowItemToolTips = false;
			this->contextMenuNotify->Size = System::Drawing::Size(94, 26);
			// 
			// toolStripMenuExit
			// 
			this->toolStripMenuExit->Name = L"toolStripMenuExit";
			this->toolStripMenuExit->Size = System::Drawing::Size(93, 22);
			this->toolStripMenuExit->Text = L"Exit";
			this->toolStripMenuExit->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuExit_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 115);
			this->Controls->Add(this->inputFPS);
			this->Controls->Add(this->labelFPS);
			this->Controls->Add(this->tbFPS);
			this->Controls->Add(this->ckbAutoStart);
			this->Controls->Add(this->btnStartGame);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Genshin FPS Unlocker";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbFPS))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inputFPS))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->contextMenuNotify->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void btnStartGame_Click(Object^ sender, EventArgs^ e);
	private: Void settingsMenuItem_Click(Object^ sender, EventArgs^ e);
	private: Void OnLoad(Object^ sender, EventArgs^ e);
	private: Void setupMenuItem_Click(Object^ sender, EventArgs^ e);
	private: Void OnDoWork(Object^ sender, DoWorkEventArgs^ e);
	private: Void OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e);
	private: Void OnResize(Object^ sender, EventArgs^ e);
	private: Void OnDoubleClick(Object^ sender, EventArgs^ e);
	private: Void toolStripMenuExit_Click(Object^ sender, EventArgs^ e);
	private: Void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);
	private: Void menuItemAbout_Click(Object^ sender, EventArgs^ e);
};
}