#include "ProcessEnumerator.hpp"
#include "ProcessManager.hpp"
#include "MemoryMonitor.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    ProcessEnumerator enumerator;

    std::vector<ProcessInfo> processes = enumerator.GetProcess();

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
                << std::setw(7) << processes[i].workingSetSize << " KiB" << " | "
                << '\n';
        }
        std::wcout << '\n';
    }

    //Info memory system
    SystemMemoryMonitor systemMonitor;
    SystemMemoryInfo systemMemoryI;

    if (systemMonitor.UpdateMemorySystem(systemMemoryI))
    {
        std::cout << "Total RAM: "
            << systemMemoryI.totalPhysical << " MiB\n";

        std::cout << "Used RAM: "
            << systemMemoryI.usedPhysical << " MiB\n";

        std::cout << "Available RAM: "
            << systemMemoryI.availablePhysical << " MiB\n";

        std::cout << "Memory Load: "
            << systemMemoryI.memoryLoad << "%\n";
    }
    std::wcout << '\n';

    ProcessManager manager;
    std::wstring name;
    DWORD pid;

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

    //Sort
    int sortChoice, orderChoice;

    std::wcout << "\n========== PROCESS SORTING ==========\n";

    std::wcout << "[1] Sort by PID\n";
    std::wcout << "[2] Sort by Thread Count\n";
    std::wcout << "[3] Sort by Process Name\n";

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
            << '\n';
    }
}

