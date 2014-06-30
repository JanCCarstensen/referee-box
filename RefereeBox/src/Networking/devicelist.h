#ifndef DEVICELIST_H
#define DEVICELIST_H

#include "device.h"
#include <QAbstractListModel>

class DeviceList : public QAbstractListModel{

    Q_OBJECT

public:

    enum AnimalRoles {
        NameRole = Qt::UserRole + 1,
        ColorRole
    };


    DeviceList(QObject *parent = 0);

    void addItem(Device* device);
    void removeItem(int device);
    Device* getSelectedDevice();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    Q_INVOKABLE void itemSelected(int id);

    void checkDevices();

signals:

    void addItemRequest(Device* device);
    void removeItemRequest(int device);

public slots:



private slots:

    void doAddItem(Device* device);
    void doRemoveItem(int device);




protected:

      QHash<int, QByteArray> roleNames() const;

private:

   QList<Device*> deviceList_;
   int selectedItem_;
};

#endif // DEVICELIST_H

