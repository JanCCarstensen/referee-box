#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QtCore/QThread>

#include "device.h"
#include "devicelist.h"

class QTcpServer;
class QTcpSocket;

class TCPServer : public QThread{

    Q_OBJECT

public:
    TCPServer(DeviceList* deviceList, QObject *parent = 0);
    virtual ~TCPServer();
    void run();
    void sendTaskSpec(QString taskSpec);

private slots:
    void newConnection();
    void waitForConnection();

private:
    QTcpServer *tcpServer_;
    DeviceList* deviceList_;


    QString getLocalIPAdress();

};

#endif // TCPSERVER_H





