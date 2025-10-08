cmake_minimum_required(VERSION 3.31)
project(hospital)

set(CMAKE_CXX_STANDARD 20)

add_executable(hospital
        interface.cpp
        patient_list.cpp
        patient.cpp
        history.cpp
)
