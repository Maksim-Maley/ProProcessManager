#pragma once

#include <Windows.h>
#include <string>

struct ProcessInfo
{
	DWORD pid;
	std::wstring name;
	DWORD parentPid;
	DWORD threadCount;
	SIZE_T workingSetSize;
};