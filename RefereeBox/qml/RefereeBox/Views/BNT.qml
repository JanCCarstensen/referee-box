import QtQuick 2.0
import QtQuick.Controls 1.2

import "../Models/" as Models


Item {

    function convertToList(model){
        var list = [];
        for(var i = 0; i < model.count; i++) {
            list.push(model.get(i).text);
        }
        return list;
    }


    anchors.fill: parent

    signal newText(string text)

    Models.PlacesModel{id: placesModelData}
    Models.OrientationModel{id: orientationsModelData}

    ListView{

        id: bntTaskView
        spacing: 30
        snapMode: ListView.SnapOneItem
        keyNavigationWraps: true
        cacheBuffer: 0
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        highlightRangeMode: ListView.ApplyRange
        smooth: false

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: controlView.left
        anchors.topMargin: 5

        delegate: BNTItemDelegate{
            placesModel: placesModelData.modelid
            orientationsModel: orientationsModelData
        }

        model: bntTaskList


    }

    Rectangle{
        id: controlView

        width: 200

        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right





        Button{

            id: addTaskElement
            text: "Add Element"

            onClicked: {
                bntTaskList.doAddEmtpyItem();
            }

        }


        Button{
            anchors.top: addTaskElement.bottom
            id: composeTaskSpec
            text: "Compose"

            onClicked: {
//                taskSpecEd.text = bntTaskList.composeTaskSpec()
               newText(bntTaskList.composeTaskSpec())
            }

        }

        ComboBox{
            anchors.top: composeTaskSpec.bottom
            id: numOfSamples
            editable: true
            model: placesModelData.modelid.count+1;
            currentIndex: 1
            validator: IntValidator {bottom: 1; top: placesModelData.modelid.count;}
        }


        Button{
            anchors.top: numOfSamples.bottom
            id: autoGenButtin
            text: "Auto generate"

            onClicked: {
                newText(bntTaskList.autogenerateBNT(numOfSamples.editText, orientationsModelData.convertToList()))
            }

        }

    }






}
