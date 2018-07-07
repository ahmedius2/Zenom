/********************************************************************************
** Form generated from reading UI file 'lineargaugesettingwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEARGAUGESETTINGWIDGET_H
#define UI_LINEARGAUGESETTINGWIDGET_H

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
#include "gauge/lineargauge.h"
#include "widget/colorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_LinearGaugeSettingWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *previewGroupBox;
    QGridLayout *gridLayout_2;
    LinearGauge *preview;
    QTabWidget *tabWidget;
    QWidget *scaleTab;
    QFormLayout *formLayout;
    QLabel *orientationLabel;
    QComboBox *orientation;
    QLabel *positionLabel;
    QComboBox *scalePosition;
    QGroupBox *rangeGroupBox;
    QFormLayout *formLayout_3;
    QLabel *rangeMinLabel;
    QDoubleSpinBox *rangeMin;
    QLabel *rangeMaxLabel;
    QDoubleSpinBox *rangeMax;
    QWidget *ticksTab;
    QFormLayout *formLayout_4;
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
    QWidget *pipeTab;
    QFormLayout *formLayout_5;
    QLabel *valueLabel;
    QSpinBox *value;
    QLabel *pipeWidthLabel;
    QSpinBox *pipeWidth;
    QLabel *pipeColorLabel;
    ColorButton *pipeColor;
    QWidget *alarmTab;
    QFormLayout *formLayout_7;
    QGroupBox *alarmGroupBox;
    QFormLayout *formLayout_2;
    QLabel *levelLabel;
    QDoubleSpinBox *alarmLevel;
    ColorButton *alarmColor;
    QLabel *alarmColorLabel;
    QWidget *generalTab;
    QFormLayout *formLayout_6;
    QLabel *titleLabel;
    QLineEdit *title;
    QLabel *textColorLabel;
    ColorButton *textColor;
    QLabel *backgroundColorLabel;
    ColorButton *backgroundColor;

    void setupUi(QWidget *LinearGaugeSettingWidget)
    {
        if (LinearGaugeSettingWidget->objectName().isEmpty())
            LinearGaugeSettingWidget->setObjectName(QString::fromUtf8("LinearGaugeSettingWidget"));
        LinearGaugeSettingWidget->resize(300, 400);
        gridLayout = new QGridLayout(LinearGaugeSettingWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        previewGroupBox = new QGroupBox(LinearGaugeSettingWidget);
        previewGroupBox->setObjectName(QString::fromUtf8("previewGroupBox"));
        gridLayout_2 = new QGridLayout(previewGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        preview = new LinearGauge(previewGroupBox);
        preview->setObjectName(QString::fromUtf8("preview"));

        gridLayout_2->addWidget(preview, 0, 0, 1, 1);


        gridLayout->addWidget(previewGroupBox, 1, 0, 1, 1);

        tabWidget = new QTabWidget(LinearGaugeSettingWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        scaleTab = new QWidget();
        scaleTab->setObjectName(QString::fromUtf8("scaleTab"));
        formLayout = new QFormLayout(scaleTab);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        orientationLabel = new QLabel(scaleTab);
        orientationLabel->setObjectName(QString::fromUtf8("orientationLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, orientationLabel);

        orientation = new QComboBox(scaleTab);
        orientation->setObjectName(QString::fromUtf8("orientation"));
        orientation->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, orientation);

        positionLabel = new QLabel(scaleTab);
        positionLabel->setObjectName(QString::fromUtf8("positionLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, positionLabel);

        scalePosition = new QComboBox(scaleTab);
        scalePosition->setObjectName(QString::fromUtf8("scalePosition"));
        scalePosition->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, scalePosition);

        rangeGroupBox = new QGroupBox(scaleTab);
        rangeGroupBox->setObjectName(QString::fromUtf8("rangeGroupBox"));
        formLayout_3 = new QFormLayout(rangeGroupBox);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        rangeMinLabel = new QLabel(rangeGroupBox);
        rangeMinLabel->setObjectName(QString::fromUtf8("rangeMinLabel"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, rangeMinLabel);

        rangeMin = new QDoubleSpinBox(rangeGroupBox);
        rangeMin->setObjectName(QString::fromUtf8("rangeMin"));
        rangeMin->setMaximumSize(QSize(150, 16777215));
        rangeMin->setDecimals(0);
        rangeMin->setMinimum(-1e+09);
        rangeMin->setMaximum(1e+09);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, rangeMin);

        rangeMaxLabel = new QLabel(rangeGroupBox);
        rangeMaxLabel->setObjectName(QString::fromUtf8("rangeMaxLabel"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, rangeMaxLabel);

        rangeMax = new QDoubleSpinBox(rangeGroupBox);
        rangeMax->setObjectName(QString::fromUtf8("rangeMax"));
        rangeMax->setMaximumSize(QSize(150, 16777215));
        rangeMax->setDecimals(0);
        rangeMax->setMinimum(-1e+09);
        rangeMax->setMaximum(1e+09);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, rangeMax);


        formLayout->setWidget(2, QFormLayout::SpanningRole, rangeGroupBox);

        tabWidget->addTab(scaleTab, QString());
        ticksTab = new QWidget();
        ticksTab->setObjectName(QString::fromUtf8("ticksTab"));
        formLayout_4 = new QFormLayout(ticksTab);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        tickCountGroupBox = new QGroupBox(ticksTab);
        tickCountGroupBox->setObjectName(QString::fromUtf8("tickCountGroupBox"));
        gridLayout_4 = new QGridLayout(tickCountGroupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        majorLabel = new QLabel(tickCountGroupBox);
        majorLabel->setObjectName(QString::fromUtf8("majorLabel"));

        gridLayout_4->addWidget(majorLabel, 0, 0, 1, 1);

        majorTick = new QSpinBox(tickCountGroupBox);
        majorTick->setObjectName(QString::fromUtf8("majorTick"));
        majorTick->setMinimum(2);

        gridLayout_4->addWidget(majorTick, 0, 1, 1, 1);

        minorLabel = new QLabel(tickCountGroupBox);
        minorLabel->setObjectName(QString::fromUtf8("minorLabel"));

        gridLayout_4->addWidget(minorLabel, 0, 2, 1, 1);

        minorTick = new QSpinBox(tickCountGroupBox);
        minorTick->setObjectName(QString::fromUtf8("minorTick"));
        minorTick->setMinimum(1);

        gridLayout_4->addWidget(minorTick, 0, 3, 1, 1);


        formLayout_4->setWidget(0, QFormLayout::LabelRole, tickCountGroupBox);

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


        formLayout_4->setWidget(1, QFormLayout::LabelRole, labelGroupBox);

        tabWidget->addTab(ticksTab, QString());
        pipeTab = new QWidget();
        pipeTab->setObjectName(QString::fromUtf8("pipeTab"));
        formLayout_5 = new QFormLayout(pipeTab);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        valueLabel = new QLabel(pipeTab);
        valueLabel->setObjectName(QString::fromUtf8("valueLabel"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, valueLabel);

        value = new QSpinBox(pipeTab);
        value->setObjectName(QString::fromUtf8("value"));
        value->setMaximumSize(QSize(150, 16777215));
        value->setMaximum(999999999);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, value);

        pipeWidthLabel = new QLabel(pipeTab);
        pipeWidthLabel->setObjectName(QString::fromUtf8("pipeWidthLabel"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, pipeWidthLabel);

        pipeWidth = new QSpinBox(pipeTab);
        pipeWidth->setObjectName(QString::fromUtf8("pipeWidth"));
        pipeWidth->setMaximumSize(QSize(150, 16777215));
        pipeWidth->setMinimum(1);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, pipeWidth);

        pipeColorLabel = new QLabel(pipeTab);
        pipeColorLabel->setObjectName(QString::fromUtf8("pipeColorLabel"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, pipeColorLabel);

        pipeColor = new ColorButton(pipeTab);
        pipeColor->setObjectName(QString::fromUtf8("pipeColor"));
        pipeColor->setMaximumSize(QSize(31, 16777215));

        formLayout_5->setWidget(2, QFormLayout::FieldRole, pipeColor);

        tabWidget->addTab(pipeTab, QString());
        alarmTab = new QWidget();
        alarmTab->setObjectName(QString::fromUtf8("alarmTab"));
        formLayout_7 = new QFormLayout(alarmTab);
        formLayout_7->setObjectName(QString::fromUtf8("formLayout_7"));
        alarmGroupBox = new QGroupBox(alarmTab);
        alarmGroupBox->setObjectName(QString::fromUtf8("alarmGroupBox"));
        alarmGroupBox->setCheckable(true);
        formLayout_2 = new QFormLayout(alarmGroupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        levelLabel = new QLabel(alarmGroupBox);
        levelLabel->setObjectName(QString::fromUtf8("levelLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, levelLabel);

        alarmLevel = new QDoubleSpinBox(alarmGroupBox);
        alarmLevel->setObjectName(QString::fromUtf8("alarmLevel"));
        alarmLevel->setMaximumSize(QSize(150, 16777215));
        alarmLevel->setDecimals(2);
        alarmLevel->setMinimum(-1e+09);
        alarmLevel->setMaximum(1e+09);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, alarmLevel);

        alarmColor = new ColorButton(alarmGroupBox);
        alarmColor->setObjectName(QString::fromUtf8("alarmColor"));
        alarmColor->setMaximumSize(QSize(31, 16777215));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, alarmColor);

        alarmColorLabel = new QLabel(alarmGroupBox);
        alarmColorLabel->setObjectName(QString::fromUtf8("alarmColorLabel"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, alarmColorLabel);


        formLayout_7->setWidget(0, QFormLayout::LabelRole, alarmGroupBox);

        tabWidget->addTab(alarmTab, QString());
        generalTab = new QWidget();
        generalTab->setObjectName(QString::fromUtf8("generalTab"));
        formLayout_6 = new QFormLayout(generalTab);
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        titleLabel = new QLabel(generalTab);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, titleLabel);

        title = new QLineEdit(generalTab);
        title->setObjectName(QString::fromUtf8("title"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        title->setMaximumSize(QSize(150, 16777215));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, title);

        textColorLabel = new QLabel(generalTab);
        textColorLabel->setObjectName(QString::fromUtf8("textColorLabel"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, textColorLabel);

        textColor = new ColorButton(generalTab);
        textColor->setObjectName(QString::fromUtf8("textColor"));
        textColor->setMaximumSize(QSize(31, 16777215));

        formLayout_6->setWidget(1, QFormLayout::FieldRole, textColor);

        backgroundColorLabel = new QLabel(generalTab);
        backgroundColorLabel->setObjectName(QString::fromUtf8("backgroundColorLabel"));

        formLayout_6->setWidget(2, QFormLayout::LabelRole, backgroundColorLabel);

        backgroundColor = new ColorButton(generalTab);
        backgroundColor->setObjectName(QString::fromUtf8("backgroundColor"));
        backgroundColor->setMaximumSize(QSize(31, 16777215));

        formLayout_6->setWidget(2, QFormLayout::FieldRole, backgroundColor);

        tabWidget->addTab(generalTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(LinearGaugeSettingWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LinearGaugeSettingWidget);
    } // setupUi

    void retranslateUi(QWidget *LinearGaugeSettingWidget)
    {
        LinearGaugeSettingWidget->setWindowTitle(QApplication::translate("LinearGaugeSettingWidget", "Form", 0, QApplication::UnicodeUTF8));
        previewGroupBox->setTitle(QApplication::translate("LinearGaugeSettingWidget", "Preview", 0, QApplication::UnicodeUTF8));
        orientationLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Orientation:", 0, QApplication::UnicodeUTF8));
        orientation->clear();
        orientation->insertItems(0, QStringList()
         << QApplication::translate("LinearGaugeSettingWidget", "Vertical", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LinearGaugeSettingWidget", "Horizontal", 0, QApplication::UnicodeUTF8)
        );
        positionLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Position:", 0, QApplication::UnicodeUTF8));
        scalePosition->clear();
        scalePosition->insertItems(0, QStringList()
         << QApplication::translate("LinearGaugeSettingWidget", "No", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LinearGaugeSettingWidget", "Left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LinearGaugeSettingWidget", "Right", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LinearGaugeSettingWidget", "Top", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LinearGaugeSettingWidget", "Bottom", 0, QApplication::UnicodeUTF8)
        );
        rangeGroupBox->setTitle(QApplication::translate("LinearGaugeSettingWidget", "Range", 0, QApplication::UnicodeUTF8));
        rangeMinLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Minimum: ", 0, QApplication::UnicodeUTF8));
        rangeMaxLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Maximum:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(scaleTab), QApplication::translate("LinearGaugeSettingWidget", "Scale", 0, QApplication::UnicodeUTF8));
        tickCountGroupBox->setTitle(QApplication::translate("LinearGaugeSettingWidget", "Max. Tick Count", 0, QApplication::UnicodeUTF8));
        majorLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Major:", 0, QApplication::UnicodeUTF8));
        minorLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Minor:", 0, QApplication::UnicodeUTF8));
        labelGroupBox->setTitle(QApplication::translate("LinearGaugeSettingWidget", "Labels", 0, QApplication::UnicodeUTF8));
        fontLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Font:", 0, QApplication::UnicodeUTF8));
        fontSizeLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Font Size:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(ticksTab), QApplication::translate("LinearGaugeSettingWidget", "Ticks", 0, QApplication::UnicodeUTF8));
        valueLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Value:", 0, QApplication::UnicodeUTF8));
        pipeWidthLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Width:", 0, QApplication::UnicodeUTF8));
        pipeColorLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Color:", 0, QApplication::UnicodeUTF8));
        pipeColor->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(pipeTab), QApplication::translate("LinearGaugeSettingWidget", "Pipe", 0, QApplication::UnicodeUTF8));
        alarmGroupBox->setTitle(QApplication::translate("LinearGaugeSettingWidget", "Enabled", 0, QApplication::UnicodeUTF8));
        levelLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Level:", 0, QApplication::UnicodeUTF8));
        alarmColor->setText(QString());
        alarmColorLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Color:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(alarmTab), QApplication::translate("LinearGaugeSettingWidget", "Alarm", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Title:", 0, QApplication::UnicodeUTF8));
        textColorLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Text:", 0, QApplication::UnicodeUTF8));
        textColor->setText(QString());
        backgroundColorLabel->setText(QApplication::translate("LinearGaugeSettingWidget", "Background:", 0, QApplication::UnicodeUTF8));
        backgroundColor->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(generalTab), QApplication::translate("LinearGaugeSettingWidget", "General", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LinearGaugeSettingWidget: public Ui_LinearGaugeSettingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEARGAUGESETTINGWIDGET_H
