#include "loco.h"
#include "decision_node.h"
#include <stdio.h>



Loco::Loco(decision *decision_node_ptr) {
    //add loco type as a parameter
    //add a loco_sounds data structure to be switched out when new loco is loaded
    //need to have two or three loco profiles available (one controlled loco, and several other locos which might also be on the layout, stationary.
    //remember you'll have sounds not associated to a loco.
    m_decision_node_ptr = decision_node_ptr;
}

// add a utility for this agent
Sound Loco::getSound(soundEnum snd_type) {
    //todo: read these from file
    Sound s;
    char sound_dir[100]; // MAKE THIS BIG ENOUGH!
    sprintf(sound_dir, "%s", SOUND_DIR);
    switch(snd_type) {
    case SND_ACCELERATE:
        s.duration = 62;
        s.path = sound_dir + std::string("/t18/t18_approach_exhaust_beat_long_pass_coaches.flac");
        break;

    case SND_DECELERATE:
        s.duration = 18;
        s.path = sound_dir + std::string("/t18/t18_arrival_hiss_brake_squeak_talking.flac");
        break;

    case SND_SHORT_WHISTLE:

        break;

    case SND_LONG_WHISTLE:
        s.duration = 2;
        s.path = sound_dir + std::string("/t18/t18_whistle_med.flac");
        break;

    case SND_PASS_MED:
        s.duration = 31;
        s.path = sound_dir + std::string("/t18/t18_fast_approach.flac");
        break;
    }
    return s;
}

