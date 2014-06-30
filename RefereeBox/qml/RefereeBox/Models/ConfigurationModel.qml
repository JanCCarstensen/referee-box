import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Item {

    property alias modelid: configurationModel

    function convertToList(){
        var list = [];
        for(var i = 0; i < configurationModel.count; i++) {
            if(configurationModel.get(i).active === "true"){
                 list.push(configurationModel.get(i).configuration);
            }
        }
        return list;
    }

    ListModel{

        id: configurationModel

    }

    XmlListModel{

        source: "../Rescources/configuration.xml"
        query: "/configurations/configuration"




        XmlRole { name: "configuration"; query: "name/string()" }
        XmlRole { name: "active"; query: "active/string()" }

        onStatusChanged: {

            if (status == XmlListModel.Ready) {

                for (var i=0; i<count; i++) {
                    var item = get(i)
                    configurationModel.append({configuration: item.configuration,
                                       active: item.active})
                }

                console.log ("configurationModel - Ready");

            }

            else if (status == XmlListModel.Error) {

                console.log ("configurationModel - Error");
                console.log(errorString());
            }

        }
    }
}
