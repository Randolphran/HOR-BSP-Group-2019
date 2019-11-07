/********************************************************************************
** Form generated from reading UI file 'ai_instant.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AI_INSTANT_H
#define UI_AI_INSTANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_AI_InstantFrame
{
public:
    QLabel *lblYCoordinateMax;
    QLabel *lblYCoordinateMid;
    QLabel *lblYCoordinateMin;
    QFrame *graphFrame;
    QLabel *lblXCoordinateStart;
    QLabel *lblXCoordinateEnd;
    QListWidget *listWidget;
    QLabel *lblInterval;
    QLineEdit *edtTimeValue;
    QLabel *lblTimeUnit;
    QSlider *sldTimerValue;
    QPushButton *btnConfigure;
    QPushButton *btnStart;
    QPushButton *btnPause;
    QPushButton *btnStop;

    void setupUi(QDialog *AI_InstantFrame)
    {
        if (AI_InstantFrame->objectName().isEmpty())
            AI_InstantFrame->setObjectName(QStringLiteral("AI_InstantFrame"));
        AI_InstantFrame->resize(762, 520);
        AI_InstantFrame->setMinimumSize(QSize(762, 520));
        AI_InstantFrame->setMaximumSize(QSize(762, 520));
        AI_InstantFrame->setAutoFillBackground(true);
        lblYCoordinateMax = new QLabel(AI_InstantFrame);
        lblYCoordinateMax->setObjectName(QStringLiteral("lblYCoordinateMax"));
        lblYCoordinateMax->setGeometry(QRect(0, 40, 46, 20));
        lblYCoordinateMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblYCoordinateMid = new QLabel(AI_InstantFrame);
        lblYCoordinateMid->setObjectName(QStringLiteral("lblYCoordinateMid"));
        lblYCoordinateMid->setGeometry(QRect(0, 200, 46, 16));
        lblYCoordinateMid->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblYCoordinateMin = new QLabel(AI_InstantFrame);
        lblYCoordinateMin->setObjectName(QStringLiteral("lblYCoordinateMin"));
        lblYCoordinateMin->setGeometry(QRect(0, 362, 46, 16));
        lblYCoordinateMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        graphFrame = new QFrame(AI_InstantFrame);
        graphFrame->setObjectName(QStringLiteral("graphFrame"));
        graphFrame->setGeometry(QRect(47, 39, 660, 340));
        graphFrame->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        lblXCoordinateStart = new QLabel(AI_InstantFrame);
        lblXCoordinateStart->setObjectName(QStringLiteral("lblXCoordinateStart"));
        lblXCoordinateStart->setGeometry(QRect(50, 380, 71, 16));
        lblXCoordinateStart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblXCoordinateEnd = new QLabel(AI_InstantFrame);
        lblXCoordinateEnd->setObjectName(QStringLiteral("lblXCoordinateEnd"));
        lblXCoordinateEnd->setGeometry(QRect(614, 380, 91, 16));
        lblXCoordinateEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        listWidget = new QListWidget(AI_InstantFrame);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(48, 400, 478, 51));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        lblInterval = new QLabel(AI_InstantFrame);
        lblInterval->setObjectName(QStringLiteral("lblInterval"));
        lblInterval->setGeometry(QRect(534, 402, 101, 16));
        lblInterval->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edtTimeValue = new QLineEdit(AI_InstantFrame);
        edtTimeValue->setObjectName(QStringLiteral("edtTimeValue"));
        edtTimeValue->setGeometry(QRect(638, 400, 45, 22));
        edtTimeValue->setAlignment(Qt::AlignCenter);
        edtTimeValue->setReadOnly(true);
        lblTimeUnit = new QLabel(AI_InstantFrame);
        lblTimeUnit->setObjectName(QStringLiteral("lblTimeUnit"));
        lblTimeUnit->setGeometry(QRect(690, 400, 16, 16));
        lblTimeUnit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        sldTimerValue = new QSlider(AI_InstantFrame);
        sldTimerValue->setObjectName(QStringLiteral("sldTimerValue"));
        sldTimerValue->setEnabled(false);
        sldTimerValue->setGeometry(QRect(535, 427, 171, 21));
        sldTimerValue->setMinimum(10);
        sldTimerValue->setMaximum(1000);
        sldTimerValue->setSingleStep(10);
        sldTimerValue->setValue(200);
        sldTimerValue->setOrientation(Qt::Horizontal);
        sldTimerValue->setTickPosition(QSlider::NoTicks);
        btnConfigure = new QPushButton(AI_InstantFrame);
        btnConfigure->setObjectName(QStringLiteral("btnConfigure"));
        btnConfigure->setEnabled(true);
        btnConfigure->setGeometry(QRect(295, 480, 101, 23));
        btnConfigure->setAutoDefault(false);
        btnStart = new QPushButton(AI_InstantFrame);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setEnabled(true);
        btnStart->setGeometry(QRect(460, 480, 75, 23));
        btnPause = new QPushButton(AI_InstantFrame);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        btnPause->setEnabled(false);
        btnPause->setGeometry(QRect(547, 480, 75, 23));
        btnPause->setAutoDefault(false);
        btnStop = new QPushButton(AI_InstantFrame);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setEnabled(false);
        btnStop->setGeometry(QRect(633, 480, 75, 23));
        btnStop->setAutoDefault(false);
        QWidget::setTabOrder(btnConfigure, btnStart);
        QWidget::setTabOrder(btnStart, btnPause);
        QWidget::setTabOrder(btnPause, btnStop);
        QWidget::setTabOrder(btnStop, sldTimerValue);
        QWidget::setTabOrder(sldTimerValue, edtTimeValue);
        QWidget::setTabOrder(edtTimeValue, listWidget);

        retranslateUi(AI_InstantFrame);

        QMetaObject::connectSlotsByName(AI_InstantFrame);
    } // setupUi

    void retranslateUi(QDialog *AI_InstantFrame)
    {
        AI_InstantFrame->setWindowTitle(QApplication::translate("AI_InstantFrame", "AI_Instant", nullptr));
        lblYCoordinateMax->setText(QApplication::translate("AI_InstantFrame", "10.0V", nullptr));
        lblYCoordinateMid->setText(QApplication::translate("AI_InstantFrame", "0", nullptr));
        lblYCoordinateMin->setText(QApplication::translate("AI_InstantFrame", "-10.0V", nullptr));
        lblXCoordinateStart->setText(QApplication::translate("AI_InstantFrame", "0Sec", nullptr));
        lblXCoordinateEnd->setText(QApplication::translate("AI_InstantFrame", "10Sec", nullptr));
        lblInterval->setText(QApplication::translate("AI_InstantFrame", "Sample Interval:", nullptr));
        edtTimeValue->setText(QApplication::translate("AI_InstantFrame", "200", nullptr));
        lblTimeUnit->setText(QApplication::translate("AI_InstantFrame", "ms", nullptr));
        btnConfigure->setText(QApplication::translate("AI_InstantFrame", "Configure", nullptr));
        btnStart->setText(QApplication::translate("AI_InstantFrame", "Start", nullptr));
        btnPause->setText(QApplication::translate("AI_InstantFrame", "Pause", nullptr));
        btnStop->setText(QApplication::translate("AI_InstantFrame", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AI_InstantFrame: public Ui_AI_InstantFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AI_INSTANT_H
