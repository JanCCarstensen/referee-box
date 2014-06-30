#ifndef BMTITEM_H
#define BMTITEM_H

#include <QString>

class BMTItem{

public:
    BMTItem();

    bool operator==(BMTItem other) const;


    QString desitnationType() const;
    void setDesitnationType(const QString &desitnationType);

    QString destination() const;
    void setDestination(const QString &destination);

    QString object() const;
    void setObject(const QString &object);

    QString sourceType() const;
    void setSourceType(const QString &sourceType);

    QString source() const;
    void setSource(const QString &source);

private:

    QString source_;
    QString sourceType_;
    QString object_;
    QString destination_;
    QString desitnationType_;

};

#endif // BMTITEM_H
