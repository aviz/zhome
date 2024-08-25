//
// Created by Avi Zrachya on 12/07/2018.
//

#include "SwitchEvent.h"
#include "Utils.h"
#include <string>
const std::string &SwitchEvent::getId() const {
    return id;
}

void SwitchEvent::setId(const std::string &id) {
    SwitchEvent::id = id;
}

GangState SwitchEvent::getState() const {
    return state;
}

void SwitchEvent::setState(GangState state) {
    SwitchEvent::state = state;
}

std::string SwitchEvent::getAction() {
    return this->id + (state == ON ? ":ON" : ":OFF");
}

void SwitchEvent::setAction(std::string action) {
    auto splits = Utils::split(action, ':');
    id = splits[0];
    state = (splits[1] == "ON" ? ON : OFF);
}
