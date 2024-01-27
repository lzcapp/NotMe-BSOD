cmake_minimum_required(VERSION 3.10)
project(Trigger-BSOD)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(NtRaiseHardError RaiseHardError/NtRaiseHardError.cpp)
add_executable(ZwRaiseHardError RaiseHardError/ZwRaiseHardError.cpp)

add_executable(SetProcessIsCritical WIN32 SetProcessIsCritical/RtlSetProcessIsCritical.cpp)
