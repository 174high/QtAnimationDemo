#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T19:37:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAnimationDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

INCLUDEPATH += /home/johnny/imx6-2/imx6/thirdpartlib/opencv/install/include
LIBS += ../../lib/libopencv_core.so \ 
        ../../lib/libopencv_highgui.so \
        ../../lib/libopencv_imgproc.so \
        ../../lib/libopencv_videoio.so \
        ../../lib/libopencv_imgcodecs.so \
        -lpthread

FORMS    += mainwindow.ui
