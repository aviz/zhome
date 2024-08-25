//
// Created by Avi Zrachya on 02/07/2018.
//

#include "MQTT.h"
#include "Event.h"
#include "Configuration.h"
#include "Utils.h"
#include "SwitchEvent.h"
#include <PubSubClient.h>
#include <ArduinoLog.h>


MQTT::MQTT() : client(wifiClient) {
    Event::subscribe("MQTT::onLoop", ON_LOOP, std::bind(&MQTT::onLoop, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("MQTT::onSetup", ON_SETUP, std::bind(&MQTT::onSetup, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("MQTT::onWifiConnect", ON_WIFI_CONNECTED, std::bind(&MQTT::onWifiConnect, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("MQTT::onSwitchState", ON_SWITCH_STATE, std::bind(&MQTT::onSwitchState, this, std::placeholders::_1, std::placeholders::_2));
}

void MQTT::onLoop(int eventId, void *data) {
    if(!connected() && connectTimeElapsed() > 30) {
        connect();
    }
    if(connected()) {
        client.loop();
    }
}

void MQTT::onWifiConnect(int eventId, void *data) {
    connect();
}

void MQTT::onSetup(int eventId, void *data) {
    setupTopics();
    client.setServer(Config.fields.mqtt_host.c_str(), 1883);
}


bool MQTT::connected() {
    return client.connected();
}

void MQTT::connect() {
    Log.notice("Connecting to mqtt host: [%s]\n", Config.fields.mqtt_host.c_str());
    client.disconnect();
    client.setCallback(std::bind(&MQTT::onConsume, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    client.connect(Utils::getUniqueDeviceId().c_str());
    client.subscribe(commands_topic.c_str());
    connectTimeStart();
}

time_t MQTT::connectTimeElapsed() {
    return time(nullptr) - this->timeConnected;
}


time_t MQTT::connectTimeStart() {
    return this->timeConnected = time(nullptr);
}

void MQTT::onConsume(char* topic, byte* payload, unsigned int length) {
    std::string command(reinterpret_cast<char*>(payload), length);
    SwitchEvent switchEvent;
    switchEvent.setAction(command);
}

void MQTT::onSwitchState(int eventId, void *data) {
    auto *switchEvent = (SwitchEvent *)data;
    client.publish(this->status_topic.c_str(), switchEvent->getAction().c_str());
}

void MQTT::setupTopics() {
    setupIncomingTopic();
    setupOutgoingTopic();
}

void MQTT::setupIncomingTopic() {
    commands_topic = Config.fields.mqtt_topic + "zswitch/commands/" + Utils::getUniqueDeviceId();
}

void MQTT::setupOutgoingTopic() {
    status_topic = Config.fields.mqtt_topic + "zswitch/status/" + Utils::getUniqueDeviceId();
}
