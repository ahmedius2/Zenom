/********************************************************************************
** Form generated from reading UI file 'legenditem.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEGENDITEM_H
#define UI_LEGENDITEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "widget/colorbutton.h"
#include "widget/linesizecombobox.h"

QT_BEGIN_NAMESPACE

class Ui_LegendItem
{
public:
    QHBoxLayout *horizontalLayout;
    ColorButton *colorButton;
    LineSizeComboBox *lineSizeCombo;
    QLabel *curveName;
    QPushButton *removeButton;

    void setupUi(QWidget *LegendItem)
    {
        if (LegendItem->objectName().isEmpty())
            LegendItem->setObjectName(QString::fromUtf8("LegendItem"));
        LegendItem->resize(133, 22);
        horizontalLayout = new QHBoxLayout(LegendItem);
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        colorButton = new ColorButton(LegendItem);
        colorButton->setObjectName(QString::fromUtf8("colorButton"));
        colorButton->setMaximumSize(QSize(14, 14));
        QPalette palette;
        QBrush brush(QColor(85, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(170, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        colorButton->setPalette(palette);
        colorButton->setAutoFillBackground(true);
        colorButton->setFlat(true);

        horizontalLayout->addWidget(colorButton);

        lineSizeCombo = new LineSizeComboBox(LegendItem);
        lineSizeCombo->setObjectName(QString::fromUtf8("lineSizeCombo"));
        lineSizeCombo->setMaximumSize(QSize(40, 18));

        horizontalLayout->addWidget(lineSizeCombo);

        curveName = new QLabel(LegendItem);
        curveName->setObjectName(QString::fromUtf8("curveName"));

        horizontalLayout->addWidget(curveName);

        removeButton = new QPushButton(LegendItem);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setMaximumSize(QSize(16, 16));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/plot/resources/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon);
        removeButton->setFlat(true);

        horizontalLayout->addWidget(removeButton);


        retranslateUi(LegendItem);

        QMetaObject::connectSlotsByName(LegendItem);
    } // setupUi

    void retranslateUi(QWidget *LegendItem)
    {
        LegendItem->setWindowTitle(QApplication::translate("LegendItem", "Form", 0, QApplication::UnicodeUTF8));
        colorButton->setText(QString());
        curveName->setText(QApplication::translate("LegendItem", "TextLabel", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LegendItem: public Ui_LegendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEGENDITEM_H
