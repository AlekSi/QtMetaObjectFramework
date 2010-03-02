QT = core testlib

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

HEADERS += tst_QtMetaObjectFramework.h

LIBS += -L../src/ -lQtMetaObjectFramework
