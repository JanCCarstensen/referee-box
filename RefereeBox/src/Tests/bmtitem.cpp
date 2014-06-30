#include "bmtitem.h"

BMTItem::BMTItem(){


}

bool BMTItem::operator==(BMTItem other) const{

   if (desitnationType() == other.desitnationType() &&
           destination() == other.destination() &&
           object() == other.object() &&
           sourceType() == other.sourceType() &&
           source() == other.source()){
       return true;
   }
   return false;
}

QString BMTItem::desitnationType() const
{
    return desitnationType_;
}

void BMTItem::setDesitnationType(const QString &desitnationType)
{
    desitnationType_ = desitnationType;
}
QString BMTItem::destination() const
{
    return destination_;
}

void BMTItem::setDestination(const QString &destination)
{
    destination_ = destination;
}
QString BMTItem::object() const
{
    return object_;
}

void BMTItem::setObject(const QString &object)
{
    object_ = object;
}
QString BMTItem::sourceType() const
{
    return sourceType_;
}

void BMTItem::setSourceType(const QString &sourceType)
{
    sourceType_ = sourceType;
}
QString BMTItem::source() const
{
    return source_;
}

void BMTItem::setSource(const QString &source)
{
    source_ = source;
}





