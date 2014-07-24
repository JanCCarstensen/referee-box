#include "arena.h"
#include <cstdlib>

#include <QDebug>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QJsonArray>



Arena::Arena(){
    numberObjectsArena_ = 0;
    numberOfPlaceAreas_ = 0;
}


void Arena::generateArenaSetup(QList<QVariant> places, QList<QString> objects, QList<QString> configurations, QList<QString> rotations, QList<QString> orientations, int objectsPerPlace){


    clearList();

    if(objects.length() >= 0 && configurations.length() > 0 && rotations.length() > 0 && orientations.length() > 0 ){

        while(0 < places.length()){
            int rdmConfiguration = rand() % configurations.length();

            ArenaPlace* currentPlace = new ArenaPlace();

            int rdmPlace = rand() % places.length();

            QMap<QString, QVariant>  qPlace = places[rdmPlace].toMap();


            currentPlace->setConfiguration(configurations[rdmConfiguration]);
            currentPlace->setPlace(qPlace["text"].toString());
            currentPlace->setNavigation(qPlace["navigation"].toBool());
            currentPlace->setPickUp(qPlace["pickup"].toBool());
            currentPlace->setPutDown(qPlace["putdown"].toBool());

            if(qPlace["putdown"].toBool()){
                ++numberOfPlaceAreas_;
            }

            places.removeAt(rdmPlace);

            if(qPlace["pickup"].toBool()){

                for( int i = 0; i < objectsPerPlace && objects.length() >
                     0; ++i){

                    int rdmObject = rand() % objects.length();
                    int rdmOrientation = rand() % orientations.length();
                    int rdmRotation = rand() % rotations.length();

                    ArenaObject* currentObject = new ArenaObject();

                    currentObject->setObject(objects[rdmObject]);
                    objects.removeAt(rdmObject);

                    currentObject->setOrientation(orientations[rdmOrientation]);
                    currentObject->setRotation(rotations[rdmRotation]);

                    currentPlace->append(currentObject);
                    ++numberObjectsArena_;
                }
                addItem(currentPlace);
            }


        }

        QJsonObject arenaSpec;
        writeJSON(arenaSpec);

        qDebug() << arenaSpec;

    }
}

void Arena::readJSON(const QJsonObject &json){

}

void Arena::writeJSON(QJsonObject &json) const{

    QJsonArray jsonPlaces;
    foreach (const ArenaPlace* place, arenaSetup_) {
        QJsonObject jsonPlace;

        jsonPlace["place"] = place->getPlace();
        jsonPlace["configuration"] = place->getConfiguration();

        QJsonArray jsonObjects;
        foreach (const ArenaObject* object, place->getObjects()) {
            QJsonObject jsonObject;

            jsonObject["object"] = object->object();
            jsonObject["rotation"] = object->rotation();
            jsonObject["orientation"] = object->orientation();

            jsonObjects.append(jsonObject);
        }
        jsonPlace["objects"] =jsonObjects;

        jsonPlaces.append(jsonPlace);
    }
    json["places"] = jsonPlaces;
}

QString Arena::getObject(QString place, int index){
    return "";
}

QString Arena::getRotation(QString place, int index){
    return "";
}

QString Arena::getOrientation(QString place, int index){
    return "";
}

int Arena::getObjectCount(QString place){
    return 1;
}

QString Arena::getConfiguration(QString place){
    return "";
}


void Arena::addItem(ArenaPlace* arenaPlace){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    arenaSetup_.append(arenaPlace);
    endInsertRows();
}

void Arena::clearList(){
    beginRemoveRows(QModelIndex(), 0, rowCount());
    numberObjectsArena_ = 0;
    numberOfPlaceAreas_ = 0;
    arenaSetup_.clear();
    endRemoveRows();
}
int Arena::numberObjectsArena() const
{
    return numberObjectsArena_;
}



int Arena::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return arenaSetup_.count();
}


QVariant Arena::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= arenaSetup_.count())
        return QVariant();

    const ArenaPlace* arenaPlace = arenaSetup_[index.row()];
    if (role == PlaceRole)
        return arenaPlace->getPlace();
    else if (role == ConfigurationRole)
        return arenaPlace->getConfiguration();
    else if (role == ObjectsRole)
        return arenaPlace->getObjectNames();
    else if (role == OrientationsRole)
        return arenaPlace->getOrientations();
    else if (role == RotationsRole)
        return arenaPlace->getRotations();
    else if (role == NavigationRole)
        return arenaPlace->getNavigation();
    else if (role == PickUpRole)
        return arenaPlace->getPickUp();
    else if (role == PutDownRole)
        return arenaPlace->getPutDown();


    return QVariant();
}

QHash<int, QByteArray> Arena::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PlaceRole] = "place";
    roles[ConfigurationRole] = "configuration";
    roles[ObjectsRole] = "objectsModel";
    roles[OrientationsRole] = "orientations";
    roles[RotationsRole] = "rotations";
    roles[PickUpRole] = "pickup";
    roles[PutDownRole] = "putdown";
    roles[NavigationRole] = "navigation";

    return roles;
}

QList<ArenaPlace*> Arena::getArenaSetup(){
    return arenaSetup_;
}

int Arena::numberOfPlaceAreas() const {
    return numberOfPlaceAreas_;
}

