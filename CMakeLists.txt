cmake_minimum_required(VERSION 3.10)
project(StudentManagement)

include(CTest) 
set(CMAKE_CXX_STANDARD 17)

add_executable(StudentManagement.exe
    main.cpp
    Student.cpp
)
