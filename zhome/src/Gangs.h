//
// Created by Avi Zrachya on 01/07/2018.
//

#ifndef ZSWITCH_GANGS_H
#define ZSWITCH_GANGS_H


#include <string>
#include <unordered_map>
#include "Gang.h"

class Gangs {
public:
    static void add(Gang *gang);
    static void remove(Gang *gang);
    static Gang *find(std::string gangId);
};


#endif //ZSWITCH_GANGS_H
