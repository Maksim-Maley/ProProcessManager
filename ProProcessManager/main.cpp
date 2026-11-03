#include "ProcessEnumerator.hpp"
#include "ProcessManager.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    std::wstring name;

    ProcessEnumerator enumerator;
    ProcessManager manager;

    std::wcout << "Find process: ";
    std::wcin >> name;

    std::vector<ProcessInfo> processes = enumerator.GetProcess();
    std::vector<ProcessInfo> nameFindProcess = manager.FilterByName(processes, name);

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
    
}

