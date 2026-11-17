#include "CpuMonitor.hpp"

std::uint64_t CpuMonitor::FileTimeToUInt64(const FILETIME& ft)
{
	ULARGE_INTEGER timeValue{};

	timeValue.LowPart = ft.dwLowDateTime;
	timeValue.HighPart = ft.dwHighDateTime;

	return timeValue.QuadPart;
}

bool CpuMonitor::GetSystemCpuTimes(CpuTimes& times)
{
	FILETIME idleTime, kernelTime, userTime;

	BOOL result = GetSystemTimes(&idleTime, &kernelTime, &userTime);

	if (!result)
	{
		DWORD errorCode = GetLastError();
		return false;
	}
		
	times.Idle = FileTimeToUInt64(idleTime);
	times.Kernel = FileTimeToUInt64(kernelTime);
	times.User = FileTimeToUInt64(userTime);
	return true;
}

void CpuMonitor::Update()
{
	if (!GetSystemCpuTimes(currentTimes))
	{
		DWORD errorCode = GetLastError();
		return;
	}

	if (hasPreviousMeasurement == false)
	{
		previousTimes = currentTimes;
		hasPreviousMeasurement = true;
		return;
	}
	
	const std::uint64_t idleDelta = currentTimes.Idle - previousTimes.Idle;

	const std::uint64_t kernelDelta = currentTimes.Kernel - previousTimes.Kernel;

	const std::uint64_t userDelta = currentTimes.User - previousTimes.User;

	const std::uint64_t totalDelta = kernelDelta + userDelta;

	const std::uint64_t busyDelta = totalDelta - idleDelta;

	if (totalDelta == 0)
	{
		return;
	}

	cpuUsage = static_cast<double>(busyDelta) / totalDelta * 100;

	previousTimes = currentTimes;
}

double CpuMonitor::GetCpuUsage()
{
	return cpuUsage;
}
