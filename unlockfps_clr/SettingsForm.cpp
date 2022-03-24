#include "Unmanaged.h"
#include "SettingsForm.h"

using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace unlockfpsclr
{

    Void SettingsForm::UpdateSettings(System::Object^ sender, FormClosingEventArgs^ e)
    {
        // update settings and write to file
        // will be called upon closing 'Settings' dialog

        settings->CustomResX = Convert::ToInt32(customResX->Value);
        settings->CustomResY = Convert::ToInt32(customResY->Value);
        settings->MonitorNum = Convert::ToInt32(monitorNum->Value);
        settings->IsExclusiveFullscreen = comboWindowMode->SelectedIndex == 1;
        settings->Priority = comboPriority->SelectedIndex;

        settings->Save();
        lbDllList->Items->Clear();
    }

    Void SettingsForm::btnDllRemove_Click(Object^ sender, EventArgs^ e)
    {
        auto index = lbDllList->SelectedIndex;
        if (index >= 0)
        {
            // if nothing goes wrong...
            // the size of these two list should be the same
            settings->DllList->RemoveAt(index);
            lbDllList->Items->RemoveAt(index);
        }
    }

    Void SettingsForm::OnLoad(Object^ sender, EventArgs^ e)
    {
        monitorNum->Maximum = GetSystemMetrics(SM_CMONITORS); // get maximum monitor count
        customResX->Value = Convert::ToDecimal(std::clamp(settings->CustomResX, Convert::ToInt32(customResX->Minimum), Convert::ToInt32(customResX->Maximum))); // sanitization
        customResY->Value = Convert::ToDecimal(std::clamp(settings->CustomResY, Convert::ToInt32(customResY->Minimum), Convert::ToInt32(customResY->Maximum))); // sanitization
        monitorNum->Value = Convert::ToDecimal(std::clamp(settings->MonitorNum, Convert::ToInt32(monitorNum->Minimum), Convert::ToInt32(monitorNum->Maximum))); // sanitization
        comboWindowMode->SelectedIndex = Convert::ToInt32(settings->IsExclusiveFullscreen);
        comboPriority->SelectedIndex = std::clamp(settings->Priority, -1, comboPriority->Items->Count);
        lbDllList->Items->AddRange(settings->DllList->ToArray());
    }

    Void SettingsForm::btnDllAdd_Click(Object^ sender, EventArgs^ e)
    {
        auto dialog = gcnew OpenFileDialog();
        dialog->Filter = "DLL (*.dll)|*.dll|All files (*.*)|*.*";
        dialog->FilterIndex = 0;
        dialog->RestoreDirectory = true;

        if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            auto selectedFile = dialog->FileName;
            auto fileName = Path::GetFileName(selectedFile);          

            if (auto index = lbDllList->Items->IndexOf(selectedFile); index >= 0)
            {
                lbDllList->SelectedIndex = index;
                MessageBox::Show("File already in list", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            // read and validate pe header
            auto fileStream = File::OpenRead(selectedFile);
            auto rawBytes = gcnew array<uint8_t>(0x1000);
            fileStream->Read(rawBytes, 0, 0x1000);
            pin_ptr<Byte> pinned = &rawBytes[0];
            if (!Unmanaged::VerifyDLL((PVOID)pinned))
            {
                MessageBox::Show("Invalid File\nThe DLL is either corrupted or 32-bit\nOnly 64-bit DLLs are supported", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            settings->DllList->Add(selectedFile);
            lbDllList->Items->Add(selectedFile);
        }

    }

    Void SettingsForm::OnFormat(Object^ sender, ListControlConvertEventArgs^ e)
    {
        // formatting for dll list box
        e->Value = Path::GetFileName(safe_cast<String^>(e->Value));
    }

}
