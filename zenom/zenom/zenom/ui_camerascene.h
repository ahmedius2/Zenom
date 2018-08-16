/********************************************************************************
** Form generated from reading UI file 'camerascene.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERASCENE_H
#define UI_CAMERASCENE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CameraScene
{
public:
    QFormLayout *formLayout;
    QLabel *label_camera;
    QHBoxLayout *horizontalLayout;
    QCheckBox *server;
    QPushButton *start;
    QLineEdit *ipAddress;
    QPushButton *up;
    QVBoxLayout *verticalLayout;
    QRadioButton *tenHund;
    QRadioButton *threeHund;
    QRadioButton *sixHund;
    QRadioButton *tenThnd;
    QPushButton *bottom;

    void setupUi(QDialog *CameraScene)
    {
        if (CameraScene->objectName().isEmpty())
            CameraScene->setObjectName(QString::fromUtf8("CameraScene"));
        CameraScene->resize(299, 221);
        CameraScene->setMinimumSize(QSize(299, 221));
        CameraScene->setMaximumSize(QSize(299, 221));
        CameraScene->setAutoFillBackground(true);
        formLayout = new QFormLayout(CameraScene);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label_camera = new QLabel(CameraScene);
        label_camera->setObjectName(QString::fromUtf8("label_camera"));
        label_camera->setMinimumSize(QSize(153, 19));
        label_camera->setAutoFillBackground(false);
        label_camera->setFrameShape(QFrame::Box);
        label_camera->setScaledContents(false);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_camera);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        server = new QCheckBox(CameraScene);
        server->setObjectName(QString::fromUtf8("server"));

        horizontalLayout->addWidget(server);

        start = new QPushButton(CameraScene);
        start->setObjectName(QString::fromUtf8("start"));
        start->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(start);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout);

        ipAddress = new QLineEdit(CameraScene);
        ipAddress->setObjectName(QString::fromUtf8("ipAddress"));
        ipAddress->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        formLayout->setWidget(2, QFormLayout::LabelRole, ipAddress);

        up = new QPushButton(CameraScene);
        up->setObjectName(QString::fromUtf8("up"));

        formLayout->setWidget(2, QFormLayout::FieldRole, up);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tenHund = new QRadioButton(CameraScene);
        tenHund->setObjectName(QString::fromUtf8("tenHund"));

        verticalLayout->addWidget(tenHund);

        threeHund = new QRadioButton(CameraScene);
        threeHund->setObjectName(QString::fromUtf8("threeHund"));

        verticalLayout->addWidget(threeHund);

        sixHund = new QRadioButton(CameraScene);
        sixHund->setObjectName(QString::fromUtf8("sixHund"));

        verticalLayout->addWidget(sixHund);

        tenThnd = new QRadioButton(CameraScene);
        tenThnd->setObjectName(QString::fromUtf8("tenThnd"));

        verticalLayout->addWidget(tenThnd);


        formLayout->setLayout(3, QFormLayout::LabelRole, verticalLayout);

        bottom = new QPushButton(CameraScene);
        bottom->setObjectName(QString::fromUtf8("bottom"));

        formLayout->setWidget(3, QFormLayout::FieldRole, bottom);


        retranslateUi(CameraScene);

        QMetaObject::connectSlotsByName(CameraScene);
    } // setupUi

    void retranslateUi(QDialog *CameraScene)
    {
        CameraScene->setWindowTitle(QApplication::translate("CameraScene", "Dialog", 0, QApplication::UnicodeUTF8));
        label_camera->setText(QApplication::translate("CameraScene", "                       Select Please", 0, QApplication::UnicodeUTF8));
        server->setText(QApplication::translate("CameraScene", "Server", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("CameraScene", "Start", 0, QApplication::UnicodeUTF8));
        up->setText(QApplication::translate("CameraScene", "Up", 0, QApplication::UnicodeUTF8));
        tenHund->setText(QApplication::translate("CameraScene", "160x120", 0, QApplication::UnicodeUTF8));
        threeHund->setText(QApplication::translate("CameraScene", "320x240", 0, QApplication::UnicodeUTF8));
        sixHund->setText(QApplication::translate("CameraScene", "640x480", 0, QApplication::UnicodeUTF8));
        tenThnd->setText(QApplication::translate("CameraScene", "1280x960", 0, QApplication::UnicodeUTF8));
        bottom->setText(QApplication::translate("CameraScene", "Bottom", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraScene: public Ui_CameraScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERASCENE_H
