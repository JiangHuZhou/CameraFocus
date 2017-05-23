#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T23:35:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraTest
TEMPLATE = app


SOURCES += main.cpp\
        Cameradialog.cpp \
    Threadworker.cpp \
    Focusmeasure.cpp \
    hillclimbsearch.cpp \
    searchthread.cpp \
    dosql.cpp


HEADERS  += Cameradialog.h \
    Threadworker.h \
    include/PixelFormatConvert.h \
    include/PixelFormatConvertTBB.h \
    include/VwCamera.h \
    include/VwGigE.API.h \
    include/VwGigE.Global.h \
    include/VwGigE.h \
    include/VwImageProcess.h \
    include/VwInterface.h \
    include/VwSDK.Error.h \
    include/VwSDK.h \
    include/VwSerial.h \
    Focusmeasure.h \
    hillclimbsearch.h \
    include/DTStageDriver.h \
    searchthread.h \
    dosql.h

FORMS    += Cameradialog.ui

INCLUDEPATH += D:/opencv32/opencv/build/include \
               D:/opencv32/opencv/build/include/opencv \
               D:/opencv32/opencv/build/include/opencv2

LIBS += -L$$PWD/lib/ -lVwGigE.V7 \
        D:/opencv32/opencv/build/x86/vc14/lib/opencv_*.lib \
        -L$$PWD/lib/ -lDTStageDriver

RESOURCES += \
    res.qrc
