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

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zenom
TEMPLATE = app


SOURCES += main.cpp\
        zenom.cpp \
    messagelistenertask.cpp \
    controlvariableswidget.cpp \
    logvariableswidget.cpp \
    widget/colorbutton.cpp \
    widget/statusbar.cpp \
    widget/checkedheader.cpp \
    widget/logvariabletreewidget.cpp \
    widget/logvariableitem.cpp \
    gauge/radialgaugesettingwidget.cpp \
    gauge/radialgauge.cpp \
    gauge/numericgaugesettingwidget.cpp \
    gauge/numericgauge.cpp \
    gauge/lineargaugesettingwidget.cpp \
    gauge/lineargauge.cpp \
    gauge/gaugewidget.cpp \
    gauge/gaugemanager.cpp \
    gauge/creategaugedialog.cpp \
    gauge/abstractgauge.cpp \
    gauge/editgaugedialog.cpp \
    scene/scenemanager.cpp \
    scene/scenewindow.cpp \
    scene/viewerwidget.cpp \
    scene/viewpoint.cpp \
    scene/binddialog.cpp \
    scene/setargumentdialog.cpp \
    scene/logvariableinterface.cpp \
    scene/updatefunctor.cpp \
    scene/nodedata.cpp \
    scene/visitors/transformvisitor.cpp \
    scene/visitors/shapevisitor.cpp \
    scene/visitors/nodevisitor.cpp \
    scene/visitors/drawablevisitor.cpp \
    scene/visitors/basevisitor.cpp \
    plot/plotmanager.cpp \
    plot/plotwindow.cpp \
    plot/attachlogvariabledialog.cpp \
    plot/plotcurve.cpp \
    plot/curvecolorgenerator.cpp \
    plot/legenditem.cpp \
    plot/plot.cpp \
    plot/plotmagnifier.cpp \
    widget/output.cpp \
    aboutdialog.cpp \
    utility/matlabstream.cpp \
    widget/linesizecombobox.cpp

HEADERS  += zenom.h \
    messagelistenertask.h \
    controlvariableswidget.h \
    logvariableswidget.h \
    widget/colorbutton.h \
    widget/statusbar.h \
    widget/checkedheader.h \
    widget/logvariabletreewidget.h \
    widget/logvariableitem.h \
    gauge/radialgaugesettingwidget.h \
    gauge/radialgauge.h \
    gauge/numericgaugesettingwidget.h \
    gauge/numericgauge.h \
    gauge/lineargaugesettingwidget.h \
    gauge/lineargauge.h \
    gauge/gaugewidget.h \
    gauge/gaugemanager.h \
    gauge/creategaugedialog.h \
    gauge/abstractgauge.h \
    gauge/editgaugedialog.h \
    scene/scenemanager.h \
    scene/scenewindow.h \
    scene/viewerwidget.h \
    scene/viewpoint.h \
    scene/binddialog.h \
    scene/setargumentdialog.h \
    scene/logvariableinterface.h \
    scene/updatefunctor.h \
    scene/nodedata.h \
    scene/visitors/transformvisitor.h \
    scene/visitors/shapevisitor.h \
    scene/visitors/nodevisitor.h \
    scene/visitors/drawablevisitor.h \
    scene/visitors/basevisitor.h \
    plot/plotmanager.h \
    plot/plotwindow.h \
    plot/attachlogvariabledialog.h \
    plot/plotcurve.h \
    plot/curvecolorgenerator.h \
    plot/legenditem.h \
    plot/plot.h \
    plot/plotmagnifier.h \
    widget/output.h \
    aboutdialog.h \
    utility/matlabstream.h \
    widget/linesizecombobox.h

FORMS    += zenom.ui \
    controlvariableswidget.ui \
    logvariableswidget.ui \
    widget/statusbar.ui \
    gauge/radialgaugesettingwidget.ui \
    gauge/numericgaugesettingwidget.ui \
    gauge/lineargaugesettingwidget.ui \
    gauge/gaugewidget.ui \
    gauge/creategaugedialog.ui \
    gauge/editgaugedialog.ui \
    scene/binddialog.ui \
    scene/setargumentdialog.ui \
    scene/scenewindow.ui \
    plot/plotwindow.ui \
    plot/attachlogvariabledialog.ui \
    plot/legenditem.ui \
    aboutdialog.ui

RESOURCES += \
    zenom.qrc

# Xenomai
INCLUDEPATH +=  $${XENOMAI_HEADERS}
DEPENDPATH += $${XENOMAI_HEADERS}
LIBS += -L$${XENOMAI_LIBS} -lnative -lxenomai

# Qwt
INCLUDEPATH +=  $${QWT_HEADERS}
DEPENDPATH += $${QWT_HEADERS}
LIBS += -L$${QWT_LIBS} -lqwt

# OpenSceneGraph
INCLUDEPATH +=  $${OSG_HEADERS}
DEPENDPATH += $${OSG_HEADERS}
LIBS += -L$${OSG_LIBS} -losgViewer -losgGA -losg -losgQt -losgDB -losgSim -lOpenThreads

# Zenom Core Library
INCLUDEPATH += ../znm-core
DEPENDPATH += ../znm-core
LIBS += -L../../lib -lznm-core

# Zenom Tools Library
INCLUDEPATH += ../znm-tools
DEPENDPATH += ../znm-tools
LIBS += -L../../lib -lznm-tools

# build directory
DESTDIR = ../../bin

# install
target.path = $${ZENOM_INSTALL_BINS}
INSTALLS += target
