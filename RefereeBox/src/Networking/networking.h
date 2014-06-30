#ifndef NETWORKING_H
#define NETWORKING_H

#include "tcpserver.h"
#include "udpserver.h"
#include "devicelist.h"
#include <QObject>

class Networking: public QObject{

    Q_OBJECT

public:
    Networking(DeviceList* deviceList);
    ~Networking();

public slots:

    void sendTaskSpec(QString taskSpec);

private:

    TCPServer* tcpserver_;
    UDPServer* udpserver_;


};

#endif // NETWORKING_H
