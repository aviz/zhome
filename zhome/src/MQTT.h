//
// Created by Avi Zrachya on 02/07/2018.
//

#ifndef ZSWITCH_MQTT_H
#define ZSWITCH_MQTT_H
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ctime>
#include <string>

class MQTT {
public:
    MQTT();

private:
    WiFiClient wifiClient;
    PubSubClient client;
    time_t timeConnected;
    std::string commands_topic;
    std::string status_topic;

    void onSwitchState(int eventId, void *data);
    void onLoop(int eventId, void *data);
    void onSetup(int eventId, void *data);
    void onWifiConnect(int eventId, void *data);
    void onConsume(char* topic, byte* payload, unsigned int length);
    void setupTopics();
    void setupIncomingTopic();
    void setupOutgoingTopic();
    void connect();
    bool connected();
    time_t connectTimeElapsed();
    time_t connectTimeStart();
};


#endif //ZSWITCH_MQTT_H
