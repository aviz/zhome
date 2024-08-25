//
// Created by Avi Zrachya on 12/07/2018.
//

#ifndef ZSWITCH_SWITCHEVENT_H
#define ZSWITCH_SWITCHEVENT_H


#include <string>
#include "Gang.h"

class SwitchEvent {
public:
    const std::string &getId() const;
    void setId(const std::string &id);
    GangState getState() const;
    void setState(GangState state);
    std::string getAction();
    void setAction(std::string action);

private:
    std::string id;
    GangState state;
};


#endif //ZSWITCH_SWITCHEVENT_H
