#include "arena.h"
#include <cstdlib>

#include <QDebug>
#include <QJsonArray>



Arena::Arena(){

}


void Arena::generateArenaSetup(QList<QString> places, QList<QString> objects, QList<QString> configurations, QList<QString> rotations, QList<QString> orientations, int objectsPerPlace){

    clearList();

    if(objects.length() > 0 && configurations.length() > 0 && rotations.length() > 0 && orientations.length() > 0 ){

        for( int pI = 0; pI < places.length(); ++pI){
            int rdmConfiguration = rand() % configurations.length();

            ArenaPlace* currentPlace = new ArenaPlace();

            currentPlace->setConfiguration(configurations[rdmConfiguration]);
            currentPlace->setPlace(places[pI]);

            for( int i = 0; i < objectsPerPlace && objects.length() > 0; ++i){

                int rdmObject = rand() % objects.length();
                int rdmOrientation = rand() % orientations.length();
                int rdmRotation = rand() % rotations.length();

                ArenaObject* currentObject = new ArenaObject();

                currentObject->setObject(objects[rdmObject]);
                objects.removeAt(rdmObject);

                currentObject->setOrientation(orientations[rdmOrientation]);
                currentObject->setRotation(rotations[rdmRotation]);

                currentPlace->append(currentObject);
            }

            addItem(currentPlace);
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

    arenaSetup_.clear();
    endRemoveRows();
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


    return QVariant();
}

QHash<int, QByteArray> Arena::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PlaceRole] = "place";
    roles[ConfigurationRole] = "configuration";
    roles[ObjectsRole] = "objectsModel";
    roles[OrientationsRole] = "orientations";
    roles[RotationsRole] = "rotations";
    return roles;
}
