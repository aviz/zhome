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


typedef std::function<void(int eventId, void *data)> EventCb;


class Event {

public:
    static Event &getInstance() {
        static Event instance;
        return instance;
    }
    static void subscribe(std::string caller, int eventId, EventCb cb);
    static void publish(int eventId, void *data = nullptr);
    void _subscribe(std::string caller, int eventId, EventCb cb);
    void _publish(int eventId, void *data);

    class subscription {
    public:
        subscription(std::string caller, EventCb cb) : cb(cb), caller(caller) {}
        EventCb cb;
        std::string caller;
    };

private:
    std::unordered_map<int, std::list<subscription *> *> eventSubscribers;

};


#endif //ZSWITCH_EVENT_H
