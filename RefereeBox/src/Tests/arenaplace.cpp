#include "arenaplace.h"

ArenaPlace::ArenaPlace(){

}

ArenaPlace::~ArenaPlace(){

}

QString ArenaPlace::getPlace() const
{
    return place_;
}

void ArenaPlace::setPlace(const QString &value)
{
    place_ = value;
}
QString ArenaPlace::getConfiguration() const
{
    return configuration_;
}

void ArenaPlace::setConfiguration(const QString &value)
{
    configuration_ = value;
}
QList<ArenaObject*> ArenaPlace::getObjects() const
{
    return objects_;
}

void ArenaPlace::setObjects(const QList<ArenaObject*> &value)
{
    objects_ = value;
}


QList<QVariant> ArenaPlace::getObjectNames() const{
    QList<QVariant> names;

    for(int i = 0; i < objects_.length(); ++i){
        names.append(objects_[i]->object());
    }
    return names;
}

QList<QVariant> ArenaPlace::getOrientations() const{
    QList<QVariant> orientations;
    for(int i = 0; i < objects_.length(); ++i){
        orientations.append(objects_[i]->orientation());
    }
    return orientations;
}

QList<QVariant> ArenaPlace::getRotations() const{
    QList<QVariant> rotations;
    for(int i = 0; i < objects_.length(); ++i){
        rotations.append(objects_[i]->rotation());
    }
    return rotations;
}


void ArenaPlace::append(ArenaObject* object){
    objects_.append(object);
}

void ArenaPlace::addItem(ArenaObject* arenaPlace){
    beginInsertColumns(QModelIndex(), rowCount(), rowCount());
    objects_.append(arenaPlace);
    endInsertRows();
}


int ArenaPlace::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return objects_.count();
}

QVariant ArenaPlace::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= objects_.count())
        return QVariant();

    const ArenaObject* arenaObject = objects_[index.row()];
    if (role == ObjectRole)
        return arenaObject->object();
    else if (role == RotationRole)
        return arenaObject->rotation();
    else if (role == OrientationRole)
        return arenaObject->orientation();
    return QVariant();
}

QHash<int, QByteArray> ArenaPlace::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ObjectRole] = "object";
    roles[RotationRole] = "rotation";
    roles[OrientationRole] = "orientation";
    return roles;
}
