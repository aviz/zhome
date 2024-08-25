//
// Created by Avi Zrachya on 01/07/2018.
//

#ifndef ZSWITCH_KEY_H
#define ZSWITCH_KEY_H

#include <string>

enum KeyState {
    PRESSED,
    UNPRESSED
};

class Key {
public:
    Key(std::string gangId, uint8_t keyPin);
    void setKeyPin(uint8_t keyPin);
    void setGangId(std::string gangId);

private:
    uint8_t keyPin;
    int currentKeyPinState;
    int lastKeyPinState;
    std::string gangId;

    void onLoop(int eventId, void *data);
    void checkKeyState();
    void onKeyStateChange();


};


#endif //ZSWITCH_KEY_H
