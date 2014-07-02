import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Item{

     id: placesModel

     property alias modelid: placedModelData



    function convertToList(){
        var list = [];
        for(var i = 0; i < placedModelData.count; i++) {
               list.push( {text: placedModelData.get(i).text, putdown: placedModelData.get(i).putdown, pickup: placedModelData.get(i).pickup, navigation: placedModelData.get(i).navigation });
        }
        return list;
    }

    function convertToListPlaces(){
        var list = [];
        for(var i = 0; i < placedModelData.count; i++) {
               list.push(placedModelData.get(i).text);
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
        XmlRole { name: "pickup"; query: "pickup/string()" }
        XmlRole { name: "putdown"; query: "putdown/string()" }
        XmlRole { name: "navigation"; query: "navigation/string()" }

        onStatusChanged: {

            if (status == XmlListModel.Ready) {

                for (var i=0; i<count; i++) {
                    var item = get(i)
                    placedModelData.append({text: item.place, putdown: item.putdown, pickup: item.pickup, navigation: item.navigation })
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


