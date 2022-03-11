#include "error.h"

std::string GetLastErrorAsString(DWORD code)
{
	LPSTR buf = nullptr;
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);
	std::string ret = buf;
	LocalFree(buf);
	return ret;
}
