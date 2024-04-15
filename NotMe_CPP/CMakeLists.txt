cmake_minimum_required(VERSION 3.10)
project(Trigger-BSOD)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(NtRaiseHardError NtRaiseHardError.cpp rc.rc)
add_executable(ZwRaiseHardError ZwRaiseHardError.cpp rc.rc)

add_executable(CloseWindowStation CloseWindowStation.cpp rc.rc)

add_executable(SetProcessIsCritical SetProcessIsCritical.cpp rc.rc)
