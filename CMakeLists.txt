cmake_minimum_required(VERSION 3.23)
project(B3_21)

set(CMAKE_CXX_STANDARD 20)

add_executable(B3_21 main.cpp ForSociety/for_society.hpp Number/number.hpp Backup/backup.hpp CalcExec/calc_exec.hpp
        Memory/memory.hpp Backup/backup.cpp CalcExec/calc_exec.cpp ForSociety/for_society.cpp Memory/memory.cpp
        Number/number.cpp Program/program.cpp Program/program.hpp CalcExec/calc_operations.cpp)
