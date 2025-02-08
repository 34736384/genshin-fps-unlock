#include "Utils.h"
#include <intrin.h>
#include <array>
#include <ranges>
#include <cmath>
#include <format>

namespace
{
	std::tuple<std::vector<uint8_t>, std::string> PatternToBytes(const char* pattern)
	{
		std::vector<uint8_t> bytes;
		std::string mask;

		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
				mask.push_back('?');
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
				mask.push_back('x');
			}
		}
		return { bytes, mask };
	}
}

std::wstring Utils::GetModulePath(HMODULE hModule)
{
    
	std::wstring path(MAX_PATH, L'\0');
	auto nChars = GetModuleFileNameW(hModule, path.data(), static_cast<uint32_t>(path.size()));

	while (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		path.resize(path.size() * 2);
		nChars = GetModuleFileNameW(hModule, path.data(), static_cast<uint32_t>(path.size()));
	}

	path.resize(nChars);
	return path;

}

std::vector<uint8_t*> Utils::PatternScanAll(std::span<uint8_t> bytes, const char* pattern)
{
	std::vector<uint8_t*> results;
	const auto [patternBytes, patternMask] = PatternToBytes(pattern);
	constexpr std::size_t chunkSize = 16;

	const auto maskCount = static_cast<std::size_t>(std::ceil(patternMask.size() / chunkSize));
	std::array<int32_t, 32> masks{};

	auto chunks = patternMask | std::views::chunk(chunkSize);
	for (std::size_t i = 0; auto chunk : chunks) {
		int32_t mask = 0;
		for (std::size_t j = 0; j < chunk.size(); ++j) {
			if (chunk[j] == 'x') {
				mask |= 1 << j;
			}
		}
		masks[i++] = mask;
	}

	__m128i xmm1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(patternBytes.data()));
	__m128i xmm2, xmm3, mask;

	auto pData = bytes.data();
	const auto end = pData + bytes.size() - patternMask.size();

	while (pData < end)
	{
		_mm_prefetch(reinterpret_cast<const char*>(pData + 64), _MM_HINT_NTA);

		if (patternBytes[0] == pData[0])
		{
			xmm2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pData));
			mask = _mm_cmpeq_epi8(xmm1, xmm2);

			if ((_mm_movemask_epi8(mask) & masks[0]) == masks[0])
			{
				bool found = true;
				for (int i = 1; i < maskCount; ++i)
				{
					xmm2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pData + i * chunkSize));
					xmm3 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(patternBytes.data() + i * chunkSize));
					mask = _mm_cmpeq_epi8(xmm2, xmm3);
					if ((_mm_movemask_epi8(mask) & masks[i]) != masks[i])
					{
						found = false;
						break;
					}
				}


				if (found) {
					results.push_back(pData);
				}

			}


		}

		++pData;
	}

	return results;
}

std::wstring Utils::GetErrorMessage(DWORD errorCode)
{
	
	LPWSTR messageBuffer = nullptr;
	const auto size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, errorCode, GetUserDefaultLangID(), reinterpret_cast<LPWSTR>(&messageBuffer), 0, nullptr);

	std::wstring message(messageBuffer, size);
	LocalFree(messageBuffer);

	return message;

}

void Utils::ShowWin32Error(const std::wstring& apiName)
{

	const auto errorCode = GetLastError();
	const auto errorMessage = GetErrorMessage(errorCode);
	
	std::wstring message = std::format(L"{} failed\nError code: {}\nError message: {}", apiName, errorCode, errorMessage);
	ShowError(message);

}

void Utils::ShowError(const std::wstring& message)
{
	MessageBoxW(nullptr, message.c_str(), L"[FPS Unlocker] Error", MB_ICONERROR);
}
