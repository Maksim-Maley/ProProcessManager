#include "ProcessEnumerator.hpp"
#include "ProcessManager.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    std::wstring name;
    int pid;

    ProcessEnumerator enumerator;
    ProcessManager manager;

    std::wcout << "Find process name: ";
    std::wcin >> name;

    std::vector<ProcessInfo> processes = enumerator.GetProcess();
    std::vector<ProcessInfo> nameFindProcess = manager.FilterByName(processes, name);
    
    // Name Find process
    if (nameFindProcess.empty())
    {
        std::cout << "Nothing" << '\n';
    }
    else
    {
        std::wcout << L"Found processes: "
            << nameFindProcess.size() << L"\n";

        std::cout << std::left;
        std::cout << std::setw(5)
            << "PID" << " | "
            << std::setw(40)
            << "NAME" 
            << "\n";
        std::cout << "--------------------------------------------------" << std::endl;
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
        std::cout << "Process not found!\n";
    }
    
    

    //Processes list
    std::wcout << "Processes: " << processes.size()
        << '\n'
        << '\n';

    if (processes.empty())
    {
        std::cout << "Nothing" << '\n';
    }
    else
    {
        std::cout << std::left;
        std::cout << std::setw(5)
            << "PID" << " | "
            << std::setw(40)
            << "NAME" << " | "
            << std::setw(6)
            << "PARENT" << " | "
            << std::setw(7)
            << "THREADS" << " | "
            << "\n";
        std::cout << "--------------------------------------------------------------------------------------" << std::endl;
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

    int sortChoice, orderChoice;

    std::cout << "\n========== PROCESS SORTING ==========\n";

    std::cout << "[1] Sort by PID\n";
    std::cout << "[2] Sort by Thread Count\n";
    std::cout << "[3] Sort by Process Name\n";

    std::cout << "\nYour choice: ";
    std::cin >> sortChoice;

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
        std::cout << "Invalid sorting option!\n";
        return 1;
    }

    std::cout << "\n========== SORT ORDER ==========\n";

    std::cout << "[1] Ascending\n";
    std::cout << "[2] Descending\n";

    std::cout << "\nYour choice: ";
    std::cin >> orderChoice;

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
        std::cout << "Invalid sorting option!\n";
        return 1;
    }
    
    manager.SortProcesses(processes, sortBy, order);

    std::cout << std::left;
    std::cout << std::setw(5)
        << "PID" << " | "
        << std::setw(40)
        << "NAME" << " | "
        << std::setw(6)
        << "PARENT" << " | "
        << std::setw(7)
        << "THREADS" << " | "
        << "\n";
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
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

