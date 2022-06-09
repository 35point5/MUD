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
    std::string name,description;
    int id;
    static int entityCnt;
    //static std::map<int,Entity*> entityMap;
public:
    Entity() : name("Undefined"), id(entityCnt++),description("") {}

    inline std::string GetName() { return name; }

    inline int GetID() const { return id; }

    inline std::string GetDescription(){return description;}

    inline void Rename(std::string s){name=s;}
};

}


#endif //PROJECT_ENTITY_H
