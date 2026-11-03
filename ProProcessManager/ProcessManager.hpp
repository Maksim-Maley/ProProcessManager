#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "ProcessInfo.hpp"

class ProcessManager
{
public:
	std::vector<ProcessInfo> FilterByName(const std::vector<ProcessInfo>& processes, const std::wstring& name);
};
