import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Rectangle {
    color: "white"
    property alias loco_select: loco_select
    width: 1000 //Screen.desktopAvailableWidth
    height: 1000 //Screen.desktopAvailableHeight

    Rectangle {
        id: idleBtn
        x: 855

        width: 125
        height: 125
        color: "purple"
        anchors.rightMargin: 20
        anchors.topMargin: -133

        anchors {
            right: parent.right
            top: parent.bottom
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("CLICKED IDLE");
                handler.onIdleClicked();
            }
        }
        Text {
            anchors.fill: parent
            text: "IDLE WAIT"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            wrapMode: Text.WordWrap
            font.pixelSize: 35
            font.capitalization: Font.SmallCaps
            font.bold: true
            font.family: "Arial"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }


    Rectangle {
        id: point1_button
        property bool toggled: true
        x: 0

        width: 125
        height: 125
        color: point1_button.toggled ? "green" : "red"
        anchors.rightMargin: 17
        anchors.topMargin: 0
        visible: true

        anchors {
            top: parent.top
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                point1_button.toggled = !point1_button.toggled
                console.log("CLICKED point1_button");
                handler.onPoint1_button_clicked();
            }
        }
        Text {
            text: point1_button.toggled ? "Point 1\nStraight" : "Point 1\nTurn"
            anchors.fill: parent
            font.pixelSize: 25
            font.capitalization: Font.SmallCaps
            font.bold: true
            font.family: "Arial"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        id: point2_button
        property bool toggled: true
        x: 130

        width: 125
        height: 125
        color: point2_button.toggled ? "green" : "red"
        anchors.rightMargin: 17
        anchors.topMargin: 0
        visible: true

        anchors {
            left: point1_button.right
            top: parent.top
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                point2_button.toggled = !point2_button.toggled
                console.log("CLICKED point2_button");
                handler.onPoint2_button_clicked();
            }
        }
        Text {
            text: point2_button.toggled ? "Point 2\nStraight" : "Point 2\nTurn"
            anchors.fill: parent
            font.pixelSize: 25
            font.capitalization: Font.SmallCaps
            font.bold: true
            font.family: "Arial"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
            id: dirForwardBtn
            property bool toggled: false
            x: 733

            width: 125
            height: 125
            color: "grey"
            anchors.rightMargin: 17
            anchors.topMargin: 0
            visible: true

            anchors {
                top: parent.top
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("CLICKED dirForward");
                    handler.onDirForwardClicked();
                    dirStopBtn.color = "grey";
                    dirForwardBtn.color = "green";
                    dirBackwardBtn.color = "grey";
                }
            }
            Text {
                text: "FWD"
                anchors.fill: parent
                font.pixelSize: 25
                font.capitalization: Font.SmallCaps
                font.bold: true
                font.family: "Arial"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

    Rectangle {
            id: dirStopBtn
            property bool toggled: true
            x: 600

            width: 125
            height: 125
            color: "green"
            anchors.rightMargin: 17
            anchors.topMargin: 0
            visible: true

            anchors {
                top: parent.top
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("CLICKED dirStop");
                    handler.onDirStopClicked();
                    dirStopBtn.color = "green";
                    dirForwardBtn.color = "grey";
                    dirBackwardBtn.color = "grey";
                    dirStopBtn.toggled = !dirStopBtn.toggled;
                    dirBackwardBtn.toggled = false;
                    handler.setSliderValue(0)
                }
            }
            Text {
                text: "STOP"
                anchors.fill: parent
                font.pixelSize: 25
                font.capitalization: Font.SmallCaps
                font.bold: true
                font.family: "Arial"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

    Rectangle {
            id: dirBackwardBtn
            property bool toggled: false
            x: 450

            width: 125
            height: 125
            color: "grey"
            anchors.rightMargin: 17
            anchors.topMargin: 0
            visible: true

            anchors {
                top: parent.top
            }


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("CLICKED dirBackward");
                    handler.onDirBackwardClicked();
                    dirStopBtn.color = "grey";
                    dirForwardBtn.color = "grey";
                    dirBackwardBtn.color = "green";
                    dirBackwardBtn.toggled = !dirBackwardBtn.toggled;
                }
            }
            Text {
                text: "BACK"
                anchors.fill: parent
                font.pixelSize: 25
                font.capitalization: Font.SmallCaps
                font.bold: true
                font.family: "Arial"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }



    Rectangle {
        id: stopBtn
        property bool toggled: false

        width: 500
        height: 125

        color: toggled ? "green" : "red"
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                stopBtn.toggled = !stopBtn.toggled
                console.log("CLICKED STOP");
                handler.toggleStop();
                handler.setSliderValue(0.0);
            }
        }

        Text {
            text: "STOP ALL TRAINS"
            anchors.fill: parent
            font.pixelSize: 45
            font.capitalization: Font.SmallCaps
            font.bold: true
            font.family: "Arial"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Slider {
        id: slider
        x: 790
        y: 240
        width: 122
        height: 404
        stepSize: 1.0/255.0
        orientation: Qt.Vertical
        value: handler.sliderValue

        onValueChanged: {
            handler.setSliderValue(value)
        }

        handle: Rectangle {
            x: slider.leftPadding + slider.availableWidth / 2 - width / 2
            y: slider.topPadding + slider.visualPosition * (slider.availableHeight - height)
            implicitWidth: 78
            implicitHeight: 78
            radius: height / 2
            color: slider.pressed ? "#f0f0f0" : "#f6f6f6"
            border.color: "#bdbebf"
            Text {
                text:slider.value
                anchors.fill: parent
                font.pixelSize: 20
                font.capitalization: Font.SmallCaps
                font.bold: true
                font.family: "Arial"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

        }
    }

    Button {
        id: sliderMinus
        x: 801
        y: 662
        width: 111
        height: 77
        text: qsTr("-")
        font.pointSize: 52

        onClicked: {
            handler.onSliderMinusClicked();
        }
    }

    Button {
        id: sliderPlus
        x: 801
        y: 165
        width: 111
        height: 77
        text: qsTr("+")
        font.pixelSize: 52

        onClicked: {
            handler.onSliderPlusClicked();
        }
    }

    ComboBox {
        id: loco_select
        x: 299
        y: 0
        font.family: "Verdana"
        displayText: qsTr("d51")
        transformOrigin: Item.Center
        currentIndex: 0
        textRole: "locomotive"
    }

    Rectangle {
        id: short_whistle
        property bool toggled: true
        x: 130
        y: 130

        width: 125
        height: 125
        color: "#649bd2"
        anchors.rightMargin: 17
        anchors.topMargin: 130
        visible: true

        anchors {
            top: parent.top
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                short_whistle.toggled = !short_whistle.toggled
                console.log("CLICKED short_whistle");
                handler.onShort_whistle_clicked();
            }
        }
        Text {
            text: "Short\nWhistle"
            anchors.fill: parent
            font.pixelSize: 25
            font.capitalization: Font.SmallCaps
            font.bold: true
            font.family: "Arial"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
