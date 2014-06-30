import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {

    property alias taskSpecText: taskSpecEdit.text

    TabView {
        id: tabView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: taskSpecEdit.top

        width: parent.width / 2

        signal textUpdate(string text)

        Tab{
            id: bntTab
            title: "BNT"
            BNT{
                 onNewText: tabView.textUpdate(text)
            }
        }


        Tab{
            id: bmtTab
            title: "BMT"
            BMT{
                onNewText: tabView.textUpdate(text)
            }
        }

        Tab{
            id: bttTab
            title: "BTT"
            BTT{
                onNewText: tabView.textUpdate(text)
            }
        }

        Tab{
            id: cbtTab
            title: "CBT"
            CBT{
                onNewText: tabView.textUpdate(text)
            }
        }

        Tab{
            id: pptTab
            title: "PPT"
            PPT{
                onNewText: tabView.textUpdate(text)
            }
        }



        onTextUpdate: taskSpecEdit.text = text
    }

    ArenaSetup{
        id: arenaSetup

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right:  parent.right
        anchors.bottom: taskSpecEdit.top

        width: parent.width / 2

    }

    TextEdit{
        id: taskSpecEdit
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        text: "Task Spec"

        height: 15
    }




}
