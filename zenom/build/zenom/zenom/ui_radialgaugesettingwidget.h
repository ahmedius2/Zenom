/********************************************************************************
** Form generated from reading UI file 'radialgaugesettingwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIALGAUGESETTINGWIDGET_H
#define UI_RADIALGAUGESETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "gauge/radialgauge.h"
#include "widget/colorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_RadialGaugeSettingWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *previewGroupBox;
    QGridLayout *gridLayout_2;
    RadialGauge *preview;
    QTabWidget *tabWidget;
    QWidget *scaleTab;
    QFormLayout *formLayout_3;
    QLabel *directionLabel;
    QComboBox *direction;
    QGroupBox *rangeGroupBox;
    QFormLayout *formLayout_5;
    QLabel *rangeMinLabel;
    QDoubleSpinBox *rangeMin;
    QLabel *rangeMaxLabel;
    QDoubleSpinBox *rangeMax;
    QGroupBox *scaleArcGroupBox;
    QGridLayout *gridLayout_7;
    QLabel *startAngleLabel;
    QDoubleSpinBox *startAngle;
    QLabel *sweepAngleLabel;
    QDoubleSpinBox *sweepAngle;
    QWidget *ticksTab;
    QFormLayout *formLayout_2;
    QGroupBox *tickCountGroupBox;
    QGridLayout *gridLayout_4;
    QLabel *majorLabel;
    QSpinBox *majorTick;
    QLabel *minorLabel;
    QSpinBox *minorTick;
    QGroupBox *labelGroupBox;
    QGridLayout *gridLayout_3;
    QFontComboBox *font;
    QLabel *fontLabel;
    QLabel *fontSizeLabel;
    QComboBox *fontSize;
    QWidget *needleTab;
    QFormLayout *formLayout;
    QLabel *valueLabel;
    QSpinBox *value;
    QLabel *needleTypeLabel;
    QComboBox *needleType;
    QLabel *needleStyleLabel;
    QComboBox *needleStyle;
    QLabel *needleColor1Label;
    ColorButton *needleColor1;
    QLabel *needleColor2Label;
    ColorButton *needleColor2;
    QWidget *generalTab;
    QFormLayout *formLayout_4;
    QLabel *titleLabel;
    QLineEdit *title;
    QLabel *textColorLabel;
    ColorButton *textColor;
    QLabel *backgroundColorLabel;
    ColorButton *backgroundColor;

    void setupUi(QWidget *RadialGaugeSettingWidget)
    {
        if (RadialGaugeSettingWidget->objectName().isEmpty())
            RadialGaugeSettingWidget->setObjectName(QString::fromUtf8("RadialGaugeSettingWidget"));
        RadialGaugeSettingWidget->resize(300, 400);
        gridLayout = new QGridLayout(RadialGaugeSettingWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        previewGroupBox = new QGroupBox(RadialGaugeSettingWidget);
        previewGroupBox->setObjectName(QString::fromUtf8("previewGroupBox"));
        gridLayout_2 = new QGridLayout(previewGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        preview = new RadialGauge(previewGroupBox);
        preview->setObjectName(QString::fromUtf8("preview"));

        gridLayout_2->addWidget(preview, 0, 0, 1, 1);


        gridLayout->addWidget(previewGroupBox, 1, 0, 1, 1);

        tabWidget = new QTabWidget(RadialGaugeSettingWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        scaleTab = new QWidget();
        scaleTab->setObjectName(QString::fromUtf8("scaleTab"));
        formLayout_3 = new QFormLayout(scaleTab);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        directionLabel = new QLabel(scaleTab);
        directionLabel->setObjectName(QString::fromUtf8("directionLabel"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, directionLabel);

        direction = new QComboBox(scaleTab);
        direction->setObjectName(QString::fromUtf8("direction"));
        direction->setMaximumSize(QSize(165, 16777215));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, direction);

        rangeGroupBox = new QGroupBox(scaleTab);
        rangeGroupBox->setObjectName(QString::fromUtf8("rangeGroupBox"));
        formLayout_5 = new QFormLayout(rangeGroupBox);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        rangeMinLabel = new QLabel(rangeGroupBox);
        rangeMinLabel->setObjectName(QString::fromUtf8("rangeMinLabel"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, rangeMinLabel);

        rangeMin = new QDoubleSpinBox(rangeGroupBox);
        rangeMin->setObjectName(QString::fromUtf8("rangeMin"));
        rangeMin->setMaximumSize(QSize(150, 16777215));
        rangeMin->setAccelerated(true);
        rangeMin->setDecimals(0);
        rangeMin->setMinimum(-1e+09);
        rangeMin->setMaximum(1e+09);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, rangeMin);

        rangeMaxLabel = new QLabel(rangeGroupBox);
        rangeMaxLabel->setObjectName(QString::fromUtf8("rangeMaxLabel"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, rangeMaxLabel);

        rangeMax = new QDoubleSpinBox(rangeGroupBox);
        rangeMax->setObjectName(QString::fromUtf8("rangeMax"));
        rangeMax->setMaximumSize(QSize(150, 16777215));
        rangeMax->setAccelerated(true);
        rangeMax->setDecimals(0);
        rangeMax->setMinimum(-1e+09);
        rangeMax->setMaximum(1e+09);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, rangeMax);


        formLayout_3->setWidget(1, QFormLayout::SpanningRole, rangeGroupBox);

        scaleArcGroupBox = new QGroupBox(scaleTab);
        scaleArcGroupBox->setObjectName(QString::fromUtf8("scaleArcGroupBox"));
        gridLayout_7 = new QGridLayout(scaleArcGroupBox);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        startAngleLabel = new QLabel(scaleArcGroupBox);
        startAngleLabel->setObjectName(QString::fromUtf8("startAngleLabel"));

        gridLayout_7->addWidget(startAngleLabel, 0, 1, 1, 1);

        startAngle = new QDoubleSpinBox(scaleArcGroupBox);
        startAngle->setObjectName(QString::fromUtf8("startAngle"));
        startAngle->setAccelerated(true);
        startAngle->setDecimals(0);
        startAngle->setMinimum(0);
        startAngle->setMaximum(359);

        gridLayout_7->addWidget(startAngle, 0, 2, 1, 1);

        sweepAngleLabel = new QLabel(scaleArcGroupBox);
        sweepAngleLabel->setObjectName(QString::fromUtf8("sweepAngleLabel"));

        gridLayout_7->addWidget(sweepAngleLabel, 0, 3, 1, 1);

        sweepAngle = new QDoubleSpinBox(scaleArcGroupBox);
        sweepAngle->setObjectName(QString::fromUtf8("sweepAngle"));
        sweepAngle->setAccelerated(true);
        sweepAngle->setDecimals(0);
        sweepAngle->setMinimum(0);
        sweepAngle->setMaximum(359);

        gridLayout_7->addWidget(sweepAngle, 0, 4, 1, 1);


        formLayout_3->setWidget(2, QFormLayout::SpanningRole, scaleArcGroupBox);

        tabWidget->addTab(scaleTab, QString());
        ticksTab = new QWidget();
        ticksTab->setObjectName(QString::fromUtf8("ticksTab"));
        formLayout_2 = new QFormLayout(ticksTab);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        tickCountGroupBox = new QGroupBox(ticksTab);
        tickCountGroupBox->setObjectName(QString::fromUtf8("tickCountGroupBox"));
        gridLayout_4 = new QGridLayout(tickCountGroupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        majorLabel = new QLabel(tickCountGroupBox);
        majorLabel->setObjectName(QString::fromUtf8("majorLabel"));

        gridLayout_4->addWidget(majorLabel, 0, 0, 1, 1);

        majorTick = new QSpinBox(tickCountGroupBox);
        majorTick->setObjectName(QString::fromUtf8("majorTick"));
        majorTick->setAccelerated(true);
        majorTick->setMinimum(2);

        gridLayout_4->addWidget(majorTick, 0, 1, 1, 1);

        minorLabel = new QLabel(tickCountGroupBox);
        minorLabel->setObjectName(QString::fromUtf8("minorLabel"));

        gridLayout_4->addWidget(minorLabel, 0, 2, 1, 1);

        minorTick = new QSpinBox(tickCountGroupBox);
        minorTick->setObjectName(QString::fromUtf8("minorTick"));
        minorTick->setAccelerated(true);
        minorTick->setMinimum(1);

        gridLayout_4->addWidget(minorTick, 0, 3, 1, 1);


        formLayout_2->setWidget(0, QFormLayout::LabelRole, tickCountGroupBox);

        labelGroupBox = new QGroupBox(ticksTab);
        labelGroupBox->setObjectName(QString::fromUtf8("labelGroupBox"));
        labelGroupBox->setCheckable(true);
        gridLayout_3 = new QGridLayout(labelGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        font = new QFontComboBox(labelGroupBox);
        font->setObjectName(QString::fromUtf8("font"));
        font->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(font, 0, 1, 1, 1);

        fontLabel = new QLabel(labelGroupBox);
        fontLabel->setObjectName(QString::fromUtf8("fontLabel"));

        gridLayout_3->addWidget(fontLabel, 0, 0, 1, 1);

        fontSizeLabel = new QLabel(labelGroupBox);
        fontSizeLabel->setObjectName(QString::fromUtf8("fontSizeLabel"));

        gridLayout_3->addWidget(fontSizeLabel, 1, 0, 1, 1);

        fontSize = new QComboBox(labelGroupBox);
        fontSize->setObjectName(QString::fromUtf8("fontSize"));
        fontSize->setMaximumSize(QSize(80, 16777215));
        fontSize->setEditable(true);

        gridLayout_3->addWidget(fontSize, 1, 1, 1, 1);


        formLayout_2->setWidget(1, QFormLayout::LabelRole, labelGroupBox);

        tabWidget->addTab(ticksTab, QString());
        needleTab = new QWidget();
        needleTab->setObjectName(QString::fromUtf8("needleTab"));
        formLayout = new QFormLayout(needleTab);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        valueLabel = new QLabel(needleTab);
        valueLabel->setObjectName(QString::fromUtf8("valueLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, valueLabel);

        value = new QSpinBox(needleTab);
        value->setObjectName(QString::fromUtf8("value"));
        value->setMaximumSize(QSize(150, 16777215));
        value->setAccelerated(true);
        value->setMinimum(-999999999);
        value->setMaximum(999999999);

        formLayout->setWidget(0, QFormLayout::FieldRole, value);

        needleTypeLabel = new QLabel(needleTab);
        needleTypeLabel->setObjectName(QString::fromUtf8("needleTypeLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, needleTypeLabel);

        needleType = new QComboBox(needleTab);
        needleType->setObjectName(QString::fromUtf8("needleType"));
        needleType->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, needleType);

        needleStyleLabel = new QLabel(needleTab);
        needleStyleLabel->setObjectName(QString::fromUtf8("needleStyleLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, needleStyleLabel);

        needleStyle = new QComboBox(needleTab);
        needleStyle->setObjectName(QString::fromUtf8("needleStyle"));
        needleStyle->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, needleStyle);

        needleColor1Label = new QLabel(needleTab);
        needleColor1Label->setObjectName(QString::fromUtf8("needleColor1Label"));

        formLayout->setWidget(3, QFormLayout::LabelRole, needleColor1Label);

        needleColor1 = new ColorButton(needleTab);
        needleColor1->setObjectName(QString::fromUtf8("needleColor1"));
        needleColor1->setMaximumSize(QSize(31, 16777215));

        formLayout->setWidget(3, QFormLayout::FieldRole, needleColor1);

        needleColor2Label = new QLabel(needleTab);
        needleColor2Label->setObjectName(QString::fromUtf8("needleColor2Label"));

        formLayout->setWidget(4, QFormLayout::LabelRole, needleColor2Label);

        needleColor2 = new ColorButton(needleTab);
        needleColor2->setObjectName(QString::fromUtf8("needleColor2"));
        needleColor2->setMaximumSize(QSize(31, 16777215));

        formLayout->setWidget(4, QFormLayout::FieldRole, needleColor2);

        tabWidget->addTab(needleTab, QString());
        generalTab = new QWidget();
        generalTab->setObjectName(QString::fromUtf8("generalTab"));
        formLayout_4 = new QFormLayout(generalTab);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        titleLabel = new QLabel(generalTab);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, titleLabel);

        title = new QLineEdit(generalTab);
        title->setObjectName(QString::fromUtf8("title"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        title->setMaximumSize(QSize(150, 16777215));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, title);

        textColorLabel = new QLabel(generalTab);
        textColorLabel->setObjectName(QString::fromUtf8("textColorLabel"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, textColorLabel);

        textColor = new ColorButton(generalTab);
        textColor->setObjectName(QString::fromUtf8("textColor"));
        textColor->setMaximumSize(QSize(31, 16777215));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, textColor);

        backgroundColorLabel = new QLabel(generalTab);
        backgroundColorLabel->setObjectName(QString::fromUtf8("backgroundColorLabel"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, backgroundColorLabel);

        backgroundColor = new ColorButton(generalTab);
        backgroundColor->setObjectName(QString::fromUtf8("backgroundColor"));
        backgroundColor->setMaximumSize(QSize(31, 16777215));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, backgroundColor);

        tabWidget->addTab(generalTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(RadialGaugeSettingWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RadialGaugeSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *RadialGaugeSettingWidget)
    {
        RadialGaugeSettingWidget->setWindowTitle(QApplication::translate("RadialGaugeSettingWidget", "Form", 0, QApplication::UnicodeUTF8));
        previewGroupBox->setTitle(QApplication::translate("RadialGaugeSettingWidget", "Preview", 0, QApplication::UnicodeUTF8));
        directionLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Direction:", 0, QApplication::UnicodeUTF8));
        direction->clear();
        direction->insertItems(0, QStringList()
         << QApplication::translate("RadialGaugeSettingWidget", "Clockwise", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RadialGaugeSettingWidget", "Counter Clockwise", 0, QApplication::UnicodeUTF8)
        );
        rangeGroupBox->setTitle(QApplication::translate("RadialGaugeSettingWidget", "Range", 0, QApplication::UnicodeUTF8));
        rangeMinLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Minimum:", 0, QApplication::UnicodeUTF8));
        rangeMaxLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Maximum:", 0, QApplication::UnicodeUTF8));
        scaleArcGroupBox->setTitle(QApplication::translate("RadialGaugeSettingWidget", "Scale Arc", 0, QApplication::UnicodeUTF8));
        startAngleLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Start:", 0, QApplication::UnicodeUTF8));
        sweepAngleLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Sweep:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(scaleTab), QApplication::translate("RadialGaugeSettingWidget", "Scale", 0, QApplication::UnicodeUTF8));
        tickCountGroupBox->setTitle(QApplication::translate("RadialGaugeSettingWidget", "Max. Tick Count", 0, QApplication::UnicodeUTF8));
        majorLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Major:", 0, QApplication::UnicodeUTF8));
        minorLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Minor:", 0, QApplication::UnicodeUTF8));
        labelGroupBox->setTitle(QApplication::translate("RadialGaugeSettingWidget", "Labels", 0, QApplication::UnicodeUTF8));
        fontLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Font:", 0, QApplication::UnicodeUTF8));
        fontSizeLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Font Size:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(ticksTab), QApplication::translate("RadialGaugeSettingWidget", "Ticks", 0, QApplication::UnicodeUTF8));
        valueLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Value:", 0, QApplication::UnicodeUTF8));
        needleTypeLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Type:", 0, QApplication::UnicodeUTF8));
        needleType->clear();
        needleType->insertItems(0, QStringList()
         << QApplication::translate("RadialGaugeSettingWidget", "Simple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RadialGaugeSettingWidget", "Magnet", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RadialGaugeSettingWidget", "Wind Arrow", 0, QApplication::UnicodeUTF8)
        );
        needleStyleLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Style:", 0, QApplication::UnicodeUTF8));
        needleStyle->clear();
        needleStyle->insertItems(0, QStringList()
         << QApplication::translate("RadialGaugeSettingWidget", "Style 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("RadialGaugeSettingWidget", "Style 2", 0, QApplication::UnicodeUTF8)
        );
        needleColor1Label->setText(QApplication::translate("RadialGaugeSettingWidget", "Color1:", 0, QApplication::UnicodeUTF8));
        needleColor1->setText(QString());
        needleColor2Label->setText(QApplication::translate("RadialGaugeSettingWidget", "Color2:", 0, QApplication::UnicodeUTF8));
        needleColor2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(needleTab), QApplication::translate("RadialGaugeSettingWidget", "Needle", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Title:", 0, QApplication::UnicodeUTF8));
        textColorLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Text:", 0, QApplication::UnicodeUTF8));
        textColor->setText(QString());
        backgroundColorLabel->setText(QApplication::translate("RadialGaugeSettingWidget", "Background:", 0, QApplication::UnicodeUTF8));
        backgroundColor->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(generalTab), QApplication::translate("RadialGaugeSettingWidget", "General", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RadialGaugeSettingWidget: public Ui_RadialGaugeSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIALGAUGESETTINGWIDGET_H
