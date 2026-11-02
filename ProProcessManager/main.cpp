#include "ProcessEnumerator.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    ProcessEnumerator enumerator;

    std::vector<ProcessInfo> processes = enumerator.GetProcess();

    std::wcout << "Processes: " << processes.size()
        << '\n'
        << '\n';

    if (processes.empty())
    {
        std::cout << "Nothing" << '\n';
    }
    else
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

