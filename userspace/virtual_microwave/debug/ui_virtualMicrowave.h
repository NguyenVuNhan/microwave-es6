/********************************************************************************
** Form generated from reading UI file 'virtualMicrowave.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIRTUALMICROWAVE_H
#define UI_VIRTUALMICROWAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VirtualMicrowave
{
public:
    QWidget *centralwidget;
    QPushButton *P90Btn;
    QPushButton *P180Btn;
    QPushButton *P360Btn;
    QPushButton *MemoryBtn;
    QPushButton *P600Btn;
    QPushButton *P900Btn;
    QPushButton *StartBtn;
    QPushButton *StopBtn;
    QPushButton *TimeBtn;
    QGroupBox *TimeDial;
    QPushButton *TImePlusBtn;
    QPushButton *TimeDecreseBtn;
    QLabel *DisplayLabel;
    QPushButton *DoorBtn;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *MemorLEDlbl;
    QLabel *RadiatorLEDlbl;
    QLabel *MicrowaveLEDlbl;
    QPlainTextEdit *loggingInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VirtualMicrowave)
    {
        if (VirtualMicrowave->objectName().isEmpty())
            VirtualMicrowave->setObjectName(QString::fromUtf8("VirtualMicrowave"));
        VirtualMicrowave->resize(557, 392);
        VirtualMicrowave->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(VirtualMicrowave);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget#centralwidget {\n"
"	//background-image: url(:/img/assets/img/background.png);	\n"
"	//background-position: right;\n"
"	//background-size: cover;\n"
"	//background-repeat: no-repeat;\n"
"	//background-position: right top;\n"
"}"));
        P90Btn = new QPushButton(centralwidget);
        P90Btn->setObjectName(QString::fromUtf8("P90Btn"));
        P90Btn->setGeometry(QRect(40, 210, 41, 31));
        P180Btn = new QPushButton(centralwidget);
        P180Btn->setObjectName(QString::fromUtf8("P180Btn"));
        P180Btn->setGeometry(QRect(90, 210, 41, 31));
        P360Btn = new QPushButton(centralwidget);
        P360Btn->setObjectName(QString::fromUtf8("P360Btn"));
        P360Btn->setGeometry(QRect(140, 210, 41, 31));
        MemoryBtn = new QPushButton(centralwidget);
        MemoryBtn->setObjectName(QString::fromUtf8("MemoryBtn"));
        MemoryBtn->setGeometry(QRect(40, 250, 41, 31));
        P600Btn = new QPushButton(centralwidget);
        P600Btn->setObjectName(QString::fromUtf8("P600Btn"));
        P600Btn->setGeometry(QRect(90, 250, 41, 31));
        P900Btn = new QPushButton(centralwidget);
        P900Btn->setObjectName(QString::fromUtf8("P900Btn"));
        P900Btn->setGeometry(QRect(140, 250, 41, 31));
        StartBtn = new QPushButton(centralwidget);
        StartBtn->setObjectName(QString::fromUtf8("StartBtn"));
        StartBtn->setGeometry(QRect(40, 160, 61, 31));
        StopBtn = new QPushButton(centralwidget);
        StopBtn->setObjectName(QString::fromUtf8("StopBtn"));
        StopBtn->setGeometry(QRect(120, 160, 61, 31));
        TimeBtn = new QPushButton(centralwidget);
        TimeBtn->setObjectName(QString::fromUtf8("TimeBtn"));
        TimeBtn->setGeometry(QRect(40, 110, 61, 23));
        TimeDial = new QGroupBox(centralwidget);
        TimeDial->setObjectName(QString::fromUtf8("TimeDial"));
        TimeDial->setGeometry(QRect(110, 80, 71, 61));
        TImePlusBtn = new QPushButton(TimeDial);
        TImePlusBtn->setObjectName(QString::fromUtf8("TImePlusBtn"));
        TImePlusBtn->setGeometry(QRect(20, 20, 31, 23));
        TimeDecreseBtn = new QPushButton(TimeDial);
        TimeDecreseBtn->setObjectName(QString::fromUtf8("TimeDecreseBtn"));
        TimeDecreseBtn->setGeometry(QRect(20, 40, 31, 23));
        DisplayLabel = new QLabel(centralwidget);
        DisplayLabel->setObjectName(QString::fromUtf8("DisplayLabel"));
        DisplayLabel->setGeometry(QRect(30, 10, 151, 61));
        QFont font;
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        DisplayLabel->setFont(font);
        DoorBtn = new QPushButton(centralwidget);
        DoorBtn->setObjectName(QString::fromUtf8("DoorBtn"));
        DoorBtn->setGeometry(QRect(40, 290, 141, 51));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(220, 10, 191, 111));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 91, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 91, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 50, 91, 16));
        MemorLEDlbl = new QLabel(groupBox);
        MemorLEDlbl->setObjectName(QString::fromUtf8("MemorLEDlbl"));
        MemorLEDlbl->setGeometry(QRect(120, 20, 31, 16));
        RadiatorLEDlbl = new QLabel(groupBox);
        RadiatorLEDlbl->setObjectName(QString::fromUtf8("RadiatorLEDlbl"));
        RadiatorLEDlbl->setGeometry(QRect(120, 80, 31, 16));
        MicrowaveLEDlbl = new QLabel(groupBox);
        MicrowaveLEDlbl->setObjectName(QString::fromUtf8("MicrowaveLEDlbl"));
        MicrowaveLEDlbl->setGeometry(QRect(120, 50, 31, 16));
        loggingInfo = new QPlainTextEdit(centralwidget);
        loggingInfo->setObjectName(QString::fromUtf8("loggingInfo"));
        loggingInfo->setGeometry(QRect(220, 140, 191, 201));
        VirtualMicrowave->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VirtualMicrowave);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 557, 20));
        VirtualMicrowave->setMenuBar(menubar);
        statusbar = new QStatusBar(VirtualMicrowave);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        VirtualMicrowave->setStatusBar(statusbar);

        retranslateUi(VirtualMicrowave);

        QMetaObject::connectSlotsByName(VirtualMicrowave);
    } // setupUi

    void retranslateUi(QMainWindow *VirtualMicrowave)
    {
        VirtualMicrowave->setWindowTitle(QCoreApplication::translate("VirtualMicrowave", "VirtualMicrowave", nullptr));
        P90Btn->setText(QCoreApplication::translate("VirtualMicrowave", "90", nullptr));
        P180Btn->setText(QCoreApplication::translate("VirtualMicrowave", "180", nullptr));
        P360Btn->setText(QCoreApplication::translate("VirtualMicrowave", "360", nullptr));
        MemoryBtn->setText(QCoreApplication::translate("VirtualMicrowave", "M", nullptr));
        P600Btn->setText(QCoreApplication::translate("VirtualMicrowave", "600", nullptr));
        P900Btn->setText(QCoreApplication::translate("VirtualMicrowave", "900", nullptr));
        StartBtn->setText(QCoreApplication::translate("VirtualMicrowave", "Start", nullptr));
        StopBtn->setText(QCoreApplication::translate("VirtualMicrowave", "Stop", nullptr));
        TimeBtn->setText(QCoreApplication::translate("VirtualMicrowave", "Time", nullptr));
        TimeDial->setTitle(QCoreApplication::translate("VirtualMicrowave", "Time dial", nullptr));
        TImePlusBtn->setText(QCoreApplication::translate("VirtualMicrowave", "+", nullptr));
        TimeDecreseBtn->setText(QCoreApplication::translate("VirtualMicrowave", "-", nullptr));
        DisplayLabel->setText(QCoreApplication::translate("VirtualMicrowave", "00:00", nullptr));
        DoorBtn->setText(QCoreApplication::translate("VirtualMicrowave", "Door", nullptr));
        groupBox->setTitle(QCoreApplication::translate("VirtualMicrowave", "LEDs", nullptr));
        label->setText(QCoreApplication::translate("VirtualMicrowave", "Memory LED", nullptr));
        label_2->setText(QCoreApplication::translate("VirtualMicrowave", "Radiator LED", nullptr));
        label_3->setText(QCoreApplication::translate("VirtualMicrowave", "Microwave LED", nullptr));
        MemorLEDlbl->setText(QCoreApplication::translate("VirtualMicrowave", "OFF", nullptr));
        RadiatorLEDlbl->setText(QCoreApplication::translate("VirtualMicrowave", "0", nullptr));
        MicrowaveLEDlbl->setText(QCoreApplication::translate("VirtualMicrowave", "OFF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VirtualMicrowave: public Ui_VirtualMicrowave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRTUALMICROWAVE_H
