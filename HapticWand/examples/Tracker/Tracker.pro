#--------------------------------------------------------------
#
# Zenom Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
#--------------------------------------------------------------

include( ../examples.pri )

TEMPLATE = app
CONFIG += console
#CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp \
    positioncontroller.cpp \
    setpoint.cpp \
    squarewavegenerator.cpp

HEADERS += \
    positioncontroller.h \
    setpoint.h \
    squarewavegenerator.h

