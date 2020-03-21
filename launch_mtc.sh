#/bin/bash
export ROS_MASTER_URI=http://localhost:11311;
export ROS_IP=127.0.0.1;
xterm -fa monaco -fs 13 -bg black -fg white -e "roscore;/bin/bash" &
xterm -fa monaco -fs 13 -bg black -fg white -e "rosrun mtc_logic mtc_l_decision_node;/bin/bash" &
sleep 2
xterm -fa monaco -fs 13 -bg black -fg white -e "rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=9600;/bin/bash" &

xinput=`xinput --list | grep 'Wacom'`
echo $xinput
if [ "$xinput" == "" ]
then
    echo "[mtc] Launching ui in xterm"
    xterm -fa monaco -fs 13 -bg black -fg white -e "rosrun mtc_ui mtc_ui;/bin/bash" &
else
    echo "[mtc] Launching ui in Xephyr session"
    Xephyr :1 -screen 1000x1000 &
    DISPLAY=:1 rosrun mtc_ui mtc_ui
fi


echo "[mtc] Model Train Control is running. ctrl+c to kill all terminals"

input=""
while [ 1 ]
do
    read input
done
