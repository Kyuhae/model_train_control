#ifndef GLOBALS_H
#define GLOBALS_H
#include "stdlib.h"
#include <vector>
#include <string>

#define DECISION_NODE_FREQUENCY 10

#define POINT_1_PIN 4
#define POINT_2_PIN 2
#define POINT_1_STRAIGHT 100 //in range 0-255
#define POINT_2_STRAIGHT 177 //in range 0-255
#define POINT_1_TURN 140 //in range 0-255
#define POINT_2_TURN 110//in range 0-255
#define SOUND_DIR "/home/phil/catkin_ws/src/model_train_control/resources/sound"

enum dirEnum {DIR_STOP,
              DIR_FORWARD,
              DIR_BACKWARD
             };

enum soundEnum {SND_SHORT_WHISTLE,
                SND_LONG_WHISTLE,
                SND_ACCELERATE,
                SND_DECELERATE,
                SND_PASS_FAST,
                SND_PASS_MED,
                SND_PASS_SLOW
               };

enum StateEnum {STATE_IDLE,
                STATE_STATION_DEPART,
                STATE_STATION_ARRIVE,
                STATE_CRUISE

                };

typedef struct s_Sound {
    std::string path;
    int duration; //in seconds
} Sound;




#endif //GLOBALS_H
