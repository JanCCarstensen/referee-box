import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.XmlListModel 2.0

Item {

    id: pptItemDelegate

    property ListModel objectsModel;

    Row {
        spacing: 10
        ComboBox {
            id: comboObject

            editable: true
            model: objectsModelData.convertToListSingle()

            currentIndex: pptTaskList.getItemObjectIndex(index, objectsModelData.convertToListSingle())
            onEditTextChanged: pptTaskList.updateObect(index, comboObject.editText)
         }


        Button{
            id: delteteItemBtn
            text: "x"

            onClicked: {

                pptTaskList.doRemoveItem(index);
            }
        }
    }
}


