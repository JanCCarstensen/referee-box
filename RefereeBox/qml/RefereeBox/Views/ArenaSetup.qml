import QtQuick 2.0
import QtQuick.Controls 1.2

import "../Models/" as Models

Rectangle {
    id: arenaSetup


    Models.PlacesModel{id: placesModelData}
    Models.ObjectsModel{id: objectsModelData}
    Models.RotationsModel{id: rotationsModelData}
    Models.ItemOrientationsModel{id: itemOrientationsModelData}
    Models.ConfigurationModel{id: configurationModelData}
    Models.OrientationModel{id: orientationModelData}

    ListView{
        id: placesSelect

        anchors.top: parent.top

        anchors.left: parent.left
        anchors.bottom: parent.bottom

        width: parent.width /3

        model: placesModelData.modelid

        header:Component{
            Row{
                Text{
                    text: "   N     "
                }
                Text{
                    text: "PU    "
                }
                Text{
                    text: "PD     "
                }

            }
        }

        delegate: Item{

                x: 10
                height: 20
                width: parent.width

                Row{

                    spacing: 10

                    CheckBox{


                          checked: navigation == "true" ? true : false

                          onClicked:  {
                              if(navigation == "true"){
                                  placesModelData.modelid.setProperty(index, "navigation", "false");
                              }else{
                                  placesModelData.modelid.setProperty(index, "navigation", "true");

                              }
                          }
                    }

                    CheckBox{


                          checked: pickup == "true" ? true : false

                          onClicked:  {
                              if(pickup == "true"){
                                  placesModelData.modelid.setProperty(index, "pickup", "false");
                              }else{
                                  placesModelData.modelid.setProperty(index, "pickup", "true");

                              }
                          }
                    }

                    CheckBox{


                          checked: putdown == "true" ? true : false

                          onClicked:  {
                              if(putdown == "true"){
                                  placesModelData.modelid.setProperty(index, "putdown", "false");
                              }else{
                                  placesModelData.modelid.setProperty(index, "putdown", "true");

                              }
                          }
                    }

                    Text{
                         text: placesModelData.modelid.get(index).text

                    }

                }
        }


    }

    ListView{
        id: objectsSelect

        anchors.top: parent.top
        anchors.left: placesSelect.right
        anchors.bottom: parent.bottom

        model: objectsModelData.modelid

        width: parent.width /3

        spacing: 10

        delegate: Item{

                x: 10
                height: 20
                width: parent.width

                Row{

                    spacing: 10


                    CheckBox{
                        checked: active == "true" ? true : false

                        onClicked:  {
                            if(active == "true"){
                                objectsModelData.modelid.setProperty(index, "active", "false");
                            }else{
                                objectsModelData.modelid.setProperty(index, "active", "true");
                            }
                        }
                    }

                    ComboBox{

                        id: numOfObject
                        editable: true
                        model: 10;

                        currentIndex: quantity;

                        onCurrentIndexChanged: objectsModelData.modelid.setProperty(index, "quantity", currentIndex);


                        validator: IntValidator {bottom: 1; top: 10;}
                    }

                    Text{
                        text: objectsModelData.modelid.get(index).text
                    }


                }
        }
    }


    ListView{
        id: itemConfiguration

        anchors.top: parent.top
        anchors.left: objectsSelect.right

        height: 200
        model: configurationModelData.modelid


        spacing: 10

        delegate: Item{

                x: 10
                height: 20
                width: parent.width

                Row{

                    spacing: 10



                    CheckBox{
                        checked: active == "true" ? true : false

                        onClicked:  {
                            if(active == "true"){
                                configurationModelData.modelid.setProperty(index, "active", "false");
                            }else{
                                configurationModelData.modelid.setProperty(index, "active", "true");

                            }
                        }


                    }

                    Text{
                        text: configuration
                    }


                }
        }
    }

    Column{
        anchors.top: itemConfiguration.bottom
        anchors.left: objectsSelect.right
        anchors.bottom: parent.bottom

        width: parent.width /3




        Button{
            id: autoGenButtin
            text: "Auto generate"


            onClicked: {
                arena.generateArenaSetup(placesModelData.convertToList(), objectsModelData.convertToList(), configurationModelData.convertToList(), rotationsModelData.convertToList(), itemOrientationsModelData.convertToList(), 5)
            }

        }


    }



}
