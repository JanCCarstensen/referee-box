#ifndef ARENASETUP_H
#define ARENASETUP_H

#include <QObject>
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QAbstractListModel>

#include "arenaobject.h"
#include "arenaplace.h"




class Arena : public QAbstractListModel{

    Q_OBJECT

public:
    Arena();

    enum ArenaPlaceRoles {
        PlaceRole = Qt::UserRole + 1,
        ConfigurationRole,
        ObjectsRole,
        RotationsRole,
        OrientationsRole,
        NavigationRole,
        PutDownRole,
        PickUpRole
    };


    void addItem(ArenaPlace* arenaPlace);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    QList<ArenaPlace*> getArenaSetup();


    int numberObjectsArena() const;
    int numberOfPlaceAreas() const;

public slots:

    void generateArenaSetup(QList<QVariant> places, QList<QString> objects, QList<QString> configurations, QList<QString> rotations, QList<QString> orientations, int objectsPerPlace);
    QString getObject(QString place, int index);
    QString getRotation(QString place, int index);
    QString getOrientation(QString place, int index);
    int getObjectCount(QString place);
    QString getConfiguration(QString place);



private:


    void readJSON(const QJsonObject &json);
    void writeJSON(QJsonObject &json) const;

    void clearList();

    int numberObjectsArena_;
    int numberOfPlaceAreas_;
    QList<ArenaPlace*> arenaSetup_;

protected:

      QHash<int, QByteArray> roleNames() const;





};

#endif // ARENASETUP_H
