//
// Created by Avi Zrachya on 28/04/2018.
//

#include <Arduino.h>
#include <ArduinoLog.h>
#include "Configuration.h"
#include "Event.h"
#include "Gang.h"
#include "Gangs.h"
#include "SwitchEvent.h"


Gang::Gang(std::string id, uint8_t relayPin) {
    setId(id);
    setRelayPin(relayPin);
    Event::subscribe("Gang::onGangToggle", ON_KEY_TOGGLE, std::bind(&Gang::onGangToggle, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("Gang::onSwitchCmd", ON_SWITCH_CMD, std::bind(&Gang::onSwitchCmd, this, std::placeholders::_1, std::placeholders::_2));
}

void Gang::setState(GangState state) {
    this->state = state;
    updateRelay();
    publishState();
}

void Gang::setId(std::string &id) {
    Gangs::remove(this);
    this->id = id;
    Gangs::add(this);
}

void Gang::setRelayPin(uint8_t relayPin) {
    this->relayPin = relayPin;
    pinMode(this->relayPin, OUTPUT);
}

void Gang::toggleState() {
    (state == ON) ? setState(OFF) : setState(ON);
}

const std::string &Gang::getId() const {
    return id;
}

void Gang::publishState() {
    SwitchEvent switchEvent;
    switchEvent.setState(this->state);
    switchEvent.setId(this->id);
    Event::publish(ON_SWITCH_STATE, (void *)&switchEvent);
}

void Gang::onGangToggle(int eventId, void *data) {
    if(this->id == ((char *)data)) {
        toggleState();
    }
}
void Gang::onSwitchCmd(int eventId, void *data) {
    auto *switchEvent = (SwitchEvent *)data;
    if(switchEvent->getId() == this->id) {
        setState(switchEvent->getState());
    }
}

void Gang::updateRelay() {
    Log.notice("%s Updating relay %s\n", id.c_str(), this->state == ON ? "ON" : "OFF");
    digitalWrite(relayPin, (uint8_t) (this->state == ON ? HIGH : LOW));
}

