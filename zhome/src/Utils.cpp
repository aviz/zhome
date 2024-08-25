//
// Created by Avi Zrachya on 02/07/2018.
//

#include <ESP8266WiFi.h>
#include "Utils.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

std::string Utils::getUniqueDeviceId() {
    char wifiHost[32] = {0};
    uint8_t mac[6];

    WiFi.macAddress((uint8_t *) &mac);
    sprintf(wifiHost, "ZSwitch-%02X.%02X.%02X.%02X.%02X.%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return std::string(wifiHost);
}


template<typename Out>
void splits(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> Utils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    splits(s, delim, std::back_inserter(elems));
    return elems;
}
