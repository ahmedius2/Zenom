#--------------------------------------------------------------
#
# Zenom Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Zenom License, Version 1.0
#
#--------------------------------------------------------------

include( ../../zenom.pri )

VERSION = 1.0.0

QT       -= core gui
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
TARGET   = znm-tools
TEMPLATE = lib

DEFINES += ZNMTOOLS_LIBRARY

SOURCES += \
    TaskXn.cpp \
    SharedMem.cpp \
    MsgQueue.cpp

HEADERS +=\
    TaskXn.h \
    SharedMem.h \
    MsgQueue.h \
    znm-tools_global.h


# build directory
DESTDIR = ../../lib

# install
target.path = $${ZENOM_INSTALL_LIBS}
INSTALLS += target

headers.files  = $${HEADERS}
headers.path   = $${ZENOM_INSTALL_HEADERS}
INSTALLS += headers

LIBS += -lrt

FORMS +=

DISTFILES +=
