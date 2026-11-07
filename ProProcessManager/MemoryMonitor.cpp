#include "MemoryMonitor.hpp"
#include <psapi.h>

void MemoryMonitor::UpdateMemory(std::vector<ProcessInfo>& processes)
{
	for (ProcessInfo& process : processes)
	{
		HANDLE processHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, process.pid);

		if (processHandle == nullptr)
		{
			DWORD errorCode = GetLastError();
			process.workingSetSize = 0;
			continue;
		}

		PROCESS_MEMORY_COUNTERS memoryCounters{};
		memoryCounters.cb = sizeof(memoryCounters);

		BOOL result = GetProcessMemoryInfo(processHandle, &memoryCounters, sizeof(memoryCounters));	
		
		if (result)
		{
			process.workingSetSize = memoryCounters.WorkingSetSize / 1024;
		}
		else
		{
			DWORD errorCode = GetLastError();
			process.workingSetSize = 0;
		}

		CloseHandle(processHandle);
	}
}

bool SystemMemoryMonitor::UpdateMemorySystem(SystemMemoryInfo& memoryInfo)
{
	MEMORYSTATUSEX memoryStatus{};
	memoryStatus.dwLength = sizeof(memoryStatus);

	BOOL result = GlobalMemoryStatusEx(&memoryStatus);

	if (!result)
	{
		return false;
	}

	memoryInfo.totalPhysical = memoryStatus.ullTotalPhys / (1024 * 1024);

	memoryInfo.availablePhysical = memoryStatus.ullAvailPhys / (1024 * 1024);

	memoryInfo.usedPhysical = (memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys) / (1024 * 1024);

	memoryInfo.memoryLoad = memoryStatus.dwMemoryLoad;

	return true;
}
