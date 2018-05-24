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

TARGET = znm-math
TEMPLATE = lib

DEFINES += ZNMMATH_LIBRARY

SOURCES += \
    Transform.cpp

HEADERS += \
    VectorBase.hpp \
    Vector.hpp \
    Transform.hpp \
    RowVector.hpp \
    ODESolverRK4.hpp \
    MatrixInitializer.hpp \
    MatrixBase.hpp \
    Matrix.hpp \
    MathException.hpp \
    LowpassFilter.hpp \
    Integrator.hpp \
    Differentiator4O.hpp \
    Differentiator.hpp \
    ColumnVector.hpp \
    Adams3Integrator.hpp \
    ButterworthFilter.hpp \
    Euler2DigitalFilter.hpp

# build directory
DESTDIR = ../../lib

# install
target.path = $${ZENOM_INSTALL_LIBS}
INSTALLS += target

headers.files  = $${HEADERS}
headers.path   = $${ZENOM_INSTALL_HEADERS}
INSTALLS += headers
