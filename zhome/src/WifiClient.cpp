//
// Created by Avi Zrachya on 18/11/2016.
//

#include "WifiClient.h"
#include "Event.h"
#include "Configuration.h"
#include "Utils.h"
#include <ESP8266WiFi.h>
#include <ArduinoLog.h>


WifiClient::WifiClient() {
    Event::subscribe("WifiClient::onSetup", ON_SETUP, std::bind(&WifiClient::onSetup, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("WifiClient::onLoop", ON_LOOP, std::bind(&WifiClient::onLoop, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("WifiClient::onConfigurationChanged", ON_CONFIGURATION_CHANGED, std::bind(&WifiClient::onConfigurationChanged, this, std::placeholders::_1, std::placeholders::_2));

}

void WifiClient::setDefaults() {
    strcat(wifiHost, Utils::getUniqueDeviceId().c_str());

}

void WifiClient::onSetup(int eventId, void *data) {
    setDefaults();
}


void WifiClient::onLoop(int eventId, void *data) {
    connectIfDisconnected();
    logStatusIfChanged();
}

void WifiClient::onConfigurationChanged(int eventId, void *data) {
    //std::unordered_map<std::string, boolean> *changed = static_cast<std::unordered_map<std::string, boolean> *>(data);
    if(Config.fields.wifi_password.length() || Config.fields.wifi_ssid.length()) {
        reconnect();
    }
}

void WifiClient::connectIfDisconnected() {
    if(!connected() && connectTimeElapsed() > 30) {
        connect();
    }
}

void WifiClient::logStatusIfChanged() {
    if(statusChanged()) {
        logStatus();
    }
}

void WifiClient::connect() {
    Log.notice("Connecting host: [%s] ssid: [%s] password: [%s]]\n", wifiHost, Config.fields.wifi_ssid.c_str(), Config.fields.wifi_password.c_str());
    WiFi.disconnect();
    WiFi.hostname(wifiHost);
    WiFi.mode(WIFI_STA);
    WiFi.begin(Config.fields.wifi_ssid.c_str(), Config.fields.wifi_password.c_str());
    connectTimeStart();
}

bool WifiClient::connected() {
    return WiFi.isConnected();
}

time_t WifiClient::connectTimeElapsed() {
    return time(NULL) - this->timeConnected;
}


time_t WifiClient::connectTimeStart() {
    return this->timeConnected = time(NULL);
}

bool WifiClient::statusChanged() {
    bool statusChanged = (lastStatus != WiFi.status());
    lastStatus = WiFi.status();
    return statusChanged;
}

void WifiClient::logStatus() {
    switch(WiFi.status()) {
        case WL_CONNECTED:
            Log.notice("WifiClient: Connected to [SSID:%s] [IP:%s]\n", Config.fields.wifi_ssid.c_str(), WiFi.localIP().toString().c_str());
            Event::publish(ON_WIFI_CONNECTED);
            break;
        case WL_CONNECT_FAILED:
            Log.error("WifiClient: Connection to [SSID:%s] failed\n", Config.fields.wifi_ssid.c_str());
            Event::publish(ON_WIFI_DISCONNECTED);
            break;
        case WL_CONNECTION_LOST:
            Log.error("WifiClient: Connection to [SSID:%s] lost\n", Config.fields.wifi_ssid.c_str());
            Event::publish(ON_WIFI_DISCONNECTED);
            break;
        case WL_DISCONNECTED:
            Log.error("WifiClient: Disconnected from [SSID:%s]\n", Config.fields.wifi_ssid.c_str());
            Event::publish(ON_WIFI_DISCONNECTED);
            break;
        default:
            Log.notice("WifiClient: Status changed to %d for [SSID:%s]\n", WiFi.status(), Config.fields.wifi_ssid.c_str());
    }
}

void WifiClient::reconnect() {
    connect();
}


