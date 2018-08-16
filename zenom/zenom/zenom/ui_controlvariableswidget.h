/********************************************************************************
** Form generated from reading UI file 'controlvariableswidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLVARIABLESWIDGET_H
#define UI_CONTROLVARIABLESWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlVariablesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *controlVariableTable;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *apply;
    QPushButton *cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ControlVariablesWidget)
    {
        if (ControlVariablesWidget->objectName().isEmpty())
            ControlVariablesWidget->setObjectName(QString::fromUtf8("ControlVariablesWidget"));
        ControlVariablesWidget->resize(320, 400);
        verticalLayout = new QVBoxLayout(ControlVariablesWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        controlVariableTable = new QTableWidget(ControlVariablesWidget);
        if (controlVariableTable->columnCount() < 2)
            controlVariableTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        controlVariableTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        controlVariableTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        controlVariableTable->setObjectName(QString::fromUtf8("controlVariableTable"));
        controlVariableTable->setAlternatingRowColors(true);
        controlVariableTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        controlVariableTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        controlVariableTable->horizontalHeader()->setDefaultSectionSize(90);

        verticalLayout->addWidget(controlVariableTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        apply = new QPushButton(ControlVariablesWidget);
        apply->setObjectName(QString::fromUtf8("apply"));

        horizontalLayout->addWidget(apply);

        cancel = new QPushButton(ControlVariablesWidget);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout->addWidget(cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ControlVariablesWidget);

        QMetaObject::connectSlotsByName(ControlVariablesWidget);
    } // setupUi

    void retranslateUi(QWidget *ControlVariablesWidget)
    {
        ControlVariablesWidget->setWindowTitle(QApplication::translate("ControlVariablesWidget", "Control Variables", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = controlVariableTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ControlVariablesWidget", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = controlVariableTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ControlVariablesWidget", "Value", 0, QApplication::UnicodeUTF8));
        apply->setText(QApplication::translate("ControlVariablesWidget", "Apply", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("ControlVariablesWidget", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ControlVariablesWidget: public Ui_ControlVariablesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLVARIABLESWIDGET_H
