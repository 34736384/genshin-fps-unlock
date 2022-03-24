#pragma once
#include "Settings.h"

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace Microsoft::Win32;
using namespace System::Runtime::InteropServices;

namespace Managed
{
	// start game with launch options
	bool StartGame(Settings^ settings);

	// attempt to find game path through registry
	List<String^>^ TryResolveGamePath();

	// get game path while the game is running
	String^ TryGetGamePath();

	void InjectDLLs(List<String^>^ paths);
};