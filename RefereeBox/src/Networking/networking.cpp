#include "networking.h"
#include <QtNetwork>
#include <QQuickView>
#include <QQmlContext>

Networking::Networking(DeviceList* deviceList){

    tcpserver_ = new TCPServer(deviceList);
    tcpserver_->moveToThread(tcpserver_);
    tcpserver_->start();

    udpserver_ = new UDPServer();
    udpserver_->moveToThread(udpserver_);
    udpserver_->start();
}


Networking::~Networking(){
    delete tcpserver_;
    delete udpserver_;

}


void Networking::sendTaskSpec(QString taskSpec){
    tcpserver_->sendTaskSpec(taskSpec);
    udpserver_->sendTaskSepc(taskSpec);
}
