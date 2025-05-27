/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *ptLog;
    QLineEdit *lePort;
    QPushButton *openBtn;
    QCheckBox *chEcho;
    QCheckBox *chBroadcast;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(835, 591);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 20, 671, 501));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ptLog = new QPlainTextEdit(gridLayoutWidget);
        ptLog->setObjectName("ptLog");
        ptLog->setReadOnly(true);

        gridLayout->addWidget(ptLog, 0, 0, 1, 1);

        lePort = new QLineEdit(gridLayoutWidget);
        lePort->setObjectName("lePort");

        gridLayout->addWidget(lePort, 3, 0, 1, 1);

        openBtn = new QPushButton(gridLayoutWidget);
        openBtn->setObjectName("openBtn");

        gridLayout->addWidget(openBtn, 4, 0, 1, 1);

        chEcho = new QCheckBox(Widget);
        chEcho->setObjectName("chEcho");
        chEcho->setGeometry(QRect(730, 30, 92, 24));
        chEcho->setCheckable(true);
        chBroadcast = new QCheckBox(Widget);
        chBroadcast->setObjectName("chBroadcast");
        chBroadcast->setGeometry(QRect(730, 60, 92, 24));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        ptLog->setPlainText(QString());
        lePort->setText(QString());
        openBtn->setText(QCoreApplication::translate("Widget", "Server Open", nullptr));
        chEcho->setText(QCoreApplication::translate("Widget", "Echo", nullptr));
        chBroadcast->setText(QCoreApplication::translate("Widget", "Broadcast", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
