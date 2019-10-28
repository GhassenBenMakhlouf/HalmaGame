#-------------------------------------------------
#
# Project created by QtCreator 2019-03-19T12:36:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = halma
TEMPLATE = app


SOURCES +=\
    logik.cpp \
    zug.cpp \
    graphic/dialog.cpp \
    graphic/main.cpp \
    graphic/halma.cpp \
    graphic/secdialog.cpp \
    graphic/widget.cpp \
    supervisor.cpp \
    network.cpp

HEADERS  += \
    logik.h \
    zug.h \
    graphic/dialog.h \
    graphic/halma.h \
    graphic/secdialog.h \
    graphic/widget.h \
    supervisor.h \
    network.h

FORMS    += \
    graphic/dialog.ui \
    graphic/halma.ui \
    graphic/secdialog.ui \
    graphic/widget.ui


CONFIG += c++14

DISTFILES += \
    graphic/halma2 \
    graphic/login.png \
    graphic/Pic_One-01.png


