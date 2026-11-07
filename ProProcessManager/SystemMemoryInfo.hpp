#pragma once

#include <Windows.h>
#include <cstdint>

struct SystemMemoryInfo
{
    std::uint64_t totalPhysical = 0;
    std::uint64_t availablePhysical = 0;
    std::uint64_t usedPhysical = 0;

    DWORD memoryLoad = 0;
};