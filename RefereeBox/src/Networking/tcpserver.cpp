#include "tcpserver.h"
#include <QtNetwork>
#include <QtDebug>

#include <stdlib.h>

TCPServer::TCPServer(DeviceList* deviceList, QObject *parent) : QThread(parent){

    tcpServer_ = new QTcpServer(this);
    deviceList_ = deviceList;
}

TCPServer::~TCPServer(){
//    qDeleteAll(deviceList_->begin(), deviceList_->end());
//    deviceList_->clear();
}

void TCPServer::run (){
    if (!tcpServer_->listen(QHostAddress::Any, 11111)) {
        qDebug() << "Unable to start the server: %1" << tcpServer_->errorString();
//        close(0);
        return;
    } else {
        QString ipAddress = getLocalIPAdress();
        qDebug() << "The TCPServer is running on ip:" << ipAddress <<"port:"<< tcpServer_->serverPort();
        connect(tcpServer_, SIGNAL(newConnection()), this, SLOT(newConnection()));
    }
    QTimer::singleShot(0, this, SLOT(waitForConnection()));
    exec();
}

void TCPServer::waitForConnection(){
    tcpServer_->waitForNewConnection(100);

    deviceList_->checkDevices();

    QTimer::singleShot(0, this, SLOT(waitForConnection()));
}


void TCPServer::sendTaskSpec(QString taskSpec){
    Device* selected = deviceList_->getSelectedDevice();
    if (selected != NULL){
        selected->sendTaskSpec(taskSpec);
        qDebug() << "Sending: " << taskSpec;
    } else {
        qDebug() << "No valid Device selected";
    }

}

QString TCPServer::getLocalIPAdress(){
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}

void TCPServer::newConnection(){

    Device* device = new Device(tcpServer_->nextPendingConnection());
    deviceList_->addItem(device);

}
