#ifndef BNTITEM_H
#define BNTITEM_H

#include <QString>
#include <QObject>

class BNTItem : public QObject{

    Q_OBJECT

    Q_PROPERTY(QString place READ getPlace WRITE setPlace)
    Q_PROPERTY(QString orientation READ getOrientation WRITE setOrientation)

public:
    BNTItem(QString place, QString orientation);
    BNTItem();
    virtual ~BNTItem ();

    bool operator==(BNTItem other) const;

    QString getPlace() const;
    QString getOrientation() const;
    void setPlace(QString place);
    void setOrientation(QString orientation);

private:

QString place_;
QString orientation_;

};

#endif // BNTITEM_H
