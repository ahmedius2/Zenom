include( ../HapticWand.pri )

# Xenomai
INCLUDEPATH +=  $${XENOMAI_HEADERS}
DEPENDPATH += $${XENOMAI_HEADERS}
LIBS += -L$${XENOMAI_LIBS} -lxenomai -lrtdm

# Zenom
INCLUDEPATH += $${ZENOM_HEADERS}
LIBS += -L$${ZENOM_LIBS} -lznm-controlbase -lznm-core -lznm-tools

# HapticWand
INCLUDEPATH += ../../HapticWand
DEPENDPATH += ../../HapticWand
LIBS += -L../../lib -lHapticWand


