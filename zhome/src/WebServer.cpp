//
// Created by Avi Zrachya on 02/12/2016.
//


#include "WebServer.h"
#include "Event.h"
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ArduinoLog.h>
#include <LittleFS.h>
#include <FS.h>
#include "Configuration.h"


WebServer::WebServer() : server(80) {
    Log.notice("WebServer Created\n");
    Event::subscribe("WebServer::onSetup", ON_SETUP, std::bind(&WebServer::onSetup, this, std::placeholders::_1, std::placeholders::_2));
    Event::subscribe("WebServer::onLoop", ON_LOOP, std::bind(&WebServer::onLoop, this, std::placeholders::_1, std::placeholders::_2));
}

void WebServer::onSetup(int eventId, void *data) {
    server.on("/var", HTTP_POST, [](){
        WebServer::getInstance().onHandleSetVar();
    });

    server.on("/key/toggle/1", HTTP_POST, [](){
                Event::publish(ON_KEY_TOGGLE, (void *)"1");
    });

    server.serveStatic("/index.htm", LittleFS, "/index.htm");
    server.serveStatic("/fonts", LittleFS, "/fonts", "max-age=86400");
    server.serveStatic("/js", LittleFS, "/js");
    server.serveStatic("/css", LittleFS, "/css", "max-age=86400");
    server.serveStatic("/images", LittleFS, "/images", "max-age=86400");
    server.serveStatic("/", LittleFS, "/index.htm");

    server.onNotFound([]() {
        WebServer::getInstance().onHandleNotFound();
    });
    server.begin();
}

void WebServer::onLoop(int eventId, void *data) {
    server.handleClient();
}

void WebServer::onHandleSetVar() {
    String name = server.arg("name");
    String value = server.arg("value");
    Log.notice("onHandleSetVar [name:%s] [value:%s]\n", name.c_str(), value.c_str());

    Config.fields.wifi_password = "dada";
    Config.save();
    JsonDocument jsonDocument;
    JsonObject json = jsonDocument.to<JsonObject>();

   // JsonObject& data = json.createNestedObject("data");



    String responsJson;
    serializeJson(json, responsJson);

    server.send ( 200, "text/json", responsJson);
}


void WebServer::onHandleNotFound() {
    Log.notice("onHandleNotFound called\n");
    server.send ( 404, "text/plain", "not found" );
}





