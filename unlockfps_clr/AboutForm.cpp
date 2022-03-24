#include "AboutForm.h"

using namespace System::Diagnostics;

namespace unlockfpsclr
{
	Void AboutForm::linkLabelSource_LinkClicked(Object^ sender, LinkLabelLinkClickedEventArgs^ e)
	{
		Process::Start("https://github.com/34736384/genshin-fps-unlock");
	}

	Void AboutForm::linkLabelIssues_LinkClicked(Object^ sender, LinkLabelLinkClickedEventArgs^ e)
	{
		Process::Start("https://github.com/34736384/genshin-fps-unlock/issues");
	}
}
