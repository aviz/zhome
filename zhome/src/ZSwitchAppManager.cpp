//
// Created by Avi Zrachya on 19/11/2016.
//

#include "ZSwitchAppManager.h"
#include "WifiClient.h"
#include "WifiAP.h"
#include "WebServer.h"
#include "Configuration.h"
#include "WifiLedIndicator.h"
#include "Settings.h"
#include "Gang.h"
#include "Key.h"
#include "MQTT.h"

ZSwitchAppManager::ZSwitchAppManager() : AppManager() {
    globals.push_back(&Config);
    globals.push_back(&WebServer::getInstance());
    globals.push_back(new WifiClient());
    globals.push_back(new WifiAP());
    globals.push_back(new MQTT());
    globals.push_back(new WifiLedIndicator(GPIO_LED1));
    globals.push_back(new Gang("KEY1", GPIO_REL1));
    globals.push_back(new Gang("KEY2", GPIO_REL2));
    globals.push_back(new Gang("KEY3", GPIO_REL3));
    globals.push_back(new Key("KEY1", GPIO_KEY1));
    globals.push_back(new Key("KEY2", GPIO_KEY2));
    globals.push_back(new Key("KEY3", GPIO_KEY3));
}

