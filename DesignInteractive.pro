#-------------------------------------------------
#
# Project created by QtCreator 2019-05-16T09:53:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesignInteractive
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        BlockPropertiesDialog.cpp \
        BuildingPropertiesDialog.cpp \
        block.cpp \
        building.cpp \
        cityscape.cpp \
        cityview.cpp \
        index.cpp \
        legends.cpp \
        main.cpp \
        publicpropertiesdialog.cpp \
        publicspace.cpp \
        user.cpp

HEADERS += \
        ../build-DesignInteractive-Desktop_Qt_5_12_3_MinGW_32_bit-Debug/ui_index.h \
        BlockPropertiesDialog.h \
        BuildingPropertiesDialog.h \
        block.h \
        building.h \
        cityscape.h \
        cityview.h \
        index.h \
        legends.h \
        publicpropertiesdialog.h \
        publicspace.h \
        user.h

FORMS += \
        BlockPropertiesDialog.ui \
        BuildingPropertiesDialog.ui \
        PublicPropertiesDialog.ui \
        form.ui \
        index.ui \
        legends.ui \
        mainwindow.ui \
        user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
