include( ../zenom.pri )


# ControlBase
INCLUDEPATH += ../../zenom/znm-controlbase
DEPENDPATH += ../../zenom/znm-controlbase

INCLUDEPATH += ../../zenom/znm-core
DEPENDPATH += ../../zenom/znm-core

INCLUDEPATH += ../../zenom/znm-tools
DEPENDPATH += ../../zenom/znm-tools

LIBS += -L../../lib -lrt -lznm-controlbase -lznm-core -lznm-tools

