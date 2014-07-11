import QtQuick 2.2
import QtQuick.Window 2.1

Window {
    id: window

    visible: true
    width: 1600
    height: 800



    Rectangle{
        id: teamFrame

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: mapFrame.top


        width: parent.width * 2/3
        height: 150

        border.width: 3
        border.color: "#000000"



        Text{
            anchors.centerIn: parent
            text: "teamFrame"
        }


    }


    Rectangle{

        id: mapFrame

        anchors.top:teamFrame.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        width: parent.width * 2/3
        height: width * 3/4

        border.width: 3
        border.color: "#000000"


        Image {
            id: mapPlaceholder
            width: parent.width
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            source: "Rescources/Map.png"
        }


    }


    Rectangle{

        id: taskFrame

        anchors.top:parent.top
        anchors.bottom: statusFrame.top
        anchors.right: parent.right
        anchors.left: mapFrame.right

        width: parent.width * 1/3
        height: 650

        border.width: 3
        border.color: "#000000"

        Text{
            anchors.centerIn: parent
            text: "taskFrame"
        }


    }


    Rectangle{

        id: statusFrame

        anchors.top:taskFrame.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        width: parent.width * 1/3
        height: 150

        border.width: 3
        border.color: "#000000"


        Text{
            anchors.centerIn: parent
            text: "statusFrame"
        }


    }


}
