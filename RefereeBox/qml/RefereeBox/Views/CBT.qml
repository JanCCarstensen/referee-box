import QtQuick 2.0
import QtQuick.Controls 1.2

import "../Models/" as Models

Item {
    anchors.fill: parent

    signal newText(string text)

    Models.PlacesModel{id: placesModelData}

    Rectangle{
        id: controlView

        anchors.fill: parent
        Row{
            id: scoureRow
            Label {
                id: sourceText
                text: "CBT Pos: "
            }

            ComboBox {
                id: comboStart
                editable: true
                model: placesModelData.convertToListPlaces()
                onEditTextChanged: cbtTaskList.updateStartPosition(comboStart.editText)
            }
        }




        Button{
            anchors.top: scoureRow.bottom
            text: "Compose"
            id: compose

            onClicked: {

               newText(cbtTaskList.composeCBTTaskSpec())


            }

        }


        Button{
            anchors.top: compose.bottom
            text: "Auto generate"

            onClicked: {

               newText(cbtTaskList.generateCBTTaskSpec(1))
               comboStart.currentIndex = cbtTaskList.getItemStartPos(placesModelData.convertToListPlaces())


            }

        }

    }
}
