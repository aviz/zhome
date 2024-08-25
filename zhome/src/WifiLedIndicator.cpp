//
// Created by Avi Zrachya on 30/06/2018.
//

#include <Arduino.h>
#include <ArduinoLog.h>
#include "WifiLedIndicator.h"
#include "Event.h"

WifiLedIndicator::WifiLedIndicator(uint8_t ledPin) : ledPin(ledPin) {
    Event::subscribe("WifiLedIndicator::onWifiConnected", ON_WIFI_CONNECTED, std::bind(&WifiLedIndicator::onWifiConnected, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("WifiLedIndicator::onWifiDisConnected", ON_WIFI_DISCONNECTED, std::bind(&WifiLedIndicator::onWifiDisConnected, this, std::placeholders::_1, std::placeholders::_2));
    pinMode(ledPin, OUTPUT);
    turnLedOff();
}

void WifiLedIndicator::onWifiConnected(int eventId, void *data) {
   // Log.notice("Switch1: %d", digitalRead(this->switchPin));
    turnLedOn();
}

void WifiLedIndicator::onWifiDisConnected(int eventId, void *data) {
    turnLedOff();
}

void WifiLedIndicator::turnLedOn() {
    digitalWrite(this->ledPin, LOW);
}

void WifiLedIndicator::turnLedOff() {
    digitalWrite(this->ledPin, HIGH);
}
