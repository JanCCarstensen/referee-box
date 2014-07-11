import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.XmlListModel 2.0

Item {

    id: bttItemDelegate

    property ListModel objectsModel;
    property ListModel placesModel;

    Row {
        spacing: 10

        ComboBox {
            id: comboSource
            editable: true
            model: placesModel

            currentIndex: bttTaskList.getItemSourceIndex(index, placesModelData.convertToListPlaces())

            onEditTextChanged: bttTaskList.updateObect(index, comboSource.editText, comboObject.editText, comboDestination.editText)
         }

        ComboBox {
            id: comboObject

            editable: true
            model: objectsModel

            currentIndex: bttTaskList.getItemObjectIndex(index, objectsModelData.convertToListSingle())

            onEditTextChanged: bttTaskList.updateObect(index, comboSource.editText, comboObject.editText, comboDestination.editText)
         }

        ComboBox {
            id: comboDestination



            editable: true
            model: placesModel
            currentIndex: bttTaskList.getItemDestinationIndex(index, placesModelData.convertToListPlaces())

            onEditTextChanged: bttTaskList.updateObect(index, comboSource.editText, comboObject.editText, comboDestination.editText)
         }


        Button{
            id: delteteItemBtn
            text: "x"

            onClicked: {

                bttTaskList.doRemoveItem(index);
            }
        }
    }
}


