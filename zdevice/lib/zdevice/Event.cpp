//
// Created by Avi Zrachya on 17/03/2018.
//

#include "Event.h"
#include <chrono>
#include <ArduinoLog.h>

Event* Event::instance = nullptr;

void Event::subscribe(std::string caller, int eventId, EventCb cb) {
    Event::getInstance()._subscribe(caller, eventId, cb);
}

void Event::publish(int eventId, void *data) {
    Event::getInstance()._publish(eventId, data);
}

void Event::_subscribe(std::string caller, int eventId, EventCb cb) {
    auto lst = eventSubscribers[eventId];
    if (lst == nullptr) {
        lst = new std::list<subscription *>();
        eventSubscribers[eventId] = lst;
    }
    auto s = new subscription(caller, cb);
    lst->push_back(s);
    Log.notice("SUBSCRIBING: %d\n", eventId);
}

void Event::_publish(int eventId, void *data) {
    Log.trace("PUBLISH: %d\n", eventId);
    auto lst = eventSubscribers[eventId];
    if (lst == nullptr) {
        Log.notice("NO SUBSCRIBERS FOR: %d\n", eventId);
        return;
    }
    Log.trace("SUBSCRIBERS FOR: %d\n", lst->size());
    for (std::list<subscription *>::const_iterator iterator = lst->begin(); iterator != lst->end(); ++iterator) {
        auto s = (*iterator);
        Log.trace("PUBLISHING: %d to %s\n", eventId, s->caller.c_str());
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        s->cb(eventId, data);
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
        auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        if (runtime > 2) {
            Log.error("PUBLISHING for [eventId:%d] [caller:%s] took %d ms\n", eventId, s->caller.c_str(), runtime);
        }
    }
    Log.trace("PUBLISHING DONE: %d\n", eventId);
}
