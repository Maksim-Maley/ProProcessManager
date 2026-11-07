cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME ProProcessManager)

project(${PROJECT_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
    ProProcessManager/main.cpp
    ProProcessManager/ProcessEnumerator.cpp
    ProProcessManager/ProcessEnumerator.hpp
    ProProcessManager/ProcessInfo.hpp
    ProProcessManager/ProcessManager.cpp
    ProProcessManager/ProcessManager.hpp
    ProProcessManager/SystemMemoryInfo.hpp
    ProProcessManager/MemoryMonitor.hpp
    ProProcessManager/MemoryMonitor.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)