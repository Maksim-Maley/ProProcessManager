#pragma once

#include <Windows.h>
#include <cstdint>

struct CpuTimes
{
	std::uint64_t Idle = 0;
	std::uint64_t Kernel = 0;
	std::uint64_t User = 0;
};

class CpuMonitor
{
private:
	CpuTimes previousTimes;
	CpuTimes currentTimes;
	bool hasPreviousMeasurement = false;
	double cpuUsage = 0.0;
public:
	bool GetSystemCpuTimes(CpuTimes& times);
	std::uint64_t FileTimeToUInt64(const FILETIME& ft);
	void Update();
	double GetCpuUsage();
};