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
INCLUDEPATH +=  %XENOMAI_HEADERS%
DEPENDPATH += %XENOMAI_HEADERS%
LIBS += -L%XENOMAI_LIBS% -lnative -lxenomai

# Zenom
INCLUDEPATH += /usr/local/include/zenom
LIBS += -L/usr/local/lib64 -lznm-controlbase -lznm-core -lznm-tools

