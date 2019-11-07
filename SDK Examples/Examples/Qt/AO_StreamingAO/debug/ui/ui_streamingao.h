/********************************************************************************
** Form generated from reading UI file 'streamingao.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMINGAO_H
#define UI_STREAMINGAO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_StreamingAOClass
{
public:
    QFrame *background;
    QPushButton *BtnSineA;
    QPushButton *BtnSquareA;
    QPushButton *BtnTriangleA;
    QPushButton *BtnSineB;
    QPushButton *BtnTriangleB;
    QPushButton *BtnSquareB;
    QLineEdit *txtboxHiLevelA;
    QLineEdit *txtboxLoLevelA;
    QLineEdit *txtboxLoLevelB;
    QLineEdit *txtboxHiLevelB;
    QLabel *chLabelA;
    QLabel *chLabelB;
    QPushButton *btnConfigure;
    QPushButton *btnStart;

    void setupUi(QDialog *StreamingAOClass)
    {
        if (StreamingAOClass->objectName().isEmpty())
            StreamingAOClass->setObjectName(QStringLiteral("StreamingAOClass"));
        StreamingAOClass->resize(339, 430);
        StreamingAOClass->setMinimumSize(QSize(339, 430));
        StreamingAOClass->setMaximumSize(QSize(339, 430));
        background = new QFrame(StreamingAOClass);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(-3, -3, 340, 431));
        background->setMinimumSize(QSize(340, 431));
        background->setStyleSheet(QStringLiteral("QFrame#background{background-image:url(:/StreamingAO/Resources/ao.png)}"));
        background->setFrameShape(QFrame::StyledPanel);
        background->setFrameShadow(QFrame::Raised);
        BtnSineA = new QPushButton(background);
        BtnSineA->setObjectName(QStringLiteral("BtnSineA"));
        BtnSineA->setGeometry(QRect(79, 127, 51, 51));
        BtnSineA->setMinimumSize(QSize(51, 51));
        BtnSineA->setMaximumSize(QSize(51, 51));
        BtnSineA->setStyleSheet(QStringLiteral("background:url(:/StreamingAO/Resources/sine.png)"));
        BtnSineA->setCheckable(true);
        BtnSineA->setFlat(true);
        BtnSquareA = new QPushButton(background);
        BtnSquareA->setObjectName(QStringLiteral("BtnSquareA"));
        BtnSquareA->setGeometry(QRect(218, 127, 51, 51));
        BtnSquareA->setMinimumSize(QSize(51, 51));
        BtnSquareA->setMaximumSize(QSize(51, 51));
        BtnSquareA->setStyleSheet(QStringLiteral("background:url(:/StreamingAO/Resources/square.png)"));
        BtnSquareA->setCheckable(true);
        BtnSquareA->setFlat(true);
        BtnTriangleA = new QPushButton(background);
        BtnTriangleA->setObjectName(QStringLiteral("BtnTriangleA"));
        BtnTriangleA->setGeometry(QRect(148, 127, 51, 51));
        BtnTriangleA->setMinimumSize(QSize(51, 51));
        BtnTriangleA->setMaximumSize(QSize(51, 51));
        BtnTriangleA->setStyleSheet(QStringLiteral("background:url(:/StreamingAO/Resources/triangle.png)"));
        BtnTriangleA->setCheckable(true);
        BtnTriangleA->setFlat(true);
        BtnSineB = new QPushButton(background);
        BtnSineB->setObjectName(QStringLiteral("BtnSineB"));
        BtnSineB->setGeometry(QRect(79, 310, 51, 51));
        BtnSineB->setMinimumSize(QSize(51, 51));
        BtnSineB->setMaximumSize(QSize(51, 51));
        BtnSineB->setStyleSheet(QStringLiteral("background:url(:/StreamingAO/Resources/sine.png)"));
        BtnSineB->setCheckable(true);
        BtnSineB->setFlat(true);
        BtnTriangleB = new QPushButton(background);
        BtnTriangleB->setObjectName(QStringLiteral("BtnTriangleB"));
        BtnTriangleB->setGeometry(QRect(150, 310, 51, 51));
        BtnTriangleB->setMinimumSize(QSize(51, 51));
        BtnTriangleB->setMaximumSize(QSize(51, 51));
        BtnTriangleB->setStyleSheet(QStringLiteral("background:url(:/StreamingAO/Resources/triangle.png)"));
        BtnTriangleB->setCheckable(true);
        BtnTriangleB->setFlat(true);
        BtnSquareB = new QPushButton(background);
        BtnSquareB->setObjectName(QStringLiteral("BtnSquareB"));
        BtnSquareB->setGeometry(QRect(218, 310, 51, 51));
        BtnSquareB->setMinimumSize(QSize(51, 51));
        BtnSquareB->setMaximumSize(QSize(51, 51));
        BtnSquareB->setStyleSheet(QStringLiteral("background:url(:/StreamingAO/Resources/square.png)"));
        BtnSquareB->setCheckable(true);
        BtnSquareB->setFlat(true);
        txtboxHiLevelA = new QLineEdit(background);
        txtboxHiLevelA->setObjectName(QStringLiteral("txtboxHiLevelA"));
        txtboxHiLevelA->setGeometry(QRect(83, 91, 73, 20));
        txtboxHiLevelA->setMinimumSize(QSize(73, 20));
        txtboxHiLevelA->setMaximumSize(QSize(73, 20));
        txtboxLoLevelA = new QLineEdit(background);
        txtboxLoLevelA->setObjectName(QStringLiteral("txtboxLoLevelA"));
        txtboxLoLevelA->setGeometry(QRect(193, 90, 73, 20));
        txtboxLoLevelA->setMinimumSize(QSize(73, 20));
        txtboxLoLevelA->setMaximumSize(QSize(73, 20));
        txtboxLoLevelB = new QLineEdit(background);
        txtboxLoLevelB->setObjectName(QStringLiteral("txtboxLoLevelB"));
        txtboxLoLevelB->setGeometry(QRect(193, 275, 73, 20));
        txtboxLoLevelB->setMinimumSize(QSize(73, 20));
        txtboxLoLevelB->setMaximumSize(QSize(73, 20));
        txtboxHiLevelB = new QLineEdit(background);
        txtboxHiLevelB->setObjectName(QStringLiteral("txtboxHiLevelB"));
        txtboxHiLevelB->setGeometry(QRect(83, 276, 73, 20));
        txtboxHiLevelB->setMinimumSize(QSize(73, 20));
        txtboxHiLevelB->setMaximumSize(QSize(73, 20));
        chLabelA = new QLabel(background);
        chLabelA->setObjectName(QStringLiteral("chLabelA"));
        chLabelA->setGeometry(QRect(228, 33, 16, 16));
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
        chLabelB->setGeometry(QRect(229, 218, 16, 16));
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
        btnConfigure = new QPushButton(background);
        btnConfigure->setObjectName(QStringLiteral("btnConfigure"));
        btnConfigure->setGeometry(QRect(125, 394, 75, 23));
        btnConfigure->setMinimumSize(QSize(75, 23));
        btnConfigure->setMaximumSize(QSize(75, 23));
        btnStart = new QPushButton(background);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setGeometry(QRect(226, 394, 75, 23));
        btnStart->setMinimumSize(QSize(75, 23));
        btnStart->setMaximumSize(QSize(75, 23));

        retranslateUi(StreamingAOClass);

        QMetaObject::connectSlotsByName(StreamingAOClass);
    } // setupUi

    void retranslateUi(QDialog *StreamingAOClass)
    {
        StreamingAOClass->setWindowTitle(QApplication::translate("StreamingAOClass", "Streaming AO", nullptr));
        BtnSineA->setText(QString());
        BtnSquareA->setText(QString());
        BtnTriangleA->setText(QString());
        BtnSineB->setText(QString());
        BtnTriangleB->setText(QString());
        BtnSquareB->setText(QString());
        txtboxHiLevelA->setText(QApplication::translate("StreamingAOClass", "5", nullptr));
        txtboxLoLevelA->setText(QApplication::translate("StreamingAOClass", "-5", nullptr));
        txtboxLoLevelB->setText(QApplication::translate("StreamingAOClass", "-5", nullptr));
        txtboxHiLevelB->setText(QApplication::translate("StreamingAOClass", "5", nullptr));
        chLabelA->setText(QApplication::translate("StreamingAOClass", "0", nullptr));
        chLabelB->setText(QApplication::translate("StreamingAOClass", "1", nullptr));
        btnConfigure->setText(QApplication::translate("StreamingAOClass", "Configure", nullptr));
        btnStart->setText(QApplication::translate("StreamingAOClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StreamingAOClass: public Ui_StreamingAOClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMINGAO_H
