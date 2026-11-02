#include "ProcessEnumerator.hpp"
#include <TlHelp32.h>

std::vector<ProcessInfo> ProcessEnumerator::GetProcess()
{
    std::vector<ProcessInfo> processes;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        DWORD errorCode = GetLastError();
        return processes;
    }

    PROCESSENTRY32W processEntry{};
    processEntry.dwSize = sizeof(PROCESSENTRY32W);

    BOOL result = Process32FirstW(snapshot, &processEntry);  
    if (!result)
    {
        DWORD errorCode = GetLastError();
        CloseHandle(snapshot);
        return processes;
    }
    
    do
    {
        ProcessInfo process{processEntry.th32ProcessID, 
            processEntry.szExeFile, 
            processEntry.th32ParentProcessID, 
            processEntry.cntThreads};

        processes.push_back(process);

        SetLastError(ERROR_SUCCESS);
        result = Process32NextW(snapshot, &processEntry);
    } while (result);
    
    DWORD errorCode = GetLastError();

    if (errorCode != ERROR_NO_MORE_FILES)
    {
        CloseHandle(snapshot);
        return processes;
    }
    
    CloseHandle(snapshot);

    return processes;
}
