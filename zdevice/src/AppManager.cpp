//
// Created by Avi Zrachya on 19/11/2016.
//

#include "AppManager.h"
#include "Event.h"
#include <Esp.h>
#include <ArduinoLog.h>

void AppManager::onSetup() {
    Log.notice("-----------------------------\n");
    Log.notice("          App Setup\n");
    Log.notice("-----------------------------\n");
    Event::publish(ON_INIT);
    Event::publish(ON_SETUP);


}

void AppManager::onLoop() {
    Event::publish(ON_LOOP);
}

AppManager::AppManager() {

}
