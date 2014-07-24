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
        source: "../robocup_2014_map.png"
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

        cellWidth: 450;
        cellHeight: 130


        model: arena

        delegate: ServiceAreaView{

            placeConfiguration: configuration
            placeName: place

            placeNavigation: navigation == "true" ? "N " : "";
            placePickUp: pickup == "true" ? "PU " : "";
            placePutDown: putdown == "true" ? "PD" : "";

            objectsDataModel: setObjectsModel(objectsModel, orientations, rotations)



        }


    }

}



