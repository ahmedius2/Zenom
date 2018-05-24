#--------------------------------------------------------------
#
# Zenom Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
#--------------------------------------------------------------

include( ../examples.pri )

TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    positioncontroller.cpp \
    setpoint.cpp \
    squarewavegenerator.cpp

HEADERS += \
    positioncontroller.h \
    setpoint.h \
    squarewavegenerator.h

