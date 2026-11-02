#pragma once

#include <vector>
#include "ProcessInfo.hpp"

class ProcessEnumerator
{
public:
    std::vector<ProcessInfo> GetProcess();
};