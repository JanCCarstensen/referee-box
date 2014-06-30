import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Item{

    id: objectsModel

    property alias modelid: objectsModelData

    function convertToList(){
        var list = [];
        for(var i = 0; i < objectsModelData.count; i++) {
            if(objectsModelData.get(i).active === "true"){
                for(var c = 0; c < objectsModelData.get(i).count; c++){
                    list.push(objectsModelData.get(i).object);
                }
            }
        }
        return list;
    }

    ListModel{
        id: objectsModelData
    }


    XmlListModel {

        source: "../Rescources/objects.xml"
        query: "/objects/object"


        XmlRole { name: "object"; query: "name/string()" }
        XmlRole { name: "active"; query: "active/string()" }
        XmlRole { name: "count"; query: "count/number()" }

        onStatusChanged: {

            if (status == XmlListModel.Ready) {

                for (var i=0; i<count; i++) {
                    var item = get(i)
                    objectsModelData.append({object: item.object, active: item.active, count: item.count})
                }

                console.log ("objectsModel - Ready");

            }

            else if (status == XmlListModel.Error) {

                console.log ("objectsModel - Error");
                console.log(errorString());
            }

        }
    }

}

