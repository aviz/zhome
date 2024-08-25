//
// Created by Avi Zrachya on 01/07/2018.
//

#include <ArduinoLog.h>
#include <unordered_map>
#include "Gangs.h"

std::unordered_map<std::string, Gang *> gangs;

void Gangs::add(Gang *gang) {
    gangs[gang->getId()] = gang;
}

void Gangs::remove(Gang *gang) {
    gangs[gang->getId()] = nullptr;
}

Gang *Gangs::find(std::string gangId) {
    Gang *gang = gangs[gangId];
    if (gang == nullptr) {
        Log.error("can't find gang id [%s]\n", gangId.c_str());
    }
    return gang;
}
