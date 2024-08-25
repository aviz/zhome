//
// Created by Avi Zrachya on 30/06/2018.
//

#ifndef ZSWITCH_WIFILEDINDICATOR_H
#define ZSWITCH_WIFILEDINDICATOR_H


#include <cstdint>

class WifiLedIndicator {
public:
    WifiLedIndicator(uint8_t ledPin);


private:
    uint8_t ledPin;
    void onWifiConnected(int eventId, void *data);
    void onWifiDisConnected(int eventId, void *data);
    void turnLedOn();
    void turnLedOff();
};


#endif //ZSWITCH_WIFILEDINDICATOR_H
