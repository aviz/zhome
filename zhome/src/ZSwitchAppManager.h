//
// Created by Avi Zrachya on 19/11/2016.
//

#ifndef ZSWITCH_ZSWITCHAPPMANAGER_H
#define ZSWITCH_ZSWITCHAPPMANAGER_H


#include <list>
#include "AppManager.h"

class ZSwitchAppManager : public AppManager {
    std::list<void *> globals;
public:
    ZSwitchAppManager();
};


#endif //ZSWITCH_ZSWITCHAPPMANAGER_H
