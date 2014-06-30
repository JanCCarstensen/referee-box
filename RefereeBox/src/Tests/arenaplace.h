#ifndef ARENAPLACE_H
#define ARENAPLACE_H

#include "arenaobject.h"

#include <QString>
#include <QAbstractListModel>
#include <QList>
#include <QVariant>

class ArenaPlace : public QAbstractListModel{

    Q_OBJECT

public:
    ArenaPlace();
    ~ArenaPlace();

    QString getPlace() const;
    void setPlace(const QString &value);

    QString getConfiguration() const;
    void setConfiguration(const QString &value);

    QList<ArenaObject*> getObjects() const;
    void setObjects(const QList<ArenaObject*> &value);

    void append(ArenaObject* object);


    QList<QVariant> getObjectNames() const;
    QList<QVariant> getOrientations() const;
    QList<QVariant> getRotations() const;

    enum ArenaObjectRoles {
        ObjectRole = Qt::UserRole + 1,
        OrientationRole,
        RotationRole
    };


    void addItem(ArenaObject* arenaPlace);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:

    QString place_;
    QString configuration_;
    QList<ArenaObject*> objects_;

protected:

      QHash<int, QByteArray> roleNames() const;

};

#endif // ARENAPLACE_H
