import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Item{

     id: placesModel

     property alias modelid: placedModelData

     function convertToList(){
         var list = [];
         for(var i = 0; i < placedModelData.count; i++) {
             if(placedModelData.get(i).active === "true"){
                list.push(placedModelData.get(i).place);
             }
         }
         return list;
     }


    ListModel{
        id: placedModelData
    }

    XmlListModel {

        source: "../Rescources/places.xml"
        query: "/places/place"




        XmlRole { name: "place"; query: "name/string()" }
        XmlRole { name: "active"; query: "active/string()" }

        onStatusChanged: {

            if (status == XmlListModel.Ready) {

                for (var i=0; i<count; i++) {
                    var item = get(i)
                    placedModelData.append({place: item.place, active: item.active})
                }

                console.log ("placesModel - Ready");

            }

            else if (status == XmlListModel.Error) {

                console.log ("placesModel - Error");
                console.log(errorString());
            }

        }
    }
}


