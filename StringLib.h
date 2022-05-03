//
// Created by Mogician on 2022/5/1.
//

#ifndef PROJECT_STRINGLIB_H
#define PROJECT_STRINGLIB_H

#include "string"
#include "vector"
#include "algorithm"

typedef std::vector<std::string> StringVec;
namespace MUD {
    StringVec split(std::string s,char c=' ');

}
#endif //PROJECT_STRINGLIB_H
