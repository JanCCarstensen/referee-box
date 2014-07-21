import QtQuick 2.0
import QtQuick.Controls 1.2

import "../Models/" as Models

Item {
    anchors.fill: parent

    signal newText(string text)

    Models.PlacesModel{id: placesModelData}
    Models.ObjectsModel{id: objectsModelData}
    Models.ConfigurationModel{id: configurationModel}

    ListView{


        id: bttTaskView
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

        delegate: BTTItemDelegate{
            objectsModel: objectsModelData.modelid
            placesModel: placesModelData.modelid

        }


        model: bttTaskList


    }

    Rectangle{
        id: controlView

        width: 200

        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        Row{
            id: scoureRow
            Label {
                id: sourceText
                text: "Start: "
            }

            ComboBox {
                id: comboStart
                editable: true
                model: placesModelData.convertToListPlaces()
                onEditTextChanged: bttTaskList.updateStartPosition(comboStart.editText)
            }
        }

        Row{
            id: destinationRow
            anchors.top: scoureRow.bottom
            Label {
                id: destinationText
                text: "End: "
            }

            ComboBox {
                id: comboEnd
                editable: true
                model: placesModelData.convertToListPlaces()

                onEditTextChanged: bttTaskList.updateEndPosition(comboEnd.editText)
            }
        }

        Button{
            anchors.top: destinationRow.bottom
            id: addTaskElement
            text: "Add Element"

            onClicked: {
                bttTaskList.doAddEmtpyItem();
            }

        }


        Button{
            id: compose
            anchors.top: addTaskElement.bottom
            text: "Compose"

            onClicked: {
                bttTaskList.updateStartPosition(comboStart.editText)
                bttTaskList.updateEndPosition(comboEnd.editText)

                console.log("click")


                newText(bttTaskList.composeBTTTaskSpec())


            }

        }

        ComboBox{
            anchors.top: compose.bottom
            id: numOfSamples
            editable: true
            model: 10;
            currentIndex: 1
            validator: IntValidator {bottom: 1; top: 10;}
        }





        Button{
            anchors.top: numOfSamples.bottom
            text: "Auto generate"

            onClicked: {

               newText(bttTaskList.generateBTTTaskSpec(numOfSamples.editText))

                comboStart.currentIndex = bttTaskList.getItemEndPos(placesModelData.convertToListPlaces())
                comboEnd.currentIndex = bttTaskList.getItemStartPos(placesModelData.convertToListPlaces())

            }

        }

    }
}
