/********************************************************************************
** Form generated from reading UI file 'creategaugedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGAUGEDIALOG_H
#define UI_CREATEGAUGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QStackedWidget>
#include "widget/logvariabletreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_CreateGaugeDialog
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QListWidget *gaugeList;
    LogVariableTreeWidget *logVariableList;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CreateGaugeDialog)
    {
        if (CreateGaugeDialog->objectName().isEmpty())
            CreateGaugeDialog->setObjectName(QString::fromUtf8("CreateGaugeDialog"));
        CreateGaugeDialog->setWindowModality(Qt::ApplicationModal);
        CreateGaugeDialog->resize(470, 570);
        gridLayout = new QGridLayout(CreateGaugeDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(CreateGaugeDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));

        gridLayout->addWidget(stackedWidget, 0, 1, 2, 1);

        gaugeList = new QListWidget(CreateGaugeDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gauge/resources/radialgauge.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(gaugeList);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gauge/resources/lineargauge.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(gaugeList);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gauge/resources/numericgauge.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(gaugeList);
        __qlistwidgetitem2->setIcon(icon2);
        gaugeList->setObjectName(QString::fromUtf8("gaugeList"));
        gaugeList->setMinimumSize(QSize(150, 0));
        gaugeList->setMaximumSize(QSize(150, 200));
        gaugeList->setIconSize(QSize(50, 50));
        gaugeList->setSpacing(5);

        gridLayout->addWidget(gaugeList, 0, 0, 1, 1);

        logVariableList = new LogVariableTreeWidget(CreateGaugeDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Log Variables"));
        logVariableList->setHeaderItem(__qtreewidgetitem);
        logVariableList->setObjectName(QString::fromUtf8("logVariableList"));
        logVariableList->setMinimumSize(QSize(150, 0));
        logVariableList->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(logVariableList, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(CreateGaugeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(CreateGaugeDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateGaugeDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateGaugeDialog, SLOT(accept()));

        gaugeList->setCurrentRow(0);


        QMetaObject::connectSlotsByName(CreateGaugeDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateGaugeDialog)
    {
        CreateGaugeDialog->setWindowTitle(QApplication::translate("CreateGaugeDialog", "Create Gauge", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = gaugeList->isSortingEnabled();
        gaugeList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = gaugeList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("CreateGaugeDialog", "Radial", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = gaugeList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("CreateGaugeDialog", "Linear", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = gaugeList->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("CreateGaugeDialog", "Numeric", 0, QApplication::UnicodeUTF8));
        gaugeList->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class CreateGaugeDialog: public Ui_CreateGaugeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGAUGEDIALOG_H
