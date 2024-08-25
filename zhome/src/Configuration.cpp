//
// Created by Avi Zrachya on 24/11/2016.
//

#include "Configuration.h"
#include "Event.h"
#include <FS.h>
#include <LittleFS.h>
#include <WString.h>
#include <ArduinoLog.h>


void Configuration::onInit(int eventId, void *data) {
    LittleFS.begin();
    initializeValues();
    // bind("version", fields.version);
    // bind("ap_password", fields.ap_password);
    // bind("ap_ssid", fields.ap_ssid);
    // bind("wifi_ssid", fields.wifi_ssid);
    // bind("wifi_password", fields.wifi_password);
    // bind("mqtt_host", fields.mqtt_host);
    // bind("mqtt_topic", fields.mqtt_topic);
    Log.notice("-----------------------------\n");
    Log.notice("      Configuration Init     \n");
    Log.notice("-----------------------------\n");
    loadFromConfig();
    initializeValues();
    save();

}



void Configuration::initializeValues() {
    fields.version = MAX_VERSION;
    fields.ap_password = "Admin";
    fields.ap_ssid = "admin";
    fields.wifi_ssid = "ZrachyaWifi";
    fields.wifi_password = "19021952";
    fields.mqtt_host = "192.168.1.10";
    fields.mqtt_topic = "zhome";
}

bool Configuration::loadFromConfig() {
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile) {
        Log.error("Failed to open config file\n");
        return false;
    }

    size_t size = configFile.size();

    char *file_content = (char *) malloc(size);

    if (file_content == NULL) {
        Log.error("Allocation error\n");
        return false;
    }

    configFile.readBytes(file_content, size);
    file_content[size] = '\0';

    Log.notice("Configuration: [%s]\n", file_content);

    deserializeJson(jsonDocument, file_content);
    free(file_content);

    return true;
}

bool Configuration::saveToConfig() {
    fields.version = MAX_VERSION;

    File config_file = LittleFS.open("/config.json", "w");
    if (!config_file) {
        Log.error("Failed to open config file for writing\n");
        return false;
    }

    serializeJson(jsonDocument, config_file);
    config_file.close();

    return true;
}

void Configuration::save() {
    Log.notice("Configuration::save() called\n");
    serializeToJsonDocument();
    Log.notice("Configuration::save() publish event\n");
    Event::publish(ON_CONFIGURATION_CHANGED);
    Log.notice("Configuration::save() commiting changes\n");
    saveToConfig();
}

Configuration::Configuration() {
    Event::subscribe("Configuration::onInit", ON_INIT, std::bind(&Configuration::onInit, this, std::placeholders::_1, std::placeholders::_2));
}

void Configuration::serializeToJsonDocument() {
    jsonDocument["version"] = fields.version;
    jsonDocument["ap_password"] = fields.ap_password;
    jsonDocument["ap_ssid"] = fields.ap_ssid;
    jsonDocument["wifi_ssid"] = fields.wifi_ssid;
    jsonDocument["wifi_password"] = fields.wifi_password;
    jsonDocument["mqtt_host"] = fields.mqtt_host;
    jsonDocument["mqtt_topic"] = fields.mqtt_topic;
}

void Configuration::deserializeFromJsonDocument() {
    fields.version = jsonDocument["version"];
    fields.ap_password = jsonDocument["ap_password"].as<std::string>();
    fields.ap_ssid = jsonDocument["ap_ssid"].as<std::string>();
    fields.wifi_ssid = jsonDocument["wifi_ssid"].as<std::string>();
    fields.wifi_password = jsonDocument["wifi_password"].as<std::string>();
    fields.mqtt_host = jsonDocument["mqtt_host"].as<std::string>();
    fields.mqtt_topic = jsonDocument["mqtt_topic"].as<std::string>();
}
Configuration Config;
