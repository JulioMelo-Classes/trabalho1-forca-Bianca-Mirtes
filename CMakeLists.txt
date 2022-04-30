cmake_minimum_required(VERSION 3.5)
project(all_any_none_program VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )

#--------------------------------
# This is for old cmake versions
#set (CMAKE_CXX_STANDARD 14)
#--------------------------------

### [1] Application target
# configura o diretório contendo os .h, assim você pode incluílos apenas com include "arquivo.h"
include_directories( include )

### [2] Test engine
# includes do test manager

# Cria um executável com nome "program" com base no main.cpp
set( APP_NAME "program" )
add_executable( ${APP_NAME}
                src/main.cpp
                src/forca.cpp )
                

# The end
