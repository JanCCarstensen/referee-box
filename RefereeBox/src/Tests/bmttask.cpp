#include "bmttask.h"

#include <QDebug>
#include <QMap>

BMTTask::BMTTask(QString taskType){

    taskType_ = taskType;

    connect( this, SIGNAL( addBNTRequest(BMTItem*) ), this, SLOT( doAddItem(BMTItem*)) ) ;
    connect( this, SIGNAL( removeBNTRequest(BMTItem*) ), this, SLOT( doRemoveItem(BMTItem*)) ) ;

    selectedItem_ = -1;
}


void BMTTask::doAddItem(BMTItem* bmtItem){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    bmtItemList_.append(bmtItem);
    endInsertRows();
}

void BMTTask::doRemoveItem(BMTItem* bmtItem){
    bmtItemList_.removeOne(bmtItem);

}

void BMTTask::addItem(BMTItem* bmtItem){
    emit addBNTRequest(bmtItem);
}

void BMTTask::removeItem(BMTItem* bmtItem){
    emit removeBNTRequest(bmtItem);
}

void BMTTask::doAddEmtpyItem(){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    bmtItemList_.append(new BMTItem());
    endInsertRows();
}


void BMTTask::doRemoveItem(int index){
    beginRemoveRows(QModelIndex(), index, index);
    bmtItemList_.removeAt(index);
    endRemoveRows();
}

void BMTTask::updateData(int index, QString source, QString sourceType, QString object, QString destination, QString destinationType){
    bmtItemList_[index]->setSource(source);
    bmtItemList_[index]->setSourceType(sourceType);
    bmtItemList_[index]->setObject(object);
    bmtItemList_[index]->setDestination(destination);
    bmtItemList_[index]->setDesitnationType(destinationType);
}

void BMTTask::updateObect(int index, QString object){
    bmtItemList_[index]->setObject(object);
}

void BMTTask::updateAllSource(QString source){
    for(int i = 0; i < bmtItemList_.length(); ++i){
        bmtItemList_[i]->setSource(source);
    }
}

void BMTTask::updateAllSourceType(QString sourceType){
    for(int i = 0; i < bmtItemList_.length(); ++i){
        bmtItemList_[i]->setSourceType(sourceType);
    }
}

void BMTTask::updateAllDestination(QString destination){
    for(int i = 0; i < bmtItemList_.length(); ++i){
        bmtItemList_[i]->setDestination(destination);
    }
}

void BMTTask::updateAllDestinationType(QString destinationType){
    for(int i = 0; i < bmtItemList_.length(); ++i){
        bmtItemList_[i]->setDesitnationType(destinationType);
    }
}

void BMTTask::updateObect(int index, QString source, QString object, QString destination){
    bmtItemList_[index]->setSource(source);
    bmtItemList_[index]->setObject(object);
    bmtItemList_[index]->setDestination(destination);
}

void BMTTask::updateStartPosition(QString start){
    startPos_ = start;
}

void BMTTask::updateEndPosition(QString end){
    endPos_ = end;
}

int BMTTask::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return bmtItemList_.count();
}

QString BMTTask::composeCBTTaskSpec(){
    QString taskSpec = "CBT<";
    if(startPos_ != NULL){
       taskSpec += startPos_;
    }
    taskSpec += ">";
    return taskSpec;
}

QString BMTTask::composePPTTaskSpec(){
    QString taskSpec = "PPT<";
    if(bmtItemList_.length() > 0){

         taskSpec += startPos_;
         taskSpec += ",";
         taskSpec += "(";

        for(int i = 0; i < bmtItemList_.length(); ++i){

            taskSpec += bmtItemList_[i]->object();
            if(i+1 != bmtItemList_.length()){
                taskSpec += ",";
            }

        }

        taskSpec += ")";
        taskSpec += ",";
        taskSpec += endPos_;


    }

    taskSpec += ">";
    qDebug() << taskSpec;
    return taskSpec;
}

