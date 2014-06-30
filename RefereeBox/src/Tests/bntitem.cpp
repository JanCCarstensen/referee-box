#include "bntitem.h"

BNTItem::BNTItem()
{
}

BNTItem::BNTItem(QString place, QString orientation){
    place_ = place;
    orientation_ = orientation;
}


BNTItem::~BNTItem (){

}

bool BNTItem::operator==(BNTItem other) const{
    if(this->place_ == other.getPlace() && this->orientation_ == other.getOrientation()){
        return true;
    }
    return false;
}

QString BNTItem::getPlace() const{
    return place_;
}



QString BNTItem::getOrientation() const{
    return orientation_;
}


void BNTItem::setPlace(QString place){
    place_ = place;
}

void BNTItem::setOrientation(QString orientation){
    orientation_ = orientation;
}
