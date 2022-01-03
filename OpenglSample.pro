#-------------------------------------------------
#
# Project created by QtCreator 2021-02-05T16:00:19
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenglSample
TEMPLATE = app

DESTDIR = $$PWD/bin

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    stlfileloader.cpp \
    kinematics.cpp \
    ddr4robotwidget.cpp \
    ddr6robotwidget.cpp \
    robotcontrolform.cpp \
    robot3dforddr4form.cpp \
    robot3dforddr6form.cpp \
    showdatetime.cpp \
    showcpumemory.cpp \
    rrglwidget.cpp

HEADERS  += mainwindow.h \
    stlfileloader.h \
    kinematics.h \
    ddr4robotwidget.h \
    ddr6robotwidget.h \
    robotcontrolform.h \
    robot3dforddr4form.h \
    robot3dforddr6form.h \
    showdatetime.h \
    showcpumemory.h \
    rrglwidget.h

FORMS    += mainwindow.ui \
    robotcontrolform.ui \
    robot3dforddr4form.ui \
    robot3dforddr6form.ui

DISTFILES +=

LIBS += -lglut -lGLU

#INCLUDEPATH += $$PWD/includes

RESOURCES += \
    images.qrc

