import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.XmlListModel 2.0

Item {

    id: bmtItemDelegate

    property ListModel objectsModel;

    Row {
        spacing: 10
        ComboBox {
            id: comboObject

            currentIndex: bmtTaskList.getItemObjectIndex(index, objectsModelData.convertToListSingle())

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


