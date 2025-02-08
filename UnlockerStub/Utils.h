#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <span>

template<typename T, typename Func>
class MemoryGuard
{
	T pResource;
	Func pFree;
public:
	MemoryGuard(T pAddress, Func pFunc) : pResource(pAddress), pFree(pFunc) {}
	~MemoryGuard() { if (pResource) pFree(pResource); }
	operator T() const { return pResource; }
	T Get() const { return pResource; }
	operator bool() const { return pResource != nullptr && pResource != INVALID_HANDLE_VALUE; }

};

using HandleGuard = MemoryGuard<HANDLE, decltype(&CloseHandle)>;
using MappedMemoryGuard = MemoryGuard<LPVOID, decltype(&UnmapViewOfFile)>;

namespace Utils
{

	std::wstring GetModulePath(HMODULE hModule);
	std::vector<uint8_t*> PatternScanAll(std::span<uint8_t> bytes, const char* pattern);

	std::wstring GetErrorMessage(DWORD errorCode);
	void ShowWin32Error(const std::wstring& apiName);
	void ShowError(const std::wstring& message);

}