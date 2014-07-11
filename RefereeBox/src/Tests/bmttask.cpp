#include "bmttask.h"

#include <QDebug>
#include <QMap>

BMTTask::BMTTask(QString taskType, Arena* arena){

    arena_ = arena;
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
    if(index < bmtItemList_.length() && index >= 0){
        bmtItemList_[index]->setObject(object);
    }
}

void BMTTask::updateAllSource(QString source){
    for(int i = 0; i < bmtItemList_.length(); ++i){
        bmtItemList_[i]->setSource(source);
    }
    startPos_ = source;
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
    endPos_ = destination;
}

void BMTTask::updateAllDestinationType(QString destinationType){
    for(int i = 0; i < bmtItemList_.length(); ++i){
        bmtItemList_[i]->setDesitnationType(destinationType);
    }
}

void BMTTask::updateObect(int index, QString source, QString object, QString destination){
    if(index > 0){
        bmtItemList_[index]->setSource(source);
        bmtItemList_[index]->setObject(object);
        bmtItemList_[index]->setDestination(destination);
    }
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


QString BMTTask::generateBMTTaskSpec(int numOfObjcetsToTransport){

    clearList();

    QList<ArenaPlace*> setup = arena_->getArenaSetup();
    int numObjects = arena_->numberObjectsArena();
    int numOfPutPlces = arena_->numberOfPlaceAreas();

    QList<QString> sources;
    QList<QString> objects;
    QList<QString> destinations;
//    QString destinationType;

    QList<int> rdmInts;
    QList<int> rdmIntsAreasPlace;


    if(numOfObjcetsToTransport < numObjects){
        while (rdmInts.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numObjects;
            if(!rdmInts.contains(rdmInt)){
                rdmInts.append(rdmInt);
            }

        }

        qSort(rdmInts);


        while (rdmIntsAreasPlace.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numOfPutPlces;
            if(!rdmIntsAreasPlace.contains(rdmInt)){
                rdmIntsAreasPlace.append(rdmInt);
            }

        }

        qSort(rdmIntsAreasPlace);

        int obCount = 0;
        int currentRdmIndex = 0;
        foreach(ArenaPlace* ap, setup){

            if(ap->getPutDown()){
                destinations.append(ap->getPlace());
            }

            foreach (ArenaObject* ob, ap->getObjects()) {
                if(currentRdmIndex < numOfObjcetsToTransport && obCount == rdmInts[currentRdmIndex]){
                    sources.append(ap->getPlace());
                    objects.append(ob->object());
                    ++currentRdmIndex;
                }

                ++obCount;
            }
        }

        for(int c = 0; c < numOfObjcetsToTransport; ++c){

            doAddItem(new BMTItem(sources[c], "", objects[c], destinations[rdmIntsAreasPlace[c]], "line" ));
            //TODO: make destinationType selectable
            startPos_ = sources[c];
            endPos_ = destinations[rdmIntsAreasPlace[c]];
        }
    }

    return composeBMTTaskSpec();
}

QString BMTTask::generateBTTTaskSpec(int numOfObjcetsToTransport){
    clearList();

    QList<ArenaPlace*> setup = arena_->getArenaSetup();
    int numObjects = arena_->numberObjectsArena();
    int numOfPutPlces = arena_->numberOfPlaceAreas();

    QList<QString> sources;
    QList<QString> objects;
    QList<QString> destinations;
//    QString destinationType;

    QList<int> rdmInts;
    QList<int> rdmIntsAreasPlace;


    if(numOfObjcetsToTransport < numObjects){
        while (rdmInts.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numObjects;
            if(!rdmInts.contains(rdmInt)){
                rdmInts.append(rdmInt);
            }

        }

        qSort(rdmInts);


        while (rdmIntsAreasPlace.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numOfPutPlces;
            if(!rdmIntsAreasPlace.contains(rdmInt)){
                rdmIntsAreasPlace.append(rdmInt);
            }

        }

        qSort(rdmIntsAreasPlace);

        int obCount = 0;
        int currentRdmIndex = 0;
        foreach(ArenaPlace* ap, setup){

            if(ap->getPutDown()){
                destinations.append(ap->getPlace());
            }

            foreach (ArenaObject* ob, ap->getObjects()) {
                if(currentRdmIndex < numOfObjcetsToTransport && obCount == rdmInts[currentRdmIndex]){
                    sources.append(ap->getPlace());
                    objects.append(ob->object());
                    ++currentRdmIndex;
                }

                ++obCount;
            }
        }

        for(int c = 0; c < numOfObjcetsToTransport; ++c){

            doAddItem(new BMTItem(sources[c], "", objects[c], destinations[rdmIntsAreasPlace[c]], "line" ));
            //TODO: make destinationType selectable
            startPos_ = sources[c];
            endPos_ = destinations[rdmIntsAreasPlace[c]];
        }
    }

    return composeBTTTaskSpec();

}

QString BMTTask::generateCBTTaskSpec(int numOfObjcetsToTransport){
    clearList();

    QList<ArenaPlace*> setup = arena_->getArenaSetup();
    int numObjects = arena_->numberObjectsArena();
    int numOfPutPlces = arena_->numberOfPlaceAreas();

    QList<QString> sources;
    QList<QString> objects;
    QList<QString> destinations;
//    QString destinationType;

    QList<int> rdmInts;
    QList<int> rdmIntsAreasPlace;


    if(numOfObjcetsToTransport < numObjects){
        while (rdmInts.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numObjects;
            if(!rdmInts.contains(rdmInt)){
                rdmInts.append(rdmInt);
            }

        }

        qSort(rdmInts);


        while (rdmIntsAreasPlace.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numOfPutPlces;
            if(!rdmIntsAreasPlace.contains(rdmInt)){
                rdmIntsAreasPlace.append(rdmInt);
            }

        }

        qSort(rdmIntsAreasPlace);

        int obCount = 0;
        int currentRdmIndex = 0;
        foreach(ArenaPlace* ap, setup){

            if(ap->getPutDown()){
                destinations.append(ap->getPlace());
            }

            foreach (ArenaObject* ob, ap->getObjects()) {
                if(currentRdmIndex < numOfObjcetsToTransport && obCount == rdmInts[currentRdmIndex]){
                    sources.append(ap->getPlace());
                    objects.append(ob->object());
                    ++currentRdmIndex;
                }

                ++obCount;
            }
        }

        for(int c = 0; c < numOfObjcetsToTransport; ++c){

            doAddItem(new BMTItem(sources[c], "", objects[c], destinations[rdmIntsAreasPlace[c]], "line" ));
            //TODO: make destinationType selectable
            startPos_ = sources[c];
            endPos_ = destinations[rdmIntsAreasPlace[c]];
        }
    }

    return composeCBTTaskSpec();

}

QString BMTTask::generatePPTTaskSpec(int numOfObjcetsToTransport){
    clearList();

    QList<ArenaPlace*> setup = arena_->getArenaSetup();
    int numObjects = arena_->numberObjectsArena();
    int numOfPutPlces = arena_->numberOfPlaceAreas();

    QList<QString> sources;
    QList<QString> objects;
    QList<QString> destinations;
//    QString destinationType;

    QList<int> rdmInts;
    QList<int> rdmIntsAreasPlace;


    if(numOfObjcetsToTransport < numObjects){
        while (rdmInts.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numObjects;
            if(!rdmInts.contains(rdmInt)){
                rdmInts.append(rdmInt);
            }

        }

        qSort(rdmInts);


        while (rdmIntsAreasPlace.length() < numOfObjcetsToTransport){

            int rdmInt = rand() % numOfPutPlces;
            if(!rdmIntsAreasPlace.contains(rdmInt)){
                rdmIntsAreasPlace.append(rdmInt);
            }

        }

        qSort(rdmIntsAreasPlace);

        int obCount = 0;
        int currentRdmIndex = 0;
        foreach(ArenaPlace* ap, setup){

            if(ap->getPutDown()){
                destinations.append(ap->getPlace());
            }

            foreach (ArenaObject* ob, ap->getObjects()) {
                if(currentRdmIndex < numOfObjcetsToTransport && obCount == rdmInts[currentRdmIndex]){
                    sources.append(ap->getPlace());
                    objects.append(ob->object());
                    ++currentRdmIndex;
                }

                ++obCount;
            }
        }

        for(int c = 0; c < numOfObjcetsToTransport; ++c){

            doAddItem(new BMTItem(sources[c], "", objects[c], destinations[rdmIntsAreasPlace[c]], "line" ));
            //TODO: make destinationType selectable
            startPos_ = sources[c];
            endPos_ = destinations[rdmIntsAreasPlace[c]];
        }
    }

    return composePPTTaskSpec();
}


void BMTTask::itemSelected(int id){
    selectedItem_ = id;
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

void BMTTask::clearList(){

    beginResetModel();
    qDeleteAll(bmtItemList_);
    bmtItemList_.clear();
    endResetModel();
}


int BMTTask::getItemObjectIndex(int index, QList<QString> objects){
    if( index < bmtItemList_.length() && index >= 0){
        return objects.indexOf(bmtItemList_[index]->object());
    } else {
        return -1;
    }
}

int BMTTask::getItemSourceTypeIndex(int index, QList<QString> sourceTypes){
    if( index < bmtItemList_.length() && index >= 0){
        return sourceTypes.indexOf(bmtItemList_[index]->sourceType());
    } else {
        return -1;
    }
}

int BMTTask::getItemSourceIndex(int index, QList<QString> sources){
    if( index < bmtItemList_.length() && index >= 0){
        return sources.indexOf(bmtItemList_[index]->source());
    } else {
        return -1;
    }
}

int BMTTask::getItemDestinationIndex(int index, QList<QString> destinations){
    if( index < bmtItemList_.length() && index >= 0){
        return destinations.indexOf(bmtItemList_[index]->destination());
    } else {
        return -1;
    }
}

int BMTTask::getItemDestinationTypeIndex(int index, QList<QString> destinationTypes){
    if( index < bmtItemList_.length() && index >= 0){
        return destinationTypes.indexOf(bmtItemList_[index]->desitnationType());
    } else {
        return -1;
    }
}

int BMTTask::getItemStartPos(QList<QString> positions){
    qDebug() << startPos_ <<  positions.indexOf(startPos_);
    return positions.indexOf(startPos_);
}


int BMTTask::getItemEndPos(QList<QString> positions){
    return positions.indexOf(endPos_);
}
