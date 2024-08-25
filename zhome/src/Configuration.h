//
// Created by Avi Zrachya on 24/11/2016.
//

#ifndef ZSWITCH_CONFIG_H
#define ZSWITCH_CONFIG_H


#include <string>
#include <map>
#include <functional>
#include <list>
#include <ArduinoJson.h>

#define MAX_PASS_LENGTH 16
#define MAX_SSID_LENGTH 128
#define MAX_VERSION 1

typedef struct {
    int version;
    std::string ap_password;
    std::string ap_ssid;
    std::string wifi_ssid;
    std::string wifi_password;
    std::string mqtt_host;
    std::string mqtt_topic;
} ConfigurationFields;


class Configuration {
private:
    bool saveToConfig();
    bool loadFromConfig();
    JsonDocument jsonDocument;

public:
    void save();

public:
    Configuration();

    void onInit(int eventId, void *data);
    void initializeValues();
    ConfigurationFields fields;

private:
    void serializeToString(std::string &out);
    void serializeToJsonDocument();
    void deserializeFromJsonDocument();

    void commit();
};

extern Configuration Config;

#endif //ZSWITCH_CONFIG_H

