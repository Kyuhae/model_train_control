#ifndef LOCO_H
#define LOCO_H

#include "globals.h"

class decision;

class Loco {

protected:
    //TODO: change this
    //ptr used to access useful info to update agents from perception callbacks
    decision *m_decision_node_ptr;

public:
    Loco(decision *decision_node_ptr);
    Sound getSound(soundEnum snd_type);
    int m_start_throttle = 154;
    int m_stop_throttle = 138;
    int m_cruise_throttle = 170;

    //br78 range [0;1]: 0.60 0.64   153 168.3



};

#endif // LOCO_H

