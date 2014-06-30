import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.XmlListModel 2.0


Item {
    id: comboBoxDelegateItem
    property XmlListModel comboModel;

    Text {
        width: parent.width
        anchors.margins: 4
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        elide: styleData.elideMode
        text: comboModel.get(styleData.value) !== undefined ? comboModel.get(styleData.value)  : ""
        color: styleData.textColor
        visible: !styleData.selected

    }

    Loader { // Initialize text editor lazily to improve performance
        id: loaderEditor

        anchors.fill: parent
        anchors.margins: 4

        sourceComponent: styleData.selected ? editor : null
        Component {
            id: editor

              ComboBox{
                  id: comboBox
                  model: comboModel
                  currentIndex: styleData.value
                  onCurrentTextChanged: largeModel.setProperty(styleData.row, styleData.role, currentText)
              }

        }
    }
}

