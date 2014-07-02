import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Item{

    id: objectsModel

    property alias modelid: objectsModelData

    function convertToList(){
        var list = [];
        for(var i = 0; i < objectsModelData.count; i++) {
            if(objectsModelData.get(i).active === "true"){
                for(var c = 0; c < objectsModelData.get(i).quantity; c++){
                    list.push(objectsModelData.get(i).text);
                }
            }
        }
        return list;
    }

    function convertToListSingle(){
        var list = [];
        for(var i = 0; i < objectsModelData.count; i++) {
              list.push(objectsModelData.get(i).text);
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
        XmlRole { name: "quantity"; query: "quantity/number()" }

        onStatusChanged: {

            if (status == XmlListModel.Ready) {

                for (var i=0; i<count; i++) {
                    var item = get(i)
                    objectsModelData.append({text: item.object, active: item.active, quantity: item.quantity})
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

