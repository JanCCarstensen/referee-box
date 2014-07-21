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

        id: bmtTaskView
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

        delegate: BMTItemDelegate{
            objectsModel: objectsModelData.modelid
        }

        model: bmtTaskList


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
                text: "Source: "
            }

            ComboBox {
                id: comboSource


                editable: true
                model: placesModelData.convertToListPlaces()
                onEditTextChanged: bmtTaskList.updateAllSource(comboSource.editText)
            }
        }

        Row{
            id: destinationRow
            anchors.top: scoureRow.bottom
            Label {
                id: destinationText
                text: "Destination: "
            }


            ComboBox {
                id: comboDestination
                editable: true
                model: placesModelData.convertToListPlaces()



                onEditTextChanged: bmtTaskList.updateAllDestination(comboDestination.editText)
            }
        }

        Row{
            id: configurationRow
            anchors.top: destinationRow.bottom
            Label {
                id: configurationText

                text: "Configuration: "
            }

            ComboBox {
                id: comboConfig

                editable: true
                model: configurationModel.convertToList()

                onEditTextChanged: bmtTaskList.updateAllDestinationType(comboConfig.editText)
            }

        }




        Button{
            anchors.top: configurationRow.bottom
            id: addTaskElement
            text: "Add Element"

            onClicked: {
                bmtTaskList.doAddEmtpyItem();
            }

        }


        Button{
            anchors.top: addTaskElement.bottom
            id: compose
            text: "Compose"

            onClicked: {
                bmtTaskList.updateAllDestinationType(comboConfig.editText)
                bmtTaskList.updateAllSource(comboSource.editText)
                bmtTaskList.updateAllDestination(comboDestination.editText)
                newText(bmtTaskList.composeBMTTaskSpec())


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

               newText(bmtTaskList.generateBMTTaskSpec(numOfSamples.editText))
               comboDestination.currentIndex = bmtTaskList.getItemEndPos(placesModelData.convertToListPlaces())
               comboSource.currentIndex = bmtTaskList.getItemStartPos(placesModelData.convertToListPlaces())

            }

        }

    }
}
