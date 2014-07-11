TEMPLATE = app

QT += qml quick widgets

SOURCES += src/main.cpp \
            src/bntitem.cpp \
            src/udpserver.cpp \
            src/bnttask.cpp \
            src/bntitem.cpp \
            src/bmtitem.cpp \
            src/bmttask.cpp \
            src/arena.cpp \
            src/arenaplace.cpp \
            src/arenaobject.cpp


RESOURCES += qml.qrc


HEADERS += \
            src/udpserver.h \
            src/bnttask.h \
            src/bntitem.h \
            src/bmtitem.h \
            src/bmttask.h \
            src/arena.h \
            src/arenaplace.h \
            src/arenaobject.h


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
