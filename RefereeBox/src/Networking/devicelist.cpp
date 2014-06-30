#include "devicelist.h"

DeviceList::DeviceList(QObject *parent): QAbstractListModel(parent){

    connect( this, SIGNAL( addItemRequest(Device*) ), this, SLOT( doAddItem(Device*)) ) ;
    connect( this, SIGNAL( removeItemRequest(int) ), this, SLOT( doRemoveItem(int)) ) ;

    selectedItem_ = -1;
}


void DeviceList::doAddItem(Device* device){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    deviceList_.append(device);
    qDebug() << "item Added";
    endInsertRows();
}

void DeviceList::doRemoveItem(int device){
    beginRemoveRows(QModelIndex(), device, device);
    deviceList_.removeOne(deviceList_[device]);

    qDebug() << "item removed";
    endRemoveRows();
}

void DeviceList::addItem(Device* device){
    emit addItemRequest(device);
}

void DeviceList::removeItem(int device){
    emit removeItemRequest(device);
}

Device* DeviceList::getSelectedDevice(){
    if(selectedItem_ == -1 || selectedItem_ > deviceList_.length()){
        return NULL;
    }
    return deviceList_[selectedItem_];
}


int DeviceList::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return deviceList_.count();
}

void DeviceList::itemSelected(int id){
    selectedItem_ = id;
    Device* selectedDevice = deviceList_.at(selectedItem_);
    qDebug() << "Selected: " << selectedDevice->getName();
}

QVariant DeviceList::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= deviceList_.count())
        return QVariant();

    const Device* device = deviceList_[index.row()];
    if (role == NameRole)
        return device->getName();
    else if (role == ColorRole)
        return device->getColor();
    return QVariant();
}


void DeviceList::checkDevices(){
    for(int i = 0; i < deviceList_.length(); ++i){
        if (deviceList_[i]->disconnected_){
            removeItem(i);
        }
    }
}

QHash<int, QByteArray> DeviceList::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ColorRole] = "color";
    return roles;
}
