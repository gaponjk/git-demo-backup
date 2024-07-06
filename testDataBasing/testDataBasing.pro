QT += testlib
QT += gui core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testdata.cpp
SOURCES += \
    checker.cpp \
    deletewindow.cpp \
    insertionwindow.cpp \
    mainwindow.cpp \
    passWindow.cpp

HEADERS += \
    checker.h \
    deletewindow.h \
    insertionwindow.h \
    mainwindow.h \
    passWindow.h

FORMS += \
    deletewindow.ui \
    insertionwindow.ui \
    mainwindow.ui
