include( ../HapticWand.pri )

# Zenom
INCLUDEPATH += $${ZENOM_HEADERS}
LIBS += -L$${ZENOM_LIBS} -lznm-controlbase -lznm-core -lznm-tools

# HapticWand
INCLUDEPATH += ../../HapticWand
DEPENDPATH += ../../HapticWand
LIBS += -L../../lib -lHapticWand


