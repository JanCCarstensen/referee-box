#include "bnttask.h"

#include <QDebug>
#include <cstdlib>


BNTTask::BNTTask(QObject *parent): QAbstractListModel(parent){

    connect( this, SIGNAL( addBNTRequest(BNTItem*) ), this, SLOT( doAddItem(BNTItem*)) ) ;
    connect( this, SIGNAL( removeBNTRequest(BNTItem*) ), this, SLOT( doRemoveItem(BNTItem*)) ) ;

    selectedItem_ = -1;
}


void BNTTask::doAddItem(BNTItem* bntItem){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    bntItemList_.append(bntItem);
    endInsertRows();
}

void BNTTask::doRemoveItem(BNTItem* bntItem){
    bntItemList_.removeOne(bntItem);

}

void BNTTask::addItem(BNTItem* bntItem){
    emit addBNTRequest(bntItem);
}

void BNTTask::removeItem(BNTItem* bntItem){
    emit removeBNTRequest(bntItem);
}

void BNTTask::doAddEmtpyItem(){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    bntItemList_.append(new BNTItem());
    endInsertRows();
}


void BNTTask::doRemoveItem(int index){
    beginRemoveRows(QModelIndex(), index, index);
    delete bntItemList_[index];
    bntItemList_.removeAt(index);
    endRemoveRows();
}

void BNTTask::updateData(int index, QString place, QString orientation){
    bntItemList_[index]->setOrientation(orientation);
    bntItemList_[index]->setPlace(place);

}

int BNTTask::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return bntItemList_.count();
}

QString BNTTask::composeTaskSpec(){

    QString taskSpec = "BNT<";

    for(int i = 0; i < bntItemList_.length(); ++i){
        taskSpec += "(";
        taskSpec += bntItemList_[i]->getPlace();
        taskSpec += ",";
        taskSpec += bntItemList_[i]->getOrientation();
        taskSpec += ",";
        taskSpec += "3";
        taskSpec += ")";
    }

    taskSpec += ">";

    qDebug() << taskSpec;

    return taskSpec;
}

QString BNTTask::getItemPlace(int index){
    qDebug() << bntItemList_[index]->getPlace();
    return bntItemList_[index]->getPlace();
}

QString BNTTask::getItemOrientation(int index){
    return bntItemList_[index]->getOrientation();
}

QString BNTTask::autogenerateBNT(int numberOfPlaces, QList<QString> places, QList<QString> orientations){

    clearList();

    if(places.length() > 0 && orientations.length() > 0){

        for(int i= 0; i < numberOfPlaces; ++i){

            int randomPlaceNum = rand() % places.length();
            int randomOrientationNum = rand() % orientations.length();

            doAddItem(new BNTItem(places[randomPlaceNum], orientations[randomOrientationNum]));

            places.removeAt(randomPlaceNum);

        }

    }

   return composeTaskSpec();
}


void BNTTask::clearList(){
    beginRemoveRows(QModelIndex(), 0, bntItemList_.length());
    qDeleteAll(bntItemList_);
    bntItemList_.clear();
    endRemoveRows();
}

void BNTTask::itemSelected(int id){
    selectedItem_ = id;
    BNTItem* selectedBNTItem = bntItemList_.at(selectedItem_);
    qDebug() << "Selected: " << selectedBNTItem->getPlace() << " " << selectedBNTItem->getOrientation();
}

QVariant BNTTask::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= bntItemList_.count())
        return QVariant();

    const BNTItem* bntItem = bntItemList_[index.row()];
    if (role == PlaceRole)
        return bntItem->getPlace();
    else if (role == OrientationRole)
        return bntItem->getOrientation();
    return QVariant();
}

int BNTTask::getItemPlaceIndex(int index, QList<QString> places){
    if( index < bntItemList_.length() && index >= 0){
        return places.indexOf(bntItemList_[index]->getPlace());
    } else {
        return -1;
    }

}

int BNTTask::getItemOrientationIndex(int index, QList<QString> orientations){
    if( index < bntItemList_.length() && index >= 0){
        return orientations.indexOf(bntItemList_[index]->getOrientation());
    } else {
        return -1;
    }
}

QHash<int, QByteArray> BNTTask::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PlaceRole] = "place";
    roles[OrientationRole] = "orientation";
    return roles;
}
