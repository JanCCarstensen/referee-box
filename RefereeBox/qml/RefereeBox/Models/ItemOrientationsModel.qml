import QtQuick 2.0
import QtQuick.XmlListModel 2.0

XmlListModel {
    id: itemOrientationsModel
    source: "../Rescources/itemOrientations.xml"
    query: "/orientations/orientation"

    function convertToList(){
        var list = [];
        for(var i = 0; i < itemOrientationsModel.count; i++) {
            list.push(itemOrientationsModel.get(i).itemOrientation);
        }
        return list;
    }

    XmlRole { name: "itemOrientation"; query: "name/string()" }

    onStatusChanged: {

        if (status == XmlListModel.Ready) {

            console.log ("itemOrientationsModel - Ready");

        }

        else if (status == XmlListModel.Error) {

            console.log ("imtemOrientationsModel - Error");
            console.log(errorString());
        }

    }
}
