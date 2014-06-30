import QtQuick 2.0
import QtQuick.Controls 1.2

import "../Models/" as Models

Item {
    anchors.fill: parent

    signal newText(string text)

    Models.PlacesModel{id: placesModelData}
    Models.ObjectsModel{id: objectsModelData}

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

        delegate: PPTItemDelegate{
            objectsModel: objectsModelData
        }

        model: pptTaskList


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
                model: placesModelData
                onEditTextChanged: pptTaskList.updateStartPosition(comboSource.editText)
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
                model: placesModelData

                onEditTextChanged: pptTaskList.updateEndPosition(comboDestination.editText)
            }
        }


        Button{
            anchors.top: destinationRow.bottom
            id: addTaskElement
            text: "Add Element"

            onClicked: {
               pptTaskList.doAddEmtpyItem();
            }

        }


        Button{
            anchors.top: addTaskElement.bottom
            text: "Compose"

            onClicked: {

               newText(pptTaskList.composePPTTaskSpec())


            }

        }

    }
}
