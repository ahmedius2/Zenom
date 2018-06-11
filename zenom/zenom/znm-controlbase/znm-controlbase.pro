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
TARGET = znm-controlbase
TEMPLATE = lib

DEFINES += ZNMCONTROLBASE_LIBRARY

SOURCES += controlbase.cpp \
    lifecycletask.cpp \
    looptask.cpp

HEADERS += controlbase.h\
    lifecycletask.h \
    looptask.h

# Zenom Core Library
INCLUDEPATH += ../znm-core
DEPENDPATH += ../znm-core
LIBS += -L../../lib/ -lznm-core

# Zenom Tools Library
INCLUDEPATH += ../znm-tools
DEPENDPATH += ../znm-tools
LIBS += -L../../lib -lznm-tools

# build directory
DESTDIR = ../../lib

# install
target.path = $${ZENOM_INSTALL_LIBS}
INSTALLS += target

headers.files  = $${HEADERS}
headers.path   = $${ZENOM_INSTALL_HEADERS}
INSTALLS += headers

