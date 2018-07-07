/********************************************************************************
** Form generated from reading UI file 'statusbar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSBAR_H
#define UI_STATUSBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusBar
{
public:
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QFrame *line_2;
    QLabel *elapsedTime;
    QFrame *line_3;
    QLabel *overruns;

    void setupUi(QWidget *StatusBar)
    {
        if (StatusBar->objectName().isEmpty())
            StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
        StatusBar->resize(417, 23);
        horizontalLayout = new QHBoxLayout(StatusBar);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        progressBar = new QProgressBar(StatusBar);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMaximumSize(QSize(16777215, 16));
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(false);

        horizontalLayout->addWidget(progressBar);

        line_2 = new QFrame(StatusBar);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        elapsedTime = new QLabel(StatusBar);
        elapsedTime->setObjectName(QString::fromUtf8("elapsedTime"));
        elapsedTime->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(elapsedTime);

        line_3 = new QFrame(StatusBar);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        overruns = new QLabel(StatusBar);
        overruns->setObjectName(QString::fromUtf8("overruns"));
        overruns->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(overruns);


        retranslateUi(StatusBar);

        QMetaObject::connectSlotsByName(StatusBar);
    } // setupUi

    void retranslateUi(QWidget *StatusBar)
    {
        StatusBar->setWindowTitle(QApplication::translate("StatusBar", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        elapsedTime->setToolTip(QApplication::translate("StatusBar", "Elapsed time", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        elapsedTime->setText(QApplication::translate("StatusBar", "T=", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        overruns->setToolTip(QApplication::translate("StatusBar", "Count of overruns", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        overruns->setText(QApplication::translate("StatusBar", "O=", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StatusBar: public Ui_StatusBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSBAR_H
