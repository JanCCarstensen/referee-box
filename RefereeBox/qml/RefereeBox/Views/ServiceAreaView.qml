import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {

    property string placeName;
    property string placeConfiguration;
    property string placeNavigation;
    property string placePickUp;
    property string placePutDown;
    property ListModel objectsDataModel;

    ListModel{
        id: objectsData
    }


    function setObjectsModel(objectsList, orientationsList, rotationsList){

        var items = [firstItem,secondItem,thirdItem];

        for (var it = 0; it < objectsList.length; it++) {
            objectsData.append({"object":objectsList[it], "orientation":orientationsList[it],"rotation":rotationsList[it]});
            items[it].object = objectsList[it];
            items[it].orientation = orientationsList[it];
            items[it].rotation = rotationsList[it];
            items[it].objectPath = "../Rescources/Objects/"+objectsList[it]+".png";
            items[it].visible = true;
        }

        return objectsData
    }



    width: 200
    height: 120

    border.width: 3
    border.color: "#000000"

    Column{

        anchors.fill: parent
        spacing: 10

        Row{

            spacing: 20
            anchors.horizontalCenter:  parent.horizontalCenter

            Text{
                text: placeName

            }

            Text{
                text: placeConfiguration

            }

            Text{
                text: placeNavigation
            }

            Text{
                text: placePickUp
            }

            Text{
                text: placePutDown
            }

        }

        Row{

            x: 10

            Column{

                id: firstItem
                visible: false

                height: 70
                width: 60

                property string object: "";
                property string orientation: "";
                property int rotation: 0;
                property string objectPath: "";


                Image {
                    height: 60
                    width: 60
                    fillMode: Image.PreserveAspectFit
                    source: firstItem.objectPath
                    transform: Rotation { origin.x: 30; origin.y: 30; angle: firstItem.rotation}

                }

                Text{
                    text: firstItem.object

                }
//                Text{
//                    text: firstItem.orientation

//                }
//                Text{
//                    text: firstItem.rotation

//                }
            }

            Column{

                id: secondItem
                visible: false

                height: 70
                width: 60

                property string object: "";
                property string orientation: "";
                property int rotation: 0;
                property string objectPath: "";


                Image {
                    height: 60
                    width: 60
                    fillMode: Image.PreserveAspectFit
                    source: secondItem.objectPath
                    transform: Rotation { origin.x: 30; origin.y: 30; angle: secondItem.rotation}

                }
                Text{
                    text: secondItem.object

                }
//                Text{
//                    text: secondItem.orientation

//                }
//                Text{
//                    text: secondItem.rotation

//                }
            }

            Column{

                id: thirdItem
                visible: false

                height: 70
                width: 60

                property string object: "";
                property string orientation: "";
                property int rotation: 0;
                property string objectPath: "";

                Image {
                    height: 60
                    width: 60
                    fillMode: Image.PreserveAspectFit
                    source: thirdItem.objectPath
                    transform: Rotation { origin.x: 30; origin.y: 30; angle: thirdItem.rotation}

                }
                Text{
                    text: thirdItem.object

                }
//                Text{
//                    text: thirdItem.orientation

//                }
//                Text{
//                    text: thirdItem.rotation

//                }
            }
        }
    }
}




