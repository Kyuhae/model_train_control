# model_train_control
## Overview
This repository contains my project to build software to control a model railway, using a pc and an arduino. The desctiption below will be tailored more towards a model-railway enthusiast than a software engineer.
The idea is that the arduino is connected to the electronics on the railway (track for locomotive power, servo motors to switch points, lights in buildings, etc). The adruino communicates with a pc via the serial interface (usb cable). The software running on the pc is what determines which commands should be sent to the arduino. The pc software also includes a Graphical User Interface (GUI), to provide the user with manual control over the railway. The pc software also allows for fully and semi-autonomous operation. The project assumes DC operation, where locomotives are NOT equipped with individual chips.  


## Features to be added:
- locomotive configuration tool: easy process to set values for minimum, maximum, and shunting speeds for each loco.
- preset actions for each locomotive: at the click of a button on the GUI, a train will accelerate to cruising speed, decelerate, stop, run around...
- integration of sensors for advanced automated operation
- add more sounds, both manual and as part of the preset actions


## DISCLAIMER
If you would like to use this project, please link to the model_train_control github repository page so that people may get information about the project should they need it.
Please also note that the settings for various electronics hardware are hard-coded for my own railway. Do not attempt to use the project with your own hardware / railway without understanding what you should change in order to avoid damaging your components. If you would like to use parts of this project, but are not sure how, feel free to ask questions at philip(dot)scales21(at)gmail(dot)com, or in the "issues" tab on the github repository page.
