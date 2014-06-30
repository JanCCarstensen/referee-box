#include "device.h"

Device::Device(QTcpSocket *socket) : socket_( socket ){

    connect(socket_, SIGNAL (readyRead()), this, SLOT (readyRead()));
    connect(socket_, SIGNAL (disconnected()),this, SLOT (disconnected()));

    qDebug() << socket_->peerAddress() << socket_->peerName() << socket_->peerPort() << "connected on" << socket_->localPort();

    name_ = socket_->peerAddress().toString();
    color_ = QColor(50,255,50,255);
    disconnected_ = false;

}

Device::Device(){
    disconnected_ = false;
}

Device::Device(QString name, QTcpSocket *socket) : socket_( socket ){

    name_ = name;
    color_ = QColor(50,50,50,255);
    disconnected_ = false;
}

Device::~Device(){
    socket_->close();
}

bool Device::operator==(Device other) const{
    if(name_.compare(other.getName()) == 0 && color_ == other.getColor()){
        return true;
    } else {
        return false;
    }
}

void Device::readyRead(){
    qDebug() << socket_->peerAddress() << socket_->peerName() << socket_->peerPort() << "sent" << socket_->readAll();
}

void Device::connected(){
    qDebug() << socket_->peerAddress() << socket_->peerName() << socket_->peerPort() << "connected on" << socket_->localPort();
}

void Device::disconnected(){

    disconnected_ = true;
    qDebug() << socket_->peerAddress() << socket_->peerName() << socket_->peerPort() << "disconeted on" << socket_->localPort();
}


QString Device::getName() const{
    return name_;
}

QColor Device::getColor() const{
    return color_;
}

QTcpSocket* Device::getSocket() const{
    return socket_;
}

void Device::sendTaskSpec(QString taskSpec){
    socket_->write(taskSpec.toUtf8());
}


