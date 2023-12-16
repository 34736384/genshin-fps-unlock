#include "SetupForm.h"
#include "Managed.h"

using namespace System::Threading;
using namespace System::Windows::Forms;

namespace unlockfpsclr
{

    Void SetupForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(settings->GamePath))
            Application::Exit();
    }

    Void SetupForm::btnBrowse_Click(Object^ sender, EventArgs^ e)
    {
        auto dialog = gcnew OpenFileDialog();
        dialog->Filter = "Process (*.exe)|*.exe|All files (*.*)|*.*";
        dialog->FilterIndex = 0;
        dialog->RestoreDirectory = true;

        if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            auto selectedFile = dialog->FileName;
            auto directory = Path::GetDirectoryName(selectedFile);
            
            if (!selectedFile->Contains("GenshinImpact.exe") && !selectedFile->Contains("YuanShen.exe"))
            {
                MessageBox::Show("Please select the game exe\nGenshinImpact.exe for OS version\nor\nYuanShen.exe for CN version", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (!File::Exists(directory + "\\UnityPlayer.dll"))
            {
                MessageBox::Show("That's not the right place", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (backgroundWorker)
                backgroundWorker->CancelAsync();
            settings->GamePath = selectedFile;
            settings->Save();
            this->Close();
        }

    }

    Void SetupForm::OnProcessFound(String^ processPath)
    {
        settings->GamePath = processPath;
        settings->Save();
        this->Close();
    }

    Void SetupForm::OnDoWork(Object^ sender, DoWorkEventArgs^ e)
    {
        auto worker = safe_cast<BackgroundWorker^>(sender);
        while (!worker->CancellationPending)
        {
            auto path = Managed::TryGetGamePath();
            if (!String::IsNullOrWhiteSpace(path))
            {
                settings->GamePath = path;
                settings->Save();
                worker->ReportProgress(100);
                break;
            }

            Thread::Sleep(200);
        }
        
    }

    Void SetupForm::OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e)
    {
        auto object = e->UserState;
        auto percentage = e->ProgressPercentage;
        if (percentage == 100)
            this->Close();
    }

    Void SetupForm::OnLoad(Object^ sender, EventArgs^ e)
    {
        auto result = Managed::TryResolveGamePath();
        if (result->Count)
        {
            btnConfirm->Visible = true;
            //btnBrowse->Visible = false;
            labelResult->Text = String::Format("Found {0} installation of the game", result->Count);
            labelResult->ForeColor = Color::Green;
            labelSelectInstance->Text = "Select the instance you want to use:";
            comboBoxSelectInst->Visible = true;
            comboBoxSelectInst->Items->AddRange(result->ToArray());
            comboBoxSelectInst->SelectedIndex = 0;
            if (!String::IsNullOrWhiteSpace(settings->GamePath))
                comboBoxSelectInst->SelectedIndex = result->IndexOf(settings->GamePath);
        }
        else
        {
            btnConfirm->Visible = false;
            //btnBrowse->Visible = true;
            labelResult->Text = "cannot find your game";
            labelResult->ForeColor = Color::Red;
            labelSelectInstance->Text = "You can open the game now or browse";
            comboBoxSelectInst->Visible = false;

            backgroundWorker = gcnew BackgroundWorker();
            backgroundWorker->WorkerReportsProgress = true;
            backgroundWorker->WorkerSupportsCancellation = true;
            backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &SetupForm::OnDoWork);
            backgroundWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &SetupForm::OnProgressChanged);
            backgroundWorker->RunWorkerAsync();
        }
    }

    Void SetupForm::btnConfirm_Click(Object^ sender, EventArgs^ e)
    {
        settings->GamePath = safe_cast<String^>(comboBoxSelectInst->Items[comboBoxSelectInst->SelectedIndex]);
        settings->Save();
        this->Close();
    }

}
