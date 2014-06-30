import QtQuick 2.0



ListView {
    id: deviceListView

    model: deviceListModel

    spacing: 3
    snapMode: ListView.SnapOneItem
    keyNavigationWraps: true
    cacheBuffer: 0
    boundsBehavior: Flickable.StopAtBounds
    flickableDirection: Flickable.AutoFlickDirection
    highlightRangeMode: ListView.ApplyRange
    smooth: false


    anchors.fill: parent
    delegate: Item {
        x: 10
        height: 30
        width: parent.width
        Row {
            spacing: 10
            Rectangle {
                width: 20
                height:20
                radius: width*0.5
                color: color
            }

            Text {
                text: "Test: "+ name
                color: color
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }
        }

        MouseArea {
            id: deviceItemMouseArea
            anchors.fill: parent
            onClicked: {deviceListModel.itemSelected(index)
            deviceListView.currentIndex = index}
        }
    }

    highlight: Component {
        Rectangle {
            x: 5
            height: 18
            width: deviceListView.width - 20
            color: "lightsteelblue"
            radius: 5
            y: deviceListView.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }
}
