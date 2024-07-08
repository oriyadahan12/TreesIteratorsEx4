#oriyati0701@gmail.com

cmake_minimum_required(VERSION 3.28)
project(TreesIterators.cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(TreesIterators main.cpp
        Tree.cpp
        Tree.hpp
        Complex.cpp
        Complex.hpp
        Testing.cpp
        doctest.h
        GUI.cpp
        GUI.hpp
)
