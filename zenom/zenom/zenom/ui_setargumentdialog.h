/********************************************************************************
** Form generated from reading UI file 'setargumentdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETARGUMENTDIALOG_H
#define UI_SETARGUMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetArgumentDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *argumentTable;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *bindButton;
    QPushButton *unbindButton;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QListWidget *logVariableList;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SetArgumentDialog)
    {
        if (SetArgumentDialog->objectName().isEmpty())
            SetArgumentDialog->setObjectName(QString::fromUtf8("SetArgumentDialog"));
        SetArgumentDialog->resize(650, 300);
        gridLayout_3 = new QGridLayout(SetArgumentDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(SetArgumentDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        argumentTable = new QTableWidget(groupBox);
        if (argumentTable->columnCount() < 3)
            argumentTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        argumentTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        argumentTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        argumentTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        argumentTable->setObjectName(QString::fromUtf8("argumentTable"));
        QPalette palette;
        QBrush brush(QColor(51, 153, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        argumentTable->setPalette(palette);
        argumentTable->setAlternatingRowColors(true);
        argumentTable->setSelectionMode(QAbstractItemView::SingleSelection);
        argumentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        argumentTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        argumentTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        argumentTable->horizontalHeader()->setStretchLastSection(true);
        argumentTable->verticalHeader()->setVisible(false);

        gridLayout->addWidget(argumentTable, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        bindButton = new QPushButton(SetArgumentDialog);
        bindButton->setObjectName(QString::fromUtf8("bindButton"));

        verticalLayout_2->addWidget(bindButton);

        unbindButton = new QPushButton(SetArgumentDialog);
        unbindButton->setObjectName(QString::fromUtf8("unbindButton"));

        verticalLayout_2->addWidget(unbindButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        gridLayout_3->addLayout(verticalLayout_2, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(SetArgumentDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(170, 16777215));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        logVariableList = new QListWidget(groupBox_2);
        logVariableList->setObjectName(QString::fromUtf8("logVariableList"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush);
        logVariableList->setPalette(palette1);

        gridLayout_2->addWidget(logVariableList, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 2, 1, 1);

        buttonBox = new QDialogButtonBox(SetArgumentDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 1, 0, 1, 3);


        retranslateUi(SetArgumentDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetArgumentDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetArgumentDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetArgumentDialog);
    } // setupUi

    void retranslateUi(QDialog *SetArgumentDialog)
    {
        SetArgumentDialog->setWindowTitle(QApplication::translate("SetArgumentDialog", "Set Argument", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SetArgumentDialog", "Parameters", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = argumentTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SetArgumentDialog", "Type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = argumentTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SetArgumentDialog", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = argumentTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SetArgumentDialog", "Log Variable", 0, QApplication::UnicodeUTF8));
        bindButton->setText(QApplication::translate("SetArgumentDialog", "Bind", 0, QApplication::UnicodeUTF8));
        unbindButton->setText(QApplication::translate("SetArgumentDialog", "Unbind", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("SetArgumentDialog", "Log Variables", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetArgumentDialog: public Ui_SetArgumentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETARGUMENTDIALOG_H
