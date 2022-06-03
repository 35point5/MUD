cmake_minimum_required(VERSION 3.22)
project(Project)

set(CMAKE_EXE_LINKER_FLAGS)

set(CMAKE_CXX_STANDARD 20)

link_directories(/usr/local/lib64)

include_directories(/usr/local/include/mysql++)
include_directories(/usr/include/mysql)

add_executable(Project main.cpp Timer.cpp Timer.h Room.cpp Room.h Player.cpp Player.h Entity.cpp Entity.h Game.cpp Game.h Item.cpp Item.h Generator.cpp Generator.h StringLib.cpp StringLib.h Supplier.cpp Supplier.h Socket.cpp Socket.h DataSocket.cpp DataSocket.h ListenSocket.cpp ListenSocket.h Connection.h Telnet.cpp Telnet.h ConnectionHandler.h SocketSet.cpp SocketSet.h ConnectionManager.h ListenManager.h MUDException.cpp MUDException.h Database.cpp Database.h)

target_link_libraries(Project libglog.so mysqlpp boost_serialization)