#pragma once

#include <vector>
#include "ProcessInfo.hpp"
#include "SystemMemoryInfo.hpp"

class MemoryMonitor
{
public:
	void UpdateMemory(std::vector<ProcessInfo>& processes);
};

class SystemMemoryMonitor
{
public:
	bool UpdateMemorySystem(SystemMemoryInfo& memoryInfo);
};