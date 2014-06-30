import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.XmlListModel 2.0

Item {

    id: bmtItemDelegate

    property XmlListModel objectsModel;

    Row {
        spacing: 10
        ComboBox {
            id: comboObject

            editable: true
            model: objectsModel

            onEditTextChanged: bmtTaskList.updateObect(index, comboObject.editText)
         }


        Button{
            id: delteteItemBtn
            text: "x"

            onClicked: {

                bmtTaskList.doRemoveItem(index);
            }
        }
    }
}


