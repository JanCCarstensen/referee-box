import QtQuick 2.0

Rectangle {

    anchors.fill: parent



    Image {
        id: mapPlaceholder
        width: parent.width /2
        fillMode: Image.PreserveAspectFit
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        source: "../Map.png"
    }

    GridView{

        width: parent.width /2
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        cellWidth: 240;
        cellHeight: 130


        model: arena

        delegate: ServiceAreaView{

            placeConfiguration: configuration
            placeName: place

            objectsDataModel: setObjectsModel(objectsModel, orientations, rotations)



        }


    }

}


