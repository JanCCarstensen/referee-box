#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QTcpSocket>
#include <QHostAddress>


class QTcpSocket;

class Device: public QObject{

    Q_OBJECT

public:
    Device();
    Device(QTcpSocket *socket);
    Device(QString name, QTcpSocket *socket = 0);
    virtual ~Device ();

    bool operator==(Device other) const;

    QString getName() const;
    QColor getColor() const;
    QTcpSocket* getSocket() const;

    void sendTaskSpec(QString taskSpec);

    bool disconnected_;


private:
    QString name_;
    QColor color_;
    QTcpSocket *socket_;


private slots:
    void readyRead ();
    void connected ();
    void disconnected ();

};

#endif // DEVICE_H
