# Add more folders to ship with the application, here
folder_01.source = qml/RefereeBox
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/Networking/networking.cpp \
    src/Networking/device.cpp \
    src/Networking/tcpserver.cpp \
    src/Networking/udpserver.cpp \
    src/Networking/devicelist.cpp \
    src/Tests/bnttask.cpp \
    src/Tests/bntitem.cpp \
    src/Tests/bmtitem.cpp \
    src/Tests/bmttask.cpp \
    src/Tests/arena.cpp \
    src/Tests/arenaplace.cpp \
    src/Tests/arenaobject.cpp


OTHER_FILES += \
    qml/RefereeBox/teamListView.qml \
    qml/RefereeBox/Views/qmldir \
    qml/RefereeBox/Rescources/qmldir \
    qml/RefereeBox/Rescources/teams.xml \
    qml/RefereeBox/main.qml \
    qml/RefereeBox/Views/TeamListView.qml \
    qml/RefereeBox/Models/PlacesModel.qml\
    qml/RefereeBox/Models/qmldir \
    qml/RefereeBox/Rescources/objects.xml \
    qml/RefereeBox/Rescources/itemOrientations.xml


HEADERS += \
    src/Networking/networking.h \
    src/Networking/device.h \
    src/Networking/tcpserver.h \
    src/Networking/udpserver.h \
    src/Networking/devicelist.h \
    src/Tests/bnttask.h \
    src/Tests/bntitem.h \
    src/Tests/bmtitem.h \
    src/Tests/bmttask.h \
    src/Tests/arena.h \
    src/Tests/arenaplace.h \
    src/Tests/arenaobject.h


# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

QT += network 
