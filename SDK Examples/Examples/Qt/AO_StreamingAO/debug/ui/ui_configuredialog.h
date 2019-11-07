/********************************************************************************
** Form generated from reading UI file 'configuredialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREDIALOG_H
#define UI_CONFIGUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfigureDialog
{
public:
    QComboBox *cmbDevice;
    QLabel *lblDevice;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QGroupBox *groupBox;
    QComboBox *cmbChannelStart;
    QLabel *lblValueRange;
    QLabel *lblChannelCount;
    QLabel *lblChannelStart;
    QComboBox *cmbValueRange;
    QComboBox *cmbChannelCount;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLineEdit *txtPointCount;
    QLabel *label_2;
    QLineEdit *txtClockRate;
    QLabel *label_3;
    QLabel *lblDevice_2;
    QLineEdit *txtProfilePath;
    QPushButton *btnBrowse;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QStringLiteral("ConfigureDialog"));
        ConfigureDialog->resize(473, 215);
        ConfigureDialog->setMinimumSize(QSize(455, 213));
        cmbDevice = new QComboBox(ConfigureDialog);
        cmbDevice->setObjectName(QStringLiteral("cmbDevice"));
        cmbDevice->setGeometry(QRect(70, 20, 141, 21));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbDevice->sizePolicy().hasHeightForWidth());
        cmbDevice->setSizePolicy(sizePolicy);
        cmbDevice->setLayoutDirection(Qt::LeftToRight);
        lblDevice = new QLabel(ConfigureDialog);
        lblDevice->setObjectName(QStringLiteral("lblDevice"));
        lblDevice->setGeometry(QRect(20, 20, 41, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
        lblDevice->setSizePolicy(sizePolicy1);
        btnOK = new QPushButton(ConfigureDialog);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(270, 181, 75, 23));
        btnCancel = new QPushButton(ConfigureDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(367, 181, 75, 23));
        btnCancel->setAutoDefault(false);
        groupBox = new QGroupBox(ConfigureDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(12, 50, 243, 121));
        cmbChannelStart = new QComboBox(groupBox);
        cmbChannelStart->setObjectName(QStringLiteral("cmbChannelStart"));
        cmbChannelStart->setGeometry(QRect(98, 20, 131, 21));
        sizePolicy.setHeightForWidth(cmbChannelStart->sizePolicy().hasHeightForWidth());
        cmbChannelStart->setSizePolicy(sizePolicy);
        lblValueRange = new QLabel(groupBox);
        lblValueRange->setObjectName(QStringLiteral("lblValueRange"));
        lblValueRange->setGeometry(QRect(8, 84, 91, 22));
        sizePolicy1.setHeightForWidth(lblValueRange->sizePolicy().hasHeightForWidth());
        lblValueRange->setSizePolicy(sizePolicy1);
        lblValueRange->setMinimumSize(QSize(91, 22));
        lblValueRange->setMaximumSize(QSize(91, 22));
        lblChannelCount = new QLabel(groupBox);
        lblChannelCount->setObjectName(QStringLiteral("lblChannelCount"));
        lblChannelCount->setGeometry(QRect(8, 52, 91, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblChannelCount->sizePolicy().hasHeightForWidth());
        lblChannelCount->setSizePolicy(sizePolicy2);
        lblChannelCount->setMinimumSize(QSize(91, 22));
        lblChannelCount->setMaximumSize(QSize(91, 22));
        lblChannelStart = new QLabel(groupBox);
        lblChannelStart->setObjectName(QStringLiteral("lblChannelStart"));
        lblChannelStart->setGeometry(QRect(8, 20, 91, 22));
        lblChannelStart->setMinimumSize(QSize(91, 22));
        lblChannelStart->setMaximumSize(QSize(91, 22));
        cmbValueRange = new QComboBox(groupBox);
        cmbValueRange->setObjectName(QStringLiteral("cmbValueRange"));
        cmbValueRange->setGeometry(QRect(99, 84, 131, 21));
        sizePolicy.setHeightForWidth(cmbValueRange->sizePolicy().hasHeightForWidth());
        cmbValueRange->setSizePolicy(sizePolicy);
        cmbChannelCount = new QComboBox(groupBox);
        cmbChannelCount->setObjectName(QStringLiteral("cmbChannelCount"));
        cmbChannelCount->setGeometry(QRect(99, 52, 131, 21));
        sizePolicy.setHeightForWidth(cmbChannelCount->sizePolicy().hasHeightForWidth());
        cmbChannelCount->setSizePolicy(sizePolicy);
        groupBox_2 = new QGroupBox(ConfigureDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(263, 50, 181, 121));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 17, 161, 16));
        label->setMinimumSize(QSize(131, 16));
        txtPointCount = new QLineEdit(groupBox_2);
        txtPointCount->setObjectName(QStringLiteral("txtPointCount"));
        txtPointCount->setGeometry(QRect(10, 37, 113, 25));
        txtPointCount->setMinimumSize(QSize(113, 25));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 68, 151, 16));
        label_2->setMinimumSize(QSize(131, 16));
        txtClockRate = new QLineEdit(groupBox_2);
        txtClockRate->setObjectName(QStringLiteral("txtClockRate"));
        txtClockRate->setGeometry(QRect(10, 87, 113, 25));
        txtClockRate->setMinimumSize(QSize(113, 25));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(128, 92, 16, 16));
        label_3->setMinimumSize(QSize(16, 16));
        lblDevice_2 = new QLabel(ConfigureDialog);
        lblDevice_2->setObjectName(QStringLiteral("lblDevice_2"));
        lblDevice_2->setGeometry(QRect(220, 20, 51, 20));
        sizePolicy1.setHeightForWidth(lblDevice_2->sizePolicy().hasHeightForWidth());
        lblDevice_2->setSizePolicy(sizePolicy1);
        txtProfilePath = new QLineEdit(ConfigureDialog);
        txtProfilePath->setObjectName(QStringLiteral("txtProfilePath"));
        txtProfilePath->setGeometry(QRect(270, 20, 121, 20));
        btnBrowse = new QPushButton(ConfigureDialog);
        btnBrowse->setObjectName(QStringLiteral("btnBrowse"));
        btnBrowse->setGeometry(QRect(400, 20, 51, 23));
#ifndef QT_NO_SHORTCUT
        lblDevice->setBuddy(cmbDevice);
        lblValueRange->setBuddy(cmbValueRange);
        lblChannelCount->setBuddy(cmbChannelCount);
        lblChannelStart->setBuddy(cmbChannelStart);
        lblDevice_2->setBuddy(cmbDevice);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(cmbDevice, cmbChannelStart);
        QWidget::setTabOrder(cmbChannelStart, cmbChannelCount);
        QWidget::setTabOrder(cmbChannelCount, cmbValueRange);
        QWidget::setTabOrder(cmbValueRange, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(ConfigureDialog);

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QApplication::translate("ConfigureDialog", "Streaming AO - Configuration", nullptr));
        lblDevice->setText(QApplication::translate("ConfigureDialog", "Device:", nullptr));
        btnOK->setText(QApplication::translate("ConfigureDialog", "OK", nullptr));
        btnCancel->setText(QApplication::translate("ConfigureDialog", "Cancel", nullptr));
        groupBox->setTitle(QApplication::translate("ConfigureDialog", "Buffered AO settings", nullptr));
        lblValueRange->setText(QApplication::translate("ConfigureDialog", "Value range:", nullptr));
        lblChannelCount->setText(QApplication::translate("ConfigureDialog", "Channel count:", nullptr));
        lblChannelStart->setText(QApplication::translate("ConfigureDialog", "Channel start:", nullptr));
        groupBox_2->setTitle(QApplication::translate("ConfigureDialog", "Output wave settings", nullptr));
        label->setText(QApplication::translate("ConfigureDialog", "Points for each waveform:", nullptr));
        txtPointCount->setText(QApplication::translate("ConfigureDialog", "400", nullptr));
        label_2->setText(QApplication::translate("ConfigureDialog", "Waveform out frequency:", nullptr));
        txtClockRate->setText(QApplication::translate("ConfigureDialog", "1000", nullptr));
        label_3->setText(QApplication::translate("ConfigureDialog", "Hz", nullptr));
        lblDevice_2->setText(QApplication::translate("ConfigureDialog", "Profile:", nullptr));
        btnBrowse->setText(QApplication::translate("ConfigureDialog", "Browser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
