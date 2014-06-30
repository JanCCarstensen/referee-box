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
                model: placesModelData
                onEditTextChanged: cbtTaskList.updateStartPosition(comboStart.editText)
            }
        }




        Button{
            anchors.top: scoureRow.bottom
            text: "Compose"

            onClicked: {

               newText(cbtTaskList.composeCBTTaskSpec())


            }

        }

    }
}
