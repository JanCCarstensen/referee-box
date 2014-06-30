#ifndef ARENAOBJECT_H
#define ARENAOBJECT_H

#include <QString>
#include <QObject>


class ArenaObject: public QObject{

    Q_OBJECT

public:
    ArenaObject();

    QString object() const;
    void setObject(const QString &object);

    QString rotation() const;
    void setRotation(const QString &rotation);

    QString orientation() const;
    void setOrientation(const QString &orientation);

private:
    QString object_;
    QString rotation_;
    QString orientation_;


};



#endif // ARENAOBJECT_H
