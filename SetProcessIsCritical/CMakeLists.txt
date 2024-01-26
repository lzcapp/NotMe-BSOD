cmake_minimum_required(VERSION 3.27)
project(SetProcessIsCritical)

set(CMAKE_CXX_STANDARD 11)

add_executable(SetProcessIsCritical WIN32 RtlSetProcessIsCritical.cpp)
