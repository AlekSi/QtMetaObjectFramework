TEMPLATE = app
QT = core testlib
CONFIG += console
CONFIG -= app_bundle

HEADERS += tst_QtMetaObjectFramework.h

LIBS += -L../src -lQtMetaObjectFramework
