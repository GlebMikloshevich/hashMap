cmake_minimum_required(VERSION 3.17)
project(hashMap)

set(CMAKE_CXX_STANDARD 17)

add_executable(hashMap main.cpp HashMapItem.cpp HashMapItem.h OpenHashMap.cpp OpenHashMap.h CloseHashMap.cpp CloseHashMap.h)