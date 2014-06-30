import QtQuick 2.0
import QtQuick.Controls 1.2

import "Views"

Rectangle {
    id: main_window
    width: 800
    height: 600

    Rectangle {
        id: menuBarRect
        x: 0
        width: parent.width
        height: 30
        radius: 1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 0.610
                color: "#ffffff"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        clip: false
        smooth: true
        border.width: 3
        border.color: "#000000"
        transformOrigin: Item.Center
        anchors.top: parent.top
        anchors.topMargin: 0

        Text {
            id: text1
            x: 11
            y: 7
            text: qsTr("Menu Bar")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: mainPanelRect
        x: 0
        y: 30
        width: parent.width
        height: (parent.height-30)
        color: "#ffffff"

        Rectangle {
            id: leftPanelRect
            x: 0
            y: 0
            width: 180
            color: "#ffffff"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            border.width: 2
            border.color: "#000000"

            TeamListView{
                anchors.fill: parent
            }



        }

        Rectangle {
            id: rightPanelRect
            x: 620
            width: 180
            color: "#ffffff"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            border.color: "#000000"

            Rectangle {
                id: devicePanelRect
                width: parent.width
                height: parent.height*0.5
                color: "#ffffff"
                anchors.top: parent.top
                border.color: "#000000"
                border.width: 2

                DeviceListView{
                    anchors.fill: parent
                }
            }


            Rectangle {
                id: timePanelRect
                x: 0
                y: 279
                width: parent.width
                height: 130
                color: "#ffffff"
                anchors.top: devicePanelRect.bottom
                anchors.topMargin: -6
                border.color: "#000000"
                Text {
                    id: text2
                    x: 62
                    y: 52
                    text: qsTr("10:00")
                    font.pixelSize: 22
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                border.width: 2
            }

            Rectangle {
                id: contorlPanelRect
                x: 0
                width: parent.width
                color: "#ffffff"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: timePanelRect.bottom
                anchors.topMargin: 0
                border.color: "#000000"
                border.width: 2

                Button{
                    id: sendTaskSPecBtn
                    text:"Send Task Spec"

                    onClicked: {
                        Networking.sendTaskSpec(taskSpecView.taskSpecText)
                    }


                }

            }

            border.width: 2
        }

        Rectangle {
            id: centerPanelRect
            x: 180
            y: 0
            height: parent.height
            color: "#ffffff"
            anchors.right: rightPanelRect.left
            anchors.rightMargin: 0
            anchors.left: leftPanelRect.right
            anchors.leftMargin: 0

            Rectangle {
                id: centerBottomPanelRect
                x: 0
                y: 285
                width: 440
                height: parent.height*0.45
                color: "#ffffff"
                border.color: "#000000"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0


                TaskSpecView{
                    id: taskSpecView
                    anchors.fill: parent
                }




            }

            Rectangle {
                id: centerTopPanelRect
                x: 0
                y: 1
                width: 440
                height: parent.height*0.55
                color: "#ffffff"
                border.color: "#000000"
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.rightMargin: 0
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.left: parent.left

                ArenaView {
                    id: mapPanelRect
                    x: 0
                    y: 0
                    color: "#ffffff"
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    border.color: "#000000"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0


                }
            }
        }
    }



}
