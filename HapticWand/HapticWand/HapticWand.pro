#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T14:06:03
#
#-------------------------------------------------

include( ../HapticWand.pri )

#QT -= core gui
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
TARGET = HapticWand
TEMPLATE = lib

DEFINES += HAPTICWAND_LIBRARY

SOURCES += hapticwand.cpp \
    hil.cpp \
    hilexception.cpp \
    hapticwand_utils.cpp

HEADERS += hapticwand.h\
        HapticWand_global.h \
    hil.h \
    hilexception.h \
    q8Config.h \
    hapticwand_utils.h

INCLUDEPATH += /usr/include/qt4/QtCore

# build directory
DESTDIR = ../lib

# install
target.path = $${HAPTIC_WAND_INSTALL_LIBS}
INSTALLS += target

headers.files  = $${HEADERS}
headers.path   = $${HAPTIC_WAND_INSTALL_HEADERS}
INSTALLS += headers
