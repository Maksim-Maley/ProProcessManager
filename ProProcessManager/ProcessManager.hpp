#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <optional>
#include <array>
#include <functional>
#include "ProcessInfo.hpp"

enum class SortOrder
{
	Ascending,
	Descending
};

enum class SortBy
{
	PID,
	ThreadCount,
	Name
};

class ProcessManager
{
public:
	std::vector<ProcessInfo> FilterByName(const std::vector<ProcessInfo>& processes, const std::wstring& name);
	std::optional<ProcessInfo> FindByPid(const std::vector<ProcessInfo>& processes, DWORD pid);
	void SortProcesses(std::vector<ProcessInfo>& processes, SortBy sortBy, SortOrder order);
};
