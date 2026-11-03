#include "ProcessManager.hpp"

std::vector<ProcessInfo> ProcessManager::FilterByName(const std::vector<ProcessInfo>& processes, const std::wstring& name)
{
	std::vector<ProcessInfo> nameFindProcess;

	for (const auto& process : processes)
	{
		if (process.name.find(name) != std::wstring::npos)
		{
			nameFindProcess.push_back(process);
		}
	}

	return nameFindProcess;
}