//
// Created by Avi Zrachya on 19/11/2016.
//

#ifndef ZSWITCH_WIFIAP_H
#define ZSWITCH_WIFIAP_H


#include <string>


class WifiAP {
public:
    WifiAP();

    void onLoop(int eventId, void *data);
    void onSetup(int eventId, void *data);
    void onConfigurationChanged(int eventId, void *data);
    void setDefaults();

private:
    std::string ssid;
    std::string password;
};


#endif //ZSWITCH_WIFIAP_H
