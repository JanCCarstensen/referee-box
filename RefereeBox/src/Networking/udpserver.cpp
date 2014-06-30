#include "udpserver.h"
#include <QtNetwork>
#include <QtDebug>

#include <stdlib.h>

UDPServer::UDPServer(QObject *parent) : QThread(parent){
    port = 11112;

}

void UDPServer::run(){

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, port);

    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
    qDebug() << "The UDPServer is running on ip:" << getLocalIPAdress() << "port:"<< port;

    QTimer::singleShot(0, this, SLOT(broadcastKeepalive()));
    exec();
}

void UDPServer::readPendingDatagrams(){
    qDebug() << "incomming";
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        qDebug() << "[" << sender.toString() << ":" << senderPort << "]" << datagram.data();
    }
//    qDebug() << udpSocket->readAll();
}


void UDPServer::broadcastKeepalive(){
    QByteArray Data;
    Data.append("<RefBox>");
    udpSocket->writeDatagram(Data, QHostAddress::Broadcast, port);
    QTimer::singleShot(5000, this, SLOT(broadcastKeepalive()));
}

QString UDPServer::getLocalIPAdress(){
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


