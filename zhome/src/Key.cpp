//
// Created by Avi Zrachya on 01/07/2018.
//

#include <ArduinoLog.h>
#include "Key.h"
#include "Event.h"



Key::Key(std::string gangId, uint8_t keyPin) {
    lastKeyPinState = -1;
    setGangId(gangId);
    setKeyPin(keyPin);
    Event::subscribe("Key::onLoop", ON_LOOP, std::bind(&Key::onLoop, this, std::placeholders::_1, std::placeholders::_2));
}

void Key::onLoop(int eventId, void *data) {
    checkKeyState();
}

void Key::checkKeyState() {
    currentKeyPinState = digitalRead(keyPin);
    if (currentKeyPinState != lastKeyPinState) {
        lastKeyPinState = currentKeyPinState;
        onKeyStateChange();
    }
}

void Key::onKeyStateChange() {
    Log.notice("Key %s: %d\n", gangId.c_str(), currentKeyPinState);
    if (currentKeyPinState == PRESSED) {
        Event::publish(ON_KEY_TOGGLE, (void *)gangId.c_str());
    }
}

void Key::setGangId(std::string gangId) {
    Key::gangId = gangId;
}
void Key::setKeyPin(uint8_t keyPin) {
    this->keyPin = keyPin;
    pinMode(this->keyPin, INPUT_PULLUP);
}