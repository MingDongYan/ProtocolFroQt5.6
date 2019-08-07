QT += core
QT -= gui

#CONFIG += c++11

TARGET = protoc_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    foo.pb.cc

HEADERS += \
    foo.pb.h
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

LIBS += -L$$PWD/ -lprotobuf
LIBS += -L$$PWD/ -lprotoc
LIBS += -L$$PWD/ -lprotobuf

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
