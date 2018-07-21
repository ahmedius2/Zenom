/********************************************************************************
** Form generated from reading UI file 'zenom.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZENOM_H
#define UI_ZENOM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "widget/output.h"

QT_BEGIN_NAMESPACE

class Ui_Zenom
{
public:
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionExit;
    QAction *actionWatch;
    QAction *actionReload;
    QAction *actionScene;
    QAction *actionPlot;
    QAction *action_Contents;
    QAction *action_About_zenom;
    QAction *actionExport_as_Matlab;
    QAction *actionClear_Recent_Projects_Menu;
    QAction *actionCamera;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    Output *output;
    QGridLayout *gridLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QGridLayout *gridLayout_2;
    QLabel *durationLabel;
    QLineEdit *duration;
    QLineEdit *frequency;
    QLabel *frequencyLabel;
    QLabel *frequencyAbb;
    QLabel *durationAbb;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuRecent_P_rojects;
    QMenu *menu_View;
    QMenu *menu_Help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Zenom)
    {
        if (Zenom->objectName().isEmpty())
            Zenom->setObjectName(QString::fromUtf8("Zenom"));
        Zenom->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/zenom/resources/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Zenom->setWindowIcon(icon);
        actionOpen_Project = new QAction(Zenom);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        actionSave_Project = new QAction(Zenom);
        actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
        actionExit = new QAction(Zenom);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionWatch = new QAction(Zenom);
        actionWatch->setObjectName(QString::fromUtf8("actionWatch"));
        actionReload = new QAction(Zenom);
        actionReload->setObjectName(QString::fromUtf8("actionReload"));
        actionScene = new QAction(Zenom);
        actionScene->setObjectName(QString::fromUtf8("actionScene"));
        actionPlot = new QAction(Zenom);
        actionPlot->setObjectName(QString::fromUtf8("actionPlot"));
        action_Contents = new QAction(Zenom);
        action_Contents->setObjectName(QString::fromUtf8("action_Contents"));
        action_About_zenom = new QAction(Zenom);
        action_About_zenom->setObjectName(QString::fromUtf8("action_About_zenom"));
        actionExport_as_Matlab = new QAction(Zenom);
        actionExport_as_Matlab->setObjectName(QString::fromUtf8("actionExport_as_Matlab"));
        actionClear_Recent_Projects_Menu = new QAction(Zenom);
        actionClear_Recent_Projects_Menu->setObjectName(QString::fromUtf8("actionClear_Recent_Projects_Menu"));
        actionCamera = new QAction(Zenom);
        actionCamera->setObjectName(QString::fromUtf8("actionCamera"));
        centralWidget = new QWidget(Zenom);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        output = new Output(centralWidget);
        output->setObjectName(QString::fromUtf8("output"));
        QFont font;
        font.setPointSize(10);
        output->setFont(font);

        gridLayout_3->addWidget(output, 1, 0, 1, 3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);
        startButton->setMinimumSize(QSize(71, 71));

        gridLayout->addWidget(startButton, 0, 0, 1, 1);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);
        stopButton->setMinimumSize(QSize(71, 71));

        gridLayout->addWidget(stopButton, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(10, -1, -1, -1);
        durationLabel = new QLabel(centralWidget);
        durationLabel->setObjectName(QString::fromUtf8("durationLabel"));

        gridLayout_2->addWidget(durationLabel, 1, 0, 1, 1);

        duration = new QLineEdit(centralWidget);
        duration->setObjectName(QString::fromUtf8("duration"));

        gridLayout_2->addWidget(duration, 1, 1, 1, 1);

        frequency = new QLineEdit(centralWidget);
        frequency->setObjectName(QString::fromUtf8("frequency"));

        gridLayout_2->addWidget(frequency, 0, 1, 1, 1);

        frequencyLabel = new QLabel(centralWidget);
        frequencyLabel->setObjectName(QString::fromUtf8("frequencyLabel"));

        gridLayout_2->addWidget(frequencyLabel, 0, 0, 1, 1);

        frequencyAbb = new QLabel(centralWidget);
        frequencyAbb->setObjectName(QString::fromUtf8("frequencyAbb"));

        gridLayout_2->addWidget(frequencyAbb, 0, 2, 1, 1);

        durationAbb = new QLabel(centralWidget);
        durationAbb->setObjectName(QString::fromUtf8("durationAbb"));

        gridLayout_2->addWidget(durationAbb, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 2, 1, 1);

        Zenom->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Zenom);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuRecent_P_rojects = new QMenu(menu_File);
        menuRecent_P_rojects->setObjectName(QString::fromUtf8("menuRecent_P_rojects"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        Zenom->setMenuBar(menuBar);
        statusBar = new QStatusBar(Zenom);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Zenom->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(actionOpen_Project);
        menu_File->addAction(actionSave_Project);
        menu_File->addSeparator();
        menu_File->addAction(actionReload);
        menu_File->addSeparator();
        menu_File->addAction(actionExport_as_Matlab);
        menu_File->addSeparator();
        menu_File->addAction(menuRecent_P_rojects->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionExit);
        menuRecent_P_rojects->addAction(actionClear_Recent_Projects_Menu);
        menu_View->addAction(actionWatch);
        menu_View->addAction(actionPlot);
        menu_View->addAction(actionScene);
        menu_View->addSeparator();
        menu_View->addAction(actionCamera);
        menu_Help->addAction(action_Contents);
        menu_Help->addSeparator();
        menu_Help->addAction(action_About_zenom);

        retranslateUi(Zenom);

        QMetaObject::connectSlotsByName(Zenom);
    } // setupUi

    void retranslateUi(QMainWindow *Zenom)
    {
        Zenom->setWindowTitle(QApplication::translate("Zenom", "Zenom", 0, QApplication::UnicodeUTF8));
        actionOpen_Project->setText(QApplication::translate("Zenom", "&Open Project...", 0, QApplication::UnicodeUTF8));
        actionOpen_Project->setShortcut(QApplication::translate("Zenom", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_Project->setText(QApplication::translate("Zenom", "&Save", 0, QApplication::UnicodeUTF8));
        actionSave_Project->setShortcut(QApplication::translate("Zenom", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("Zenom", "E&xit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("Zenom", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionWatch->setText(QApplication::translate("Zenom", "&Watch...", 0, QApplication::UnicodeUTF8));
        actionReload->setText(QApplication::translate("Zenom", "&Reload", 0, QApplication::UnicodeUTF8));
        actionScene->setText(QApplication::translate("Zenom", "&Scene", 0, QApplication::UnicodeUTF8));
        actionPlot->setText(QApplication::translate("Zenom", "&Plot", 0, QApplication::UnicodeUTF8));
        action_Contents->setText(QApplication::translate("Zenom", "&Contents", 0, QApplication::UnicodeUTF8));
        action_Contents->setShortcut(QApplication::translate("Zenom", "F1", 0, QApplication::UnicodeUTF8));
        action_About_zenom->setText(QApplication::translate("Zenom", "&About...", 0, QApplication::UnicodeUTF8));
        actionExport_as_Matlab->setText(QApplication::translate("Zenom", "Export as Matlab...", 0, QApplication::UnicodeUTF8));
        actionClear_Recent_Projects_Menu->setText(QApplication::translate("Zenom", "Clear Menu", 0, QApplication::UnicodeUTF8));
        actionCamera->setText(QApplication::translate("Zenom", "Camera", 0, QApplication::UnicodeUTF8));
        startButton->setText(QString());
        stopButton->setText(QString());
        durationLabel->setText(QApplication::translate("Zenom", "Duration:", 0, QApplication::UnicodeUTF8));
        frequencyLabel->setText(QApplication::translate("Zenom", "Frequency:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        frequencyAbb->setToolTip(QApplication::translate("Zenom", "Hertz", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        frequencyAbb->setText(QApplication::translate("Zenom", "Hz", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        durationAbb->setToolTip(QApplication::translate("Zenom", "Second", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        durationAbb->setText(QApplication::translate("Zenom", "s", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("Zenom", "&File", 0, QApplication::UnicodeUTF8));
        menuRecent_P_rojects->setTitle(QApplication::translate("Zenom", "Recent &Projects", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("Zenom", "&View", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("Zenom", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Zenom: public Ui_Zenom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZENOM_H
