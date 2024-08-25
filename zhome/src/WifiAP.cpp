//
// Created by Avi Zrachya on 19/11/2016.
//

#include "WifiAP.h"
#include <ESP8266WiFi.h>
#include <ArduinoLog.h>
#include "Configuration.h"
#include "Event.h"
#include "Utils.h"

WifiAP::WifiAP() {
    Event::subscribe("WifiAP::onSetup", ON_SETUP, std::bind(&WifiAP::onSetup, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("WifiAP::onLoop", ON_LOOP, std::bind(&WifiAP::onLoop, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("WifiAP::onConfigurationChanged", ON_CONFIGURATION_CHANGED, std::bind(&WifiAP::onConfigurationChanged, this, std::placeholders::_1, std::placeholders::_2));
}

void WifiAP::setDefaults() {
    ssid = Utils::getUniqueDeviceId();

    // override from config.
    if (Config.fields.ap_ssid.length() > 0) {
        ssid = Config.fields.ap_ssid;
    }

    password = Config.fields.ap_password;
}

void WifiAP::onConfigurationChanged(int eventId, void *data) {

}

void WifiAP::onLoop(int eventId, void *data) {

}

void WifiAP::onSetup(int eventId, void *data) {
    setDefaults();
    WiFi.softAP(ssid.c_str(), password.c_str());
    IPAddress myIP = WiFi.softAPIP();

    Log.notice("AP: [%s] IP: [%s]\n", ssid.c_str(), myIP.toString().c_str());
}