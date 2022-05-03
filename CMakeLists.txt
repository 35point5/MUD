cmake_minimum_required(VERSION 3.22)
project(Project)

set(CMAKE_EXE_LINKER_FLAGS -static)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project main.cpp Timer.cpp Timer.h Room.cpp Room.h Player.cpp Player.h Entity.cpp Entity.h Game.cpp Game.h Item.cpp Item.h Generator.cpp Generator.h StringLib.cpp StringLib.h Supplier.cpp Supplier.h)
