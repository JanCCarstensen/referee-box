import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Rectangle {

    XmlListModel {
        id: teamModel
        source: "../Rescources/teams.xml"
        query: "/teams/team"

        XmlRole { name: "name"; query: "name/string()" }
        XmlRole { name: "teamID"; query: "teamID/string()" }

        onStatusChanged: {

            if (status == XmlListModel.Ready) {

                console.log ("Ready");

            }

            else if (status == XmlListModel.Error) {

                console.log ("Error");
                console.log(errorString());
            }

        }
    }

    id: teamPanelRect
    x: 0
    width: parent.width
    color: "#ffffff"
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
    border.width: 2
    border.color: "#000000"

    ListView {
        id: teamListView
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
            id: teamListItem
            x: 10
            height: 20
            width: parent.width

            Row {
                spacing: 10
                Text {
                    text: teamID
                }
                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                }
            }



            MouseArea {
                id: teamItemMouseArea
                anchors.fill: parent
                onClicked: teamListView.currentIndex = index
            }


        }


        model: teamModel

        highlight: Component {
            Rectangle {
                x: 5
                height: 18
                width: teamListView.width - 10
                color: "lightsteelblue"
                radius: 5
                y: teamListView.currentItem.y
                Behavior on y {
                    SpringAnimation {
                        spring: 3
                        damping: 0.2
                    }
                }
            }
        }
    }
}
