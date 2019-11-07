/********************************************************************************
** Form generated from reading UI file 'staticao.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATICAO_H
#define UI_STATICAO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_StaticAOClass
{
public:
    QFrame *background;
    QPushButton *BtnSineA;
    QPushButton *BtnTriangleA;
    QPushButton *BtnSquareA;
    QPushButton *BtnSineB;
    QPushButton *BtnTriangleB;
    QPushButton *BtnSquareB;
    QPushButton *BtnManualB;
    QPushButton *BtnManualA;
    QLineEdit *txtboxHiLevelA;
    QLineEdit *txtboxLoLevelA;
    QLineEdit *txtboxValueA;
    QLineEdit *txtboxHiLevelB;
    QLineEdit *txtboxLoLevelB;
    QLineEdit *txtboxValueB;
    QLabel *chLabelA;
    QLabel *chLabelB;
    QSlider *timerTrackBar;
    QLabel *timerFreqLabel;
    QPushButton *btnConfigure;

    void setupUi(QDialog *StaticAOClass)
    {
        if (StaticAOClass->objectName().isEmpty())
            StaticAOClass->setObjectName(QStringLiteral("StaticAOClass"));
        StaticAOClass->resize(389, 447);
        StaticAOClass->setMinimumSize(QSize(389, 447));
        StaticAOClass->setMaximumSize(QSize(389, 447));
        background = new QFrame(StaticAOClass);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(-1, -3, 391, 451));
        background->setAutoFillBackground(false);
        background->setStyleSheet(QStringLiteral("QFrame#background{background-image:url(:/StaticAO/Resources/AO.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        BtnSineA = new QPushButton(background);
        BtnSineA->setObjectName(QStringLiteral("BtnSineA"));
        BtnSineA->setGeometry(QRect(70, 124, 51, 51));
        BtnSineA->setMinimumSize(QSize(51, 51));
        BtnSineA->setMaximumSize(QSize(51, 51));
        BtnSineA->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/sine.png)"));
        BtnSineA->setCheckable(true);
        BtnSineA->setFlat(true);
        BtnTriangleA = new QPushButton(background);
        BtnTriangleA->setObjectName(QStringLiteral("BtnTriangleA"));
        BtnTriangleA->setGeometry(QRect(136, 124, 51, 51));
        BtnTriangleA->setMinimumSize(QSize(51, 51));
        BtnTriangleA->setMaximumSize(QSize(51, 51));
        BtnTriangleA->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/triangle.png)"));
        BtnTriangleA->setCheckable(true);
        BtnTriangleA->setFlat(true);
        BtnSquareA = new QPushButton(background);
        BtnSquareA->setObjectName(QStringLiteral("BtnSquareA"));
        BtnSquareA->setGeometry(QRect(203, 125, 51, 51));
        BtnSquareA->setMinimumSize(QSize(51, 51));
        BtnSquareA->setMaximumSize(QSize(51, 51));
        BtnSquareA->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/square.png)"));
        BtnSquareA->setCheckable(true);
        BtnSquareA->setFlat(true);
        BtnSineB = new QPushButton(background);
        BtnSineB->setObjectName(QStringLiteral("BtnSineB"));
        BtnSineB->setGeometry(QRect(70, 301, 51, 51));
        BtnSineB->setMinimumSize(QSize(51, 51));
        BtnSineB->setMaximumSize(QSize(51, 51));
        BtnSineB->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/sine.png)"));
        BtnSineB->setCheckable(true);
        BtnSineB->setFlat(true);
        BtnTriangleB = new QPushButton(background);
        BtnTriangleB->setObjectName(QStringLiteral("BtnTriangleB"));
        BtnTriangleB->setGeometry(QRect(139, 302, 51, 51));
        BtnTriangleB->setMinimumSize(QSize(51, 51));
        BtnTriangleB->setMaximumSize(QSize(51, 51));
        BtnTriangleB->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/triangle.png)"));
        BtnTriangleB->setCheckable(true);
        BtnTriangleB->setFlat(true);
        BtnSquareB = new QPushButton(background);
        BtnSquareB->setObjectName(QStringLiteral("BtnSquareB"));
        BtnSquareB->setGeometry(QRect(207, 303, 51, 51));
        BtnSquareB->setMinimumSize(QSize(51, 51));
        BtnSquareB->setMaximumSize(QSize(51, 51));
        BtnSquareB->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/square.png)"));
        BtnSquareB->setCheckable(true);
        BtnSquareB->setFlat(true);
        BtnManualB = new QPushButton(background);
        BtnManualB->setObjectName(QStringLiteral("BtnManualB"));
        BtnManualB->setGeometry(QRect(288, 303, 51, 51));
        BtnManualB->setMinimumSize(QSize(51, 51));
        BtnManualB->setMaximumSize(QSize(51, 51));
        BtnManualB->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/manual.png)"));
        BtnManualB->setCheckable(false);
        BtnManualB->setFlat(true);
        BtnManualA = new QPushButton(background);
        BtnManualA->setObjectName(QStringLiteral("BtnManualA"));
        BtnManualA->setGeometry(QRect(290, 125, 51, 51));
        BtnManualA->setMinimumSize(QSize(51, 51));
        BtnManualA->setMaximumSize(QSize(51, 51));
        BtnManualA->setStyleSheet(QStringLiteral("background:url(:/StaticAO/Resources/manual.png)"));
        BtnManualA->setCheckable(false);
        BtnManualA->setFlat(true);
        txtboxHiLevelA = new QLineEdit(background);
        txtboxHiLevelA->setObjectName(QStringLiteral("txtboxHiLevelA"));
        txtboxHiLevelA->setGeometry(QRect(73, 90, 73, 20));
        txtboxHiLevelA->setMinimumSize(QSize(73, 20));
        txtboxHiLevelA->setMaximumSize(QSize(73, 20));
        txtboxLoLevelA = new QLineEdit(background);
        txtboxLoLevelA->setObjectName(QStringLiteral("txtboxLoLevelA"));
        txtboxLoLevelA->setGeometry(QRect(165, 90, 73, 20));
        txtboxLoLevelA->setMinimumSize(QSize(73, 20));
        txtboxLoLevelA->setMaximumSize(QSize(73, 20));
        txtboxValueA = new QLineEdit(background);
        txtboxValueA->setObjectName(QStringLiteral("txtboxValueA"));
        txtboxValueA->setGeometry(QRect(280, 90, 65, 20));
        txtboxValueA->setMinimumSize(QSize(65, 20));
        txtboxValueA->setMaximumSize(QSize(65, 20));
        txtboxHiLevelB = new QLineEdit(background);
        txtboxHiLevelB->setObjectName(QStringLiteral("txtboxHiLevelB"));
        txtboxHiLevelB->setGeometry(QRect(73, 269, 73, 20));
        txtboxHiLevelB->setMinimumSize(QSize(73, 20));
        txtboxHiLevelB->setMaximumSize(QSize(73, 20));
        txtboxLoLevelB = new QLineEdit(background);
        txtboxLoLevelB->setObjectName(QStringLiteral("txtboxLoLevelB"));
        txtboxLoLevelB->setGeometry(QRect(165, 267, 73, 20));
        txtboxLoLevelB->setMinimumSize(QSize(73, 20));
        txtboxLoLevelB->setMaximumSize(QSize(73, 20));
        txtboxValueB = new QLineEdit(background);
        txtboxValueB->setObjectName(QStringLiteral("txtboxValueB"));
        txtboxValueB->setGeometry(QRect(280, 267, 65, 20));
        txtboxValueB->setMinimumSize(QSize(65, 20));
        txtboxValueB->setMaximumSize(QSize(65, 20));
        chLabelA = new QLabel(background);
        chLabelA->setObjectName(QStringLiteral("chLabelA"));
        chLabelA->setGeometry(QRect(268, 34, 16, 16));
        chLabelA->setMinimumSize(QSize(16, 16));
        chLabelA->setMaximumSize(QSize(16, 16));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        chLabelA->setFont(font);
        chLabelA->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));
        chLabelA->setTextFormat(Qt::RichText);
        chLabelA->setAlignment(Qt::AlignCenter);
        chLabelB = new QLabel(background);
        chLabelB->setObjectName(QStringLiteral("chLabelB"));
        chLabelB->setGeometry(QRect(271, 211, 16, 16));
        chLabelB->setMinimumSize(QSize(16, 16));
        chLabelB->setMaximumSize(QSize(16, 16));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        chLabelB->setFont(font1);
        chLabelB->setStyleSheet(QStringLiteral("color:rgb(255, 170, 0)"));
        chLabelB->setTextFormat(Qt::RichText);
        chLabelB->setAlignment(Qt::AlignCenter);
        timerTrackBar = new QSlider(background);
        timerTrackBar->setObjectName(QStringLiteral("timerTrackBar"));
        timerTrackBar->setGeometry(QRect(140, 403, 111, 21));
        timerTrackBar->setMinimum(10);
        timerTrackBar->setMaximum(1000);
        timerTrackBar->setValue(50);
        timerTrackBar->setOrientation(Qt::Horizontal);
        timerFreqLabel = new QLabel(background);
        timerFreqLabel->setObjectName(QStringLiteral("timerFreqLabel"));
        timerFreqLabel->setGeometry(QRect(253, 405, 41, 16));
        timerFreqLabel->setMinimumSize(QSize(41, 16));
        timerFreqLabel->setMaximumSize(QSize(41, 16));
        btnConfigure = new QPushButton(background);
        btnConfigure->setObjectName(QStringLiteral("btnConfigure"));
        btnConfigure->setGeometry(QRect(298, 401, 75, 23));
        btnConfigure->setMinimumSize(QSize(75, 23));
        btnConfigure->setMaximumSize(QSize(75, 23));

        retranslateUi(StaticAOClass);

        QMetaObject::connectSlotsByName(StaticAOClass);
    } // setupUi

    void retranslateUi(QDialog *StaticAOClass)
    {
        StaticAOClass->setWindowTitle(QApplication::translate("StaticAOClass", "Static AO", nullptr));
        BtnSineA->setText(QString());
        BtnTriangleA->setText(QString());
        BtnSquareA->setText(QString());
        BtnSineB->setText(QString());
        BtnTriangleB->setText(QString());
        BtnSquareB->setText(QString());
        BtnManualB->setText(QString());
        BtnManualA->setText(QString());
        txtboxHiLevelA->setText(QApplication::translate("StaticAOClass", "5", nullptr));
        txtboxLoLevelA->setText(QApplication::translate("StaticAOClass", "-5", nullptr));
        txtboxValueA->setText(QApplication::translate("StaticAOClass", "2.5", nullptr));
        txtboxHiLevelB->setText(QApplication::translate("StaticAOClass", "5", nullptr));
        txtboxLoLevelB->setText(QApplication::translate("StaticAOClass", "-5", nullptr));
        txtboxValueB->setText(QApplication::translate("StaticAOClass", "2.5", nullptr));
        chLabelA->setText(QApplication::translate("StaticAOClass", "0", nullptr));
        chLabelB->setText(QApplication::translate("StaticAOClass", "1", nullptr));
        timerFreqLabel->setText(QApplication::translate("StaticAOClass", "50ms", nullptr));
        btnConfigure->setText(QApplication::translate("StaticAOClass", "Configure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StaticAOClass: public Ui_StaticAOClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATICAO_H
