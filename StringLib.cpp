//
// Created by Mogician on 2022/5/1.
//

#include "StringLib.h"

namespace MUD{
    StringVec split(std::string s,char c){
        int pos;
        StringVec sv;
        while ((pos=s.find(c))!=s.npos && s.length()){
            sv.push_back(s.substr(0,pos));
            s.erase(0,pos+1);
        }
        sv.push_back(s);
        StringVec::iterator it;
        sv.erase(std::remove(sv.begin(),sv.end(),""),sv.end());
        return sv;
    }
}
