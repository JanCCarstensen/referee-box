import QtQuick 2.0
import QtQuick.XmlListModel 2.0

XmlListModel {
    id: rotationsModel
    source: "../Rescources/rotations.xml"
    query: "/rotations/rotation"

    function convertToList(){
        var list = [];
        for(var i = 0; i < rotationsModel.count; i++) {
            list.push(rotationsModel.get(i).rotation);
        }
        return list;
    }

    XmlRole { name: "rotation"; query: "name/string()" }

    onStatusChanged: {

        if (status == XmlListModel.Ready) {

            console.log ("rotationsModel - Ready");

        }

        else if (status == XmlListModel.Error) {

            console.log ("rotationsModel - Error");
            console.log(errorString());
        }

    }
}
