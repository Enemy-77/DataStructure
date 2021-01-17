cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tools/cmake/")
include(Macro)

PROJECT(DataStructure)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

INCLUDE_DIRECTORIES(src)
ADD_SUBDIRECTORY(src bin)
ADD_SUBDIRECTORY(test)