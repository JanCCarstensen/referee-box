import QtQuick 2.0
import QtQuick.XmlListModel 2.0

XmlListModel {
    id: orientationsModel
    source: "../Rescources/orientations.xml"
    query: "/orientations/orientation"

    function convertToList(){
        var list = [];
        for(var i = 0; i < orientationsModel.count; i++) {
            list.push(orientationsModel.get(i).orientation);
        }
        return list;
    }

    XmlRole { name: "orientation"; query: "name/string()" }

    onStatusChanged: {

        if (status == XmlListModel.Ready) {

            console.log ("orientationsModel - Ready");

        }

        else if (status == XmlListModel.Error) {

            console.log ("orientationsModel - Error");
            console.log(errorString());
        }

    }
}
