//
// Created by Avi Zrachya on 18/11/2016.
//

#include <ESP8266mDNS.h>
#include "ZDeviceApp.h"

#include <ArduinoLog.h>


ZDeviceApp *app;

void setup() {
    Serial.begin(9600);
    Log.begin(LOG_LEVEL_NOTICE, &Serial);

    Log.notice("Initialazing\n");
    app = new ZDeviceApp();
    app->onSetup();
}

void loop() {
    app->onLoop();
}