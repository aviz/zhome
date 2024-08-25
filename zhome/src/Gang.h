//
// Created by Avi Zrachya on 28/04/2018.
//

#ifndef ZSWITCH_GANG_H
#define ZSWITCH_GANG_H

#include <string>

enum GangState {
    ON,
    OFF
};


class Gang {
private:
    GangState state;
    std::string id;
    uint8_t relayPin;
    void setState(GangState state);
    void publishState();
    void updateRelay();
    void onGangToggle(int eventId, void *data);
    void onSwitchCmd(int eventId, void *data);


    void toggleState();


public:
    Gang(std::string id, uint8_t relayPin);
    void setId(std::string &id);

    const std::string &getId() const;

    void setRelayPin(uint8_t relayPin);

};


#endif //ZSWITCH_GANG_H
