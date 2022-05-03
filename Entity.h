//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_ENTITY_H
#define PROJECT_ENTITY_H


#include <string>
#include "map"
namespace MUD{
class Entity {
protected:
    std::string name;
    int id;
    static int entityCnt;
    //static std::map<int,Entity*> entityMap;
public:
    Entity() : name("Undefined"), id(entityCnt++) {}

    inline std::string Name() { return name; }

    inline int ID() const { return id; }
};

}


#endif //PROJECT_ENTITY_H
