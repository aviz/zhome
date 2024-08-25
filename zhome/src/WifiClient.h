//
// Created by Avi Zrachya on 18/11/2016.
//

#ifndef ZSWITCH_WIFICLIENT_H
#define ZSWITCH_WIFICLIENT_H


#include <WString.h>
#include <ctime>


class WifiClient {
public:
    WifiClient();
    void onConfigurationChanged(int eventId, void *data);
    void onLoop(int eventId, void *data);
    void onSetup(int eventId, void *data);

private:
    char wifiHost[32] = {0};
    time_t timeConnected;
    uint8_t lastStatus;

    void connect();
    bool connected();
    time_t connectTimeElapsed();
    time_t connectTimeStart();
    void logStatus();
    bool statusChanged();
    void setDefaults();

    void logStatusIfChanged();
    void reconnect();
    void connectIfDisconnected();
};


#endif //ZSWITCH_WIFICLIENT_H
