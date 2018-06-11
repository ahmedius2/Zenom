#--------------------------------------------------------------
#
# Zenom Hard Real-Time Simulation Enviroment
# Copyright (C) 2013
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Zenom License, Version 1.0
#
#--------------------------------------------------------------

include( ../examples.pri )

TEMPLATE = app
CONFIG += console
CONFIG += qt
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
SOURCES += main.cpp
