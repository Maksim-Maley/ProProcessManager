#include "ProcessEnumerator.hpp"
#include "ProcessManager.hpp"
#include "MemoryMonitor.hpp"
#include "CpuMonitor.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    ProcessEnumerator enumerator;

    std::vector<ProcessInfo> processes = enumerator.GetProcess();

    ProcessManager manager;
    std::wstring name;

    std::wcout << "Find process name: ";
    std::getline(std::wcin, name);

    std::vector<ProcessInfo> nameFindProcess = manager.FindByName(processes, name);

    // Name Find process
    if (nameFindProcess.empty())
    {
        std::wcout << "Nothing" << '\n';
    }
    else
    {
        std::wcout << L"Found processes: "
            << nameFindProcess.size() << L"\n";

        std::wcout << std::left;
        std::wcout << std::setw(5)
            << "PID" << " | "
            << std::setw(40)
            << "NAME"
            << "\n";
        std::wcout << "--------------------------------------------------" << std::endl;
        for (std::size_t i = 0; i < nameFindProcess.size(); ++i)
        {
            std::wcout << std::left
                << std::setw(5) << nameFindProcess[i].pid << " | "
                << std::setw(40) << nameFindProcess[i].name << " | "
                << '\n';
        }
        std::wcout << '\n';
    }

    MemoryMonitor memoryMonitor;
    memoryMonitor.UpdateMemory(processes);

    //Processes list
    std::wcout << "Processes: " << processes.size()
        << '\n'
        << '\n';

    if (processes.empty())
    {
        std::wcout << "Nothing" << '\n';
    }
    else
    {
        std::wcout << std::left;
        std::wcout << std::setw(5)
            << "PID" << " | "
            << std::setw(40)
            << "NAME" << " | "
            << std::setw(6)
            << "PARENT" << " | "
            << std::setw(7)
            << "THREADS" << " | "
            << "\n";
        std::wcout << "--------------------------------------------------------------------------------------" << std::endl;
        for (std::size_t i = 0; i < processes.size(); ++i)
        {
            std::wcout << std::left
                << std::setw(5) << processes[i].pid << " | "
                << std::setw(40) << processes[i].name << " | "
                << std::setw(6) << processes[i].parentPid << " | "
                << std::setw(7) << processes[i].threadCount << " | "
                << std::setw(7) << processes[i].workingSetSize /1024 << " KiB" << " | "
                << std::setw(7) << processes[i].cpuUsage << " | "
                << '\n';
        }
        std::wcout << '\n';
    }

    //Info memory system
    SystemMemoryMonitor systemMonitor;
    SystemMemoryInfo systemMemoryI;

    if (systemMonitor.UpdateMemorySystem(systemMemoryI))
    {
        std::wcout << "Total RAM: "
            << systemMemoryI.totalPhysical / (1024 * 1024) << " MiB\n";

        std::wcout << "Used RAM: "
            << systemMemoryI.usedPhysical / (1024 * 1024) << " MiB\n";

        std::wcout << "Available RAM: "
            << systemMemoryI.availablePhysical / (1024 * 1024) << " MiB\n";

        std::wcout << "Memory Load: "
            << systemMemoryI.memoryLoad << "%\n";
    }
    std::wcout << '\n';

    CpuMonitor cpuMonitor;

    cpuMonitor.Update();

    Sleep(1000);

    cpuMonitor.Update();
    double usage = cpuMonitor.GetCpuUsage();

    std::wcout << L"CPU Usage: " << usage << L"%" << '\n';

    //Sort
    int sortChoice, orderChoice;

    std::wcout << "\n========== PROCESS SORTING ==========\n";

    std::wcout << "[1] Sort by PID\n";
    std::wcout << "[2] Sort by Thread Count\n";
    std::wcout << "[3] Sort by Process Name\n";
    std::wcout << "[4] Sort by Memory\n";

    std::wcout << "\nYour choice: ";
    std::wcin >> sortChoice;

    SortBy sortBy;

    switch (sortChoice)
    {
    case 1:
    {
        sortBy = SortBy::PID;
        break;
    }
    case 2:
    {
        sortBy = SortBy::ThreadCount;
        break;
    }
    case 3:
    {
        sortBy = SortBy::Name;
        break;
    }
    case 4:
    {
        sortBy = SortBy::Memory;
        break;
    }
    default:
        std::wcout << "Invalid sorting option!\n";
        return 1;
    }

    std::wcout << "\n========== SORT ORDER ==========\n";

    std::wcout << "[1] Ascending\n";
    std::wcout << "[2] Descending\n";

    std::wcout << "\nYour choice: ";
    std::wcin >> orderChoice;

    SortOrder order;

    switch (orderChoice)
    {
    case 1:
    {
        order = SortOrder::Ascending;
        break;
    }
    case 2:
    {
        order = SortOrder::Descending;
        break;
    }
    default:
        std::wcout << "Invalid sorting option!\n";
        return 1;
    }
    
    manager.SortProcesses(processes, sortBy, order);

    std::wcout << std::left;
    std::wcout << std::setw(5)
        << "PID" << " | "
        << std::setw(40)
        << "NAME" << " | "
        << std::setw(6)
        << "PARENT" << " | "
        << std::setw(7)
        << "THREADS" << " | "
        << "\n";
    std::wcout << "--------------------------------------------------------------------------------------" << std::endl;
    for (std::size_t i = 0; i < processes.size(); ++i)
    {
        std::wcout << std::left
            << std::setw(5) << processes[i].pid << " | "
            << std::setw(40) << processes[i].name << " | "
            << std::setw(6) << processes[i].parentPid << " | "
            << std::setw(7) << processes[i].threadCount << " | "
            << std::setw(7) << processes[i].workingSetSize / 1024 << " KiB" << " | "
            << '\n';
    }std::wcout << '\n';

    DWORD pid;

    std::wcout << "Find process pid: ";
    std::wcin >> pid;

    std::optional<ProcessInfo> pidFindProcess = manager.FindByPid(processes, pid);

    //PID find process
    if (pidFindProcess.has_value())
    {
        std::wcout << "Name: " << pidFindProcess->name << '\n';
        std::wcout << "PID: " << pidFindProcess->pid << '\n'
            << '\n';
    }
    else
    {
        std::wcout << "Process not found!\n";
    }

}

