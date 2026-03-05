cmake_minimum_required(VERSION 3.10)

project(CPU)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPU
    main.cpp
    acumulador.cpp
    alu.cpp
    icr.cpp
    mar.cpp
    mdr.cpp
    memoria.cpp
    pc.cpp
    unidadControl.cpp
)