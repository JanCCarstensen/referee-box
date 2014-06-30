#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QStringList>
#include <QtCore/QThread>
#include <QUdpSocket>

class QUdpSocket;

class UDPServer : public QThread{

    Q_OBJECT

public:
    explicit UDPServer(QObject *parent = 0);
    void run();

private slots:
    void readPendingDatagrams();
    void broadcastKeepalive();

private:
    QUdpSocket *udpSocket;
    qint16 port;

    QString getLocalIPAdress();

};

#endif // UDPSERVER_H
