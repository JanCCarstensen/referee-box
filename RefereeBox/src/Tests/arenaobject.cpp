#include "arenaobject.h"

ArenaObject::ArenaObject(){
    object_ = "";
    rotation_ = "";
    orientation_ = "";
}

QString ArenaObject::object() const
{
    return object_;
}

void ArenaObject::setObject(const QString &object)
{
    object_ = object;
}
QString ArenaObject::rotation() const
{
    return rotation_;
}

void ArenaObject::setRotation(const QString &rotation)
{
    rotation_ = rotation;
}
QString ArenaObject::orientation() const
{
    return orientation_;
}

void ArenaObject::setOrientation(const QString &orientation)
{
    orientation_ = orientation;
}



