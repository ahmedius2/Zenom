#--------------------------------------------------------------
#
# Zenom Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
#--------------------------------------------------------------

TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

# Xenomai
INCLUDEPATH +=  /usr/xenomai/include
DEPENDPATH += /usr/xenomai/include
LIBS += -L/usr/xenomai/lib -lnative -lxenomai

# Zenom
INCLUDEPATH += /usr/include/zenom
LIBS += -L/usr/lib64 -lznm-controlbase -lznm-core -lznm-tools

