/********************************************************************************
** Form generated from reading UI file 'attachlogvariabledialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTACHLOGVARIABLEDIALOG_H
#define UI_ATTACHLOGVARIABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include "widget/logvariabletreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_AttachLogVariableDialog
{
public:
    QVBoxLayout *verticalLayout;
    LogVariableTreeWidget *logVariableList;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AttachLogVariableDialog)
    {
        if (AttachLogVariableDialog->objectName().isEmpty())
            AttachLogVariableDialog->setObjectName(QString::fromUtf8("AttachLogVariableDialog"));
        AttachLogVariableDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(AttachLogVariableDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        logVariableList = new LogVariableTreeWidget(AttachLogVariableDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Log Variables"));
        logVariableList->setHeaderItem(__qtreewidgetitem);
        logVariableList->setObjectName(QString::fromUtf8("logVariableList"));
        logVariableList->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(logVariableList);

        buttonBox = new QDialogButtonBox(AttachLogVariableDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AttachLogVariableDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AttachLogVariableDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AttachLogVariableDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AttachLogVariableDialog);
    } // setupUi

    void retranslateUi(QDialog *AttachLogVariableDialog)
    {
        AttachLogVariableDialog->setWindowTitle(QApplication::translate("AttachLogVariableDialog", "Select a Variable(s) to Attach:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AttachLogVariableDialog: public Ui_AttachLogVariableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTACHLOGVARIABLEDIALOG_H
