/********************************************************************************
** Form generated from reading UI file 'plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWINDOW_H
#define UI_PLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "plot/plot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotWindow
{
public:
    QAction *actionAttach_Log_Variable;
    QAction *actionSet_Time_Interval;
    QAction *actionAutoscale;
    QAction *action_Contents;
    QAction *actionI_mport;
    QAction *action_Export;
    QAction *action_Close;
    QAction *action_Open;
    QAction *action_Save;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    Plot *plot;
    QToolBar *toolBar;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QMenu *menu_Plot;

    void setupUi(QMainWindow *PlotWindow)
    {
        if (PlotWindow->objectName().isEmpty())
            PlotWindow->setObjectName(QString::fromUtf8("PlotWindow"));
        PlotWindow->resize(600, 400);
        actionAttach_Log_Variable = new QAction(PlotWindow);
        actionAttach_Log_Variable->setObjectName(QString::fromUtf8("actionAttach_Log_Variable"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/zenom/resources/link.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAttach_Log_Variable->setIcon(icon);
        actionSet_Time_Interval = new QAction(PlotWindow);
        actionSet_Time_Interval->setObjectName(QString::fromUtf8("actionSet_Time_Interval"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/plot/resources/timeinterval.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_Time_Interval->setIcon(icon1);
        actionAutoscale = new QAction(PlotWindow);
        actionAutoscale->setObjectName(QString::fromUtf8("actionAutoscale"));
        actionAutoscale->setCheckable(true);
        actionAutoscale->setChecked(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/plot/resources/autoscale.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAutoscale->setIcon(icon2);
        action_Contents = new QAction(PlotWindow);
        action_Contents->setObjectName(QString::fromUtf8("action_Contents"));
        actionI_mport = new QAction(PlotWindow);
        actionI_mport->setObjectName(QString::fromUtf8("actionI_mport"));
        action_Export = new QAction(PlotWindow);
        action_Export->setObjectName(QString::fromUtf8("action_Export"));
        action_Close = new QAction(PlotWindow);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        action_Open = new QAction(PlotWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save = new QAction(PlotWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        centralwidget = new QWidget(PlotWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plot = new Plot(centralwidget);
        plot->setObjectName(QString::fromUtf8("plot"));

        gridLayout->addWidget(plot, 0, 0, 1, 1);

        PlotWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(PlotWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        PlotWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(PlotWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 23));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_Plot = new QMenu(menubar);
        menu_Plot->setObjectName(QString::fromUtf8("menu_Plot"));
        PlotWindow->setMenuBar(menubar);

        toolBar->addAction(actionAutoscale);
        toolBar->addSeparator();
        toolBar->addAction(actionSet_Time_Interval);
        toolBar->addSeparator();
        toolBar->addAction(actionAttach_Log_Variable);
        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Plot->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Save);
        menu_File->addSeparator();
        menu_File->addAction(action_Export);
        menu_File->addSeparator();
        menu_File->addAction(action_Close);
        menu_Help->addAction(action_Contents);
        menu_Plot->addAction(actionAutoscale);
        menu_Plot->addAction(actionSet_Time_Interval);
        menu_Plot->addSeparator();
        menu_Plot->addAction(actionAttach_Log_Variable);

        retranslateUi(PlotWindow);

        QMetaObject::connectSlotsByName(PlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlotWindow)
    {
        PlotWindow->setWindowTitle(QApplication::translate("PlotWindow", "Plot", 0, QApplication::UnicodeUTF8));
        actionAttach_Log_Variable->setText(QApplication::translate("PlotWindow", "Attach &Log Variable...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAttach_Log_Variable->setToolTip(QApplication::translate("PlotWindow", "Attach Log Variable to Plot", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSet_Time_Interval->setText(QApplication::translate("PlotWindow", "Set &Time Interval...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSet_Time_Interval->setToolTip(QApplication::translate("PlotWindow", "Sets Plot Time Interval", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAutoscale->setText(QApplication::translate("PlotWindow", "&Autoscale", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAutoscale->setToolTip(QApplication::translate("PlotWindow", "Autoscale", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Contents->setText(QApplication::translate("PlotWindow", "&Contents", 0, QApplication::UnicodeUTF8));
        action_Contents->setShortcut(QApplication::translate("PlotWindow", "F1", 0, QApplication::UnicodeUTF8));
        actionI_mport->setText(QApplication::translate("PlotWindow", "I&mport...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionI_mport->setToolTip(QApplication::translate("PlotWindow", "Import", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Export->setText(QApplication::translate("PlotWindow", "&Export...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Export->setToolTip(QApplication::translate("PlotWindow", "Export", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Close->setText(QApplication::translate("PlotWindow", "&Close", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("PlotWindow", "&Open...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Open->setToolTip(QApplication::translate("PlotWindow", "Open Zenom Plot File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Save->setText(QApplication::translate("PlotWindow", "&Save...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Save->setToolTip(QApplication::translate("PlotWindow", "Save as Zenom Plot File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("PlotWindow", "Plot Tool Bar", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("PlotWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("PlotWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_Plot->setTitle(QApplication::translate("PlotWindow", "&Plot", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlotWindow: public Ui_PlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWINDOW_H
