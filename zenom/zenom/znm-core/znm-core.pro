#--------------------------------------------------------------
#
# Zenom Hard Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Zenom License, Version 1.0
#
#--------------------------------------------------------------

include( ../../zenom.pri )

VERSION = 1.0.0

QT       -= core gui

TARGET = znm-core
TEMPLATE = lib

DEFINES += ZNMCORE_LIBRARY

SOURCES += \
    variable.cpp \
    logvariable.cpp \
    controlvariable.cpp \
    datarepository.cpp

HEADERS +=\
        znm-core_global.h \
    variable.h \
    logvariable.h \
    controlvariable.h \
    datarepository.h

# Zenom Tools Library
INCLUDEPATH += ../znm-tools
DEPENDPATH += ../znm-tools
LIBS += -L../../lib -lznm-tools

# Xenomai
INCLUDEPATH +=  $${XENOMAI_HEADERS}
DEPENDPATH += $${XENOMAI_HEADERS}
LIBS += -L$${XENOMAI_LIBS} -lnative

# build directory
DESTDIR = ../../lib

# install
target.path = $${ZENOM_INSTALL_LIBS}
INSTALLS += target

headers.files  = $${HEADERS}
headers.path   = $${ZENOM_INSTALL_HEADERS}
INSTALLS += headers
