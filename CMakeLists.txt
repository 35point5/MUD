cmake_minimum_required(VERSION 3.22)
project(Project)

set(CMAKE_EXE_LINKER_FLAGS)

set(CMAKE_CXX_STANDARD 20)

link_directories(/usr/local/lib64)
#link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/include/mysql++)
include_directories(/usr/include/mysql)
#include_directories(${PROJECT_SOURCE_DIR}/include/mysql++)
#include_directories(${PROJECT_SOURCE_DIR}/include/mysql)
#include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Project main.cpp Timer.cpp Timer.h Room.cpp Room.h entity/Player.cpp entity/Player.h entity/Entity.cpp entity/Entity.h Game.cpp Game.h entity/Item.cpp entity/Item.h Generator.cpp Generator.h StringLib.cpp StringLib.h Supplier.cpp Supplier.h socket/Socket.cpp socket/Socket.h socket/DataSocket.cpp socket/DataSocket.h socket/ListenSocket.cpp socket/ListenSocket.h socket/Connection.h socket/Telnet.cpp socket/Telnet.h socket/ConnectionHandler.h socket/SocketSet.cpp socket/SocketSet.h socket/ConnectionManager.h socket/ListenManager.h MUDException.cpp MUDException.h Database.cpp Database.h entity/Creature.cpp entity/Creature.h entity/Mob.cpp entity/Mob.h Recover.cpp Recover.h entity/Dog.cpp entity/Dog.h entity/Key.cpp entity/Key.h entity/Beast.cpp entity/Beast.h entity/Gun.cpp entity/Gun.h entity/Food.cpp entity/Food.h)

target_link_libraries(Project libglog.so mysqlpp boost_serialization)