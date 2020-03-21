#define DECISION_NODE_FREQUENCY 10


enum dirEnum {DIR_STOP,
              DIR_FORWARD,
              DIR_BACKWARD
               };
enum soundEnum {SHORT_WHISTLE,
                LONG_WHISTLE,
                START,
                STOP,
                PASS_FAST,
                PASS_MED,
                PASS_SLOW
               };

#define POINT_1_PIN 4
#define POINT_2_PIN 2
#define POINT_1_STRAIGHT 100 //in range 0-255
#define POINT_2_STRAIGHT 177 //in range 0-255
#define POINT_1_TURN 140 //in range 0-255
#define POINT_2_TURN 110//in range 0-255
#define SOUND_DIR "model_train_control/resources/sound"
