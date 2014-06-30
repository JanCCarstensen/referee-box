import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.XmlListModel 2.0

Item {

    id: bntItemDelegate

    property XmlListModel placesModel;
    property XmlListModel orientationsModel;

    function convertToList(model){
        var list = [];
        for(var i = 0; i < model.count; i++) {
            list.push(model.get(i).text);
        }
        return list;
    }

    Row {
        spacing: 10
        ComboBox {
            id: comboPlace

            currentIndex: bntTaskList.getItemPlaceIndex(index, convertToList(placesModel))

            editable: true

            model: placesModel

            onEditTextChanged: bntTaskList.updateData(index, comboPlace.editText, comboObject.editText)
         }

        ComboBox {
            id: comboObject

            currentIndex: bntTaskList.getItemOrientationIndex(index, convertToList(orientationsModel))

            editable: true
            model: orientationsModel

            onEditTextChanged: bntTaskList.updateData(index, comboPlace.editText, comboObject.editText)

         }

        Button{
            id: delteteItemBtn
            text: "x"

            onClicked: {

                bntTaskList.doRemoveItem(index);
            }
        }
    }
}


