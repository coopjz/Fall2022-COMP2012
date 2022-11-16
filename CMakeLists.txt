cmake_minimum_required(VERSION 3.16)
project(comp2012)

set(CMAKE_CXX_STANDARD 14)

include_directories(PA/skeleton)

add_executable(comp2012
        PA/skeleton/a.out
        PA/skeleton/course.cpp
        PA/skeleton/course.h
        PA/skeleton/course.o
        PA/skeleton/course_database.cpp
        PA/skeleton/course_database.h
        PA/skeleton/course_database.o
        PA/skeleton/main.cpp
        PA/skeleton/main.o
        PA/skeleton/Makefile
        PA/skeleton/pa1
        PA/skeleton/student.cpp
        PA/skeleton/student.h
        PA/skeleton/student.o
        PA/skeleton/student_database.cpp
        PA/skeleton/student_database.h
        PA/skeleton/student_database.o
        PA/skeleton/swap_list.cpp
        PA/skeleton/swap_list.h
        PA/skeleton/swap_list.o
        PA/skeleton/system.cpp
        PA/skeleton/system.h
        PA/skeleton/system.o
        PA/skeleton/test.cpp
        PA/skeleton/wait_list.cpp
        PA/skeleton/wait_list.h
        PA/skeleton/wait_list.o)