QString BMTTask::composeBTTTaskSpec(){
    QString taskSpec = "BTT<";

    QMap<QString, QList<QString> > initialState;
    QMap<QString, QList<QString> > goalState;



    if(bmtItemList_.length() > 0){


        for(int i = 0; i < bmtItemList_.length(); ++i){
            if(initialState.contains(bmtItemList_[i]->source())){
                initialState[bmtItemList_[i]->source()].append(bmtItemList_[i]->object());
            } else {
                QList<QString> tmpList;
                tmpList.append(bmtItemList_[i]->object());
                initialState.insert(bmtItemList_[i]->source(), tmpList);
            }

            if(goalState.contains(bmtItemList_[i]->destination())){
                goalState[bmtItemList_[i]->destination()].append(bmtItemList_[i]->object());
            } else {
                QList<QString> tmpList;
                tmpList.append(bmtItemList_[i]->object());
                goalState.insert(bmtItemList_[i]->destination(), tmpList);
            }


        }

        taskSpec += "initialsituation(";
        for(int i = 0; i < initialState.keys().length(); ++i){
            taskSpec += "<";
            taskSpec += initialState.keys()[i];
            taskSpec += ",";
            taskSpec += "line(";
            for(int j = 0; j < initialState[initialState.keys()[i]].length(); ++j){
                taskSpec += initialState[initialState.keys()[i]][j];
                if(j+1 != initialState[initialState.keys()[i]].length()){
                    taskSpec += ",";
                }
            }

            taskSpec += ")>";
        }


        taskSpec += ");goalsituation(";
        for(int i = 0; i < goalState.keys().length(); ++i){
            taskSpec += "<";
            taskSpec += goalState.keys()[i];
            taskSpec += ",";
            taskSpec += "line(";
            for(int j = 0; j < goalState[goalState.keys()[i]].length(); ++j){
                taskSpec += goalState[goalState.keys()[i]][j];
                if(j+1 != goalState[goalState.keys()[i]].length()){
                    taskSpec += ",";
                }
            }

            taskSpec += ")>";
        }
        taskSpec += ")";



    }

    taskSpec += ">";
    qDebug() << taskSpec;
    return taskSpec;
}

QString BMTTask::composeBMTTaskSpec(){
    QString taskSpec = "BMT<";
    if(bmtItemList_.length() > 0){

         taskSpec += bmtItemList_[0]->source();
         taskSpec += ",";
         taskSpec += bmtItemList_[0]->source();
         taskSpec += ",";
         taskSpec += bmtItemList_[0]->destination();
         taskSpec += ",";
         taskSpec += bmtItemList_[0]->desitnationType();
         taskSpec += "(";

        for(int i = 0; i < bmtItemList_.length(); ++i){

            taskSpec += bmtItemList_[i]->object();
            if(i+1 != bmtItemList_.length()){
                taskSpec += ",";
            }

        }

        taskSpec += ")";
        taskSpec += ",";
        taskSpec += bmtItemList_[0]->destination();


    }

    taskSpec += ">";
    qDebug() << taskSpec;
    return taskSpec;
}

void BMTTask::itemSelected(int id){
    selectedItem_ = id;
//    BMTItem* selectedBNTItem = bntItemList_.at(selectedItem_);
//    qDebug() << "Selected: " << selectedBNTItem->getPlace() << " " << selectedBNTItem->getOrientation();
}

QVariant BMTTask::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= bmtItemList_.count())
        return QVariant();

    const BMTItem* bmtItem = bmtItemList_[index.row()];
    if (role == SourceRole)
        return bmtItem->source();
    else if (role == SourceTypeRole)
        return bmtItem->sourceType();
    else if (role == ObjectRole)
        return bmtItem->object();
    else if (role == DesitnationRole)
        return bmtItem->destination();
    else if (role == DestinationTypeRole)
        return bmtItem->desitnationType();
    return QVariant();
}

QHash<int, QByteArray> BMTTask::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[SourceRole] = "source";
    roles[SourceTypeRole] = "sourceType";
    roles[ObjectRole] = "object";
    roles[DesitnationRole] = "destination";
    roles[DestinationTypeRole] = "destinationType";
    return roles;
}
