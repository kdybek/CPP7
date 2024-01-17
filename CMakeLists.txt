cmake_minimum_required(VERSION 3.22)
project(CPP7)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(CPP7
        surfaces.h
        example.cc
        ps_plot.cc
        ps_plot.h
        real.h)
