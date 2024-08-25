//
// Created by Avi Zrachya on 17/03/2018.
//

#ifndef ZSWITCH_EVENT_H
#define ZSWITCH_EVENT_H

#include <unordered_map>
#include <list>
#include <functional>
#include "Events.h"
#include <string>
#include <ArduinoLog.h>

typedef std::function<void(int eventId, void *data)> EventCb;

class Event {

public:
    static Event *instance;
    static Event& getInstance() {
        if (instance == nullptr) {
            instance = new Event();
        }
        return *instance;
    }

    static void setInstance(Event* i) {
        instance = i;
    }

    static void subscribe(std::string caller, int eventId, EventCb cb);
    static void publish(int eventId, void* data = nullptr);
    virtual void _subscribe(std::string caller, int eventId, EventCb cb);
    virtual void _publish(int eventId, void* data);

    class subscription {
    public:
        subscription(std::string caller, EventCb cb) : cb(cb), caller(caller) {}
        EventCb cb;
        std::string caller;
    };

private:
    std::unordered_map<int, std::list<subscription*>*> eventSubscribers;

};

#endif //ZSWITCH_EVENT_H
