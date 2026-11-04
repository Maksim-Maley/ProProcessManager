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

std::optional<ProcessInfo> ProcessManager::FindByPid(const std::vector<ProcessInfo>& processes, DWORD pid)
{
	for (const auto& process : processes)
	{
		if (process.pid == pid)
		{
			return process;
		}
	}

	return std::nullopt;
}

void ProcessManager::SortProcesses(std::vector<ProcessInfo>& processes, SortBy sortBy, SortOrder order)
{
	switch (sortBy)
	{
	case SortBy::PID:
	{
		switch (order)
		{
		case SortOrder::Ascending:
		{
			std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b)
				{
					return a.pid < b.pid;
				}
			);
			break;
		}
		case SortOrder::Descending:
		{
			std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b)
				{
					return a.pid > b.pid;
				}
			);
			break;
		}
		}
		break;
	}
	case SortBy::Name:
	{
		switch (order)
		{
		case SortOrder::Ascending:
		{
			std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b)
				{
					return a.name < b.name;
				}
			);
			break;
		}
		case SortOrder::Descending:
		{
			std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b)
				{
					return a.name > b.name;
				}
			);
			break;
		}
		}
		break;
	}
	case SortBy::ThreadCount:
	{
		switch (order)
		{
		case SortOrder::Ascending:
		{
			std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b)
				{
					return a.threadCount < b.threadCount;
				}
			);
			break;
		}
		case SortOrder::Descending:
		{
			std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b)
				{
					return a.threadCount > b.threadCount;
				}
			);
			break;
		}
		}
		break;
	}
	}
}
