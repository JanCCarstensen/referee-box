#include <QtGui/QGuiApplication>

#include <QQmlExtensionPlugin>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "qtquick2applicationviewer.h"

#include "Networking/networking.h"
#include "Networking/devicelist.h"

#include "Tests/arena.h"
#include "Tests/bnttask.h"
#include "Tests/bmttask.h"
#include "Tests/arenaobject.h"
#include "Tests/arenaplace.h"

#include <QQuickView>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qRegisterMetaType<Device*>("Device");
    qRegisterMetaType<BNTItem*>("BNTItem");
    qRegisterMetaType<BMTItem*>("BMTItem");
    qRegisterMetaType<ArenaObject*>("ArenaObject");
    qRegisterMetaType<ArenaPlace*>("ArenaPlace");

    QtQuick2ApplicationViewer viewer;

    DeviceList deviceList;
    viewer.rootContext()->setContextProperty("deviceListModel", &deviceList);

    Arena arena;
    viewer.rootContext()->setContextProperty("arena", &arena);

    BNTTask bntTask;
    viewer.rootContext()->setContextProperty("bntTaskList", &bntTask);

    BMTTask bmtTask("BMT");
    viewer.rootContext()->setContextProperty("bmtTaskList", &bmtTask);

    BMTTask bttTask("BTT");
    viewer.rootContext()->setContextProperty("bttTaskList", &bttTask);

    BMTTask cbtTask("CBT");
    viewer.rootContext()->setContextProperty("cbtTaskList", &cbtTask);

    BMTTask pptTask("PPT");
    viewer.rootContext()->setContextProperty("pptTaskList", &pptTask);

    Networking* networking = new Networking(&deviceList);
    viewer.rootContext()->setContextProperty("Networking", networking);

    viewer.setMainQmlFile(QStringLiteral("qml/RefereeBox/main.qml"));
    viewer.showExpanded();




    return app.exec();
}
