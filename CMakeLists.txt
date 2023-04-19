cmake_minimum_required(VERSION 3.23)
project(B3_21)

set(CMAKE_CXX_STANDARD 20)

#setting up wxWidgets
set(wxWidgets_ROOT_DIR </opt/homebrew/bin/wx-config>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

#copy necessary files
configure_file(${CMAKE_SOURCE_DIR}/backend/message_queue/message_queue_file ${CMAKE_BINARY_DIR} COPYONLY)

#including project files
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR})


#adding executables
add_executable(B3_21 main.cpp backend/calc_exec/calc_exec.hpp frontend/test.cpp)


add_library(backup OBJECT backend/backup/backup.cpp)
target_include_directories(backup PRIVATE backend/backup)

add_library(calc_exec OBJECT backend/calc_exec/calc_exec.cpp backend/calc_exec/calc_operations.cpp)
target_include_directories(calc_exec PRIVATE backend/calc_exec)

add_library(for_society OBJECT backend/for_society/for_society.cpp)
target_include_directories(for_society PRIVATE backend/for_society)

add_library(number OBJECT backend/number/number.cpp)
target_include_directories(number PRIVATE backend/number)

add_library(number_buffer OBJECT backend/number_buffer/number_buffer.cpp)
target_include_directories(number_buffer PRIVATE backend/number_buffer)

add_library(program OBJECT backend/program_buffer_exec/program.cpp)
target_include_directories(program PRIVATE backend/program_buffer_exec)

add_library(message_queue OBJECT backend/message_queue/message_queue.cpp)
target_include_directories(message_queue PRIVATE backend/message_queue)


target_link_directories(B3_21 PRIVATE ${calc_exec} ${program} ${number_buffer} ${number} ${backup} ${message_queue} ${for_society})

target_link_libraries(B3_21 PRIVATE ${wxWidgets_LIBRARIES})