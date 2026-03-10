/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *headerLayout;
    QLabel *titleLabel;
    QSpacerItem *headerSpacer;
    QLabel *connectionStatusLabel;
    QHBoxLayout *infoLayout;
    QGroupBox *playerGroup;
    QFormLayout *playerForm;
    QLabel *playerIdLabel;
    QLabel *playerIdValue;
    QLabel *positionLabel;
    QLabel *positionValue;
    QLabel *moneyLabel;
    QLabel *moneyValue;
    QGroupBox *gameGroup;
    QFormLayout *gameForm;
    QLabel *currentPlayerLabel;
    QLabel *currentPlayerValue;
    QLabel *fieldLabel;
    QLabel *fieldValue;
    QLabel *diceLabel;
    QLabel *diceValue;
    QLabel *turnStatusLabel;
    QLabel *turnStatusValue;
    QHBoxLayout *actionLayout;
    QGroupBox *actionsGroup;
    QVBoxLayout *actionsLayout;
    QPushButton *StartGame_Button;
    QPushButton *rollDiceButton;
    QPushButton *EndTurn_Button;
    QGroupBox *buyGroup;
    QVBoxLayout *buyLayout;
    QLabel *buyPromptLabel;
    QHBoxLayout *buyButtonsLayout;
    QPushButton *BuyDecisonYes_Button;
    QPushButton *BuyDecsionNo_Button;
    QGroupBox *logGroup;
    QVBoxLayout *logLayout;
    QTextEdit *logTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        headerLayout->addWidget(titleLabel);

        headerSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);

        connectionStatusLabel = new QLabel(centralwidget);
        connectionStatusLabel->setObjectName("connectionStatusLabel");

        headerLayout->addWidget(connectionStatusLabel);


        mainLayout->addLayout(headerLayout);

        infoLayout = new QHBoxLayout();
        infoLayout->setObjectName("infoLayout");
        playerGroup = new QGroupBox(centralwidget);
        playerGroup->setObjectName("playerGroup");
        playerForm = new QFormLayout(playerGroup);
        playerForm->setObjectName("playerForm");
        playerIdLabel = new QLabel(playerGroup);
        playerIdLabel->setObjectName("playerIdLabel");

        playerForm->setWidget(0, QFormLayout::ItemRole::LabelRole, playerIdLabel);

        playerIdValue = new QLabel(playerGroup);
        playerIdValue->setObjectName("playerIdValue");

        playerForm->setWidget(0, QFormLayout::ItemRole::FieldRole, playerIdValue);

        positionLabel = new QLabel(playerGroup);
        positionLabel->setObjectName("positionLabel");

        playerForm->setWidget(1, QFormLayout::ItemRole::LabelRole, positionLabel);

        positionValue = new QLabel(playerGroup);
        positionValue->setObjectName("positionValue");

        playerForm->setWidget(1, QFormLayout::ItemRole::FieldRole, positionValue);

        moneyLabel = new QLabel(playerGroup);
        moneyLabel->setObjectName("moneyLabel");

        playerForm->setWidget(2, QFormLayout::ItemRole::LabelRole, moneyLabel);

        moneyValue = new QLabel(playerGroup);
        moneyValue->setObjectName("moneyValue");

        playerForm->setWidget(2, QFormLayout::ItemRole::FieldRole, moneyValue);


        infoLayout->addWidget(playerGroup);

        gameGroup = new QGroupBox(centralwidget);
        gameGroup->setObjectName("gameGroup");
        gameForm = new QFormLayout(gameGroup);
        gameForm->setObjectName("gameForm");
        currentPlayerLabel = new QLabel(gameGroup);
        currentPlayerLabel->setObjectName("currentPlayerLabel");

        gameForm->setWidget(0, QFormLayout::ItemRole::LabelRole, currentPlayerLabel);

        currentPlayerValue = new QLabel(gameGroup);
        currentPlayerValue->setObjectName("currentPlayerValue");

        gameForm->setWidget(0, QFormLayout::ItemRole::FieldRole, currentPlayerValue);

        fieldLabel = new QLabel(gameGroup);
        fieldLabel->setObjectName("fieldLabel");

        gameForm->setWidget(1, QFormLayout::ItemRole::LabelRole, fieldLabel);

        fieldValue = new QLabel(gameGroup);
        fieldValue->setObjectName("fieldValue");

        gameForm->setWidget(1, QFormLayout::ItemRole::FieldRole, fieldValue);

        diceLabel = new QLabel(gameGroup);
        diceLabel->setObjectName("diceLabel");

        gameForm->setWidget(2, QFormLayout::ItemRole::LabelRole, diceLabel);

        diceValue = new QLabel(gameGroup);
        diceValue->setObjectName("diceValue");

        gameForm->setWidget(2, QFormLayout::ItemRole::FieldRole, diceValue);

        turnStatusLabel = new QLabel(gameGroup);
        turnStatusLabel->setObjectName("turnStatusLabel");

        gameForm->setWidget(3, QFormLayout::ItemRole::LabelRole, turnStatusLabel);

        turnStatusValue = new QLabel(gameGroup);
        turnStatusValue->setObjectName("turnStatusValue");

        gameForm->setWidget(3, QFormLayout::ItemRole::FieldRole, turnStatusValue);


        infoLayout->addWidget(gameGroup);


        mainLayout->addLayout(infoLayout);

        actionLayout = new QHBoxLayout();
        actionLayout->setObjectName("actionLayout");
        actionsGroup = new QGroupBox(centralwidget);
        actionsGroup->setObjectName("actionsGroup");
        actionsLayout = new QVBoxLayout(actionsGroup);
        actionsLayout->setObjectName("actionsLayout");
        StartGame_Button = new QPushButton(actionsGroup);
        StartGame_Button->setObjectName("StartGame_Button");

        actionsLayout->addWidget(StartGame_Button);

        rollDiceButton = new QPushButton(actionsGroup);
        rollDiceButton->setObjectName("rollDiceButton");

        actionsLayout->addWidget(rollDiceButton);

        EndTurn_Button = new QPushButton(actionsGroup);
        EndTurn_Button->setObjectName("EndTurn_Button");

        actionsLayout->addWidget(EndTurn_Button);


        actionLayout->addWidget(actionsGroup);

        buyGroup = new QGroupBox(centralwidget);
        buyGroup->setObjectName("buyGroup");
        buyLayout = new QVBoxLayout(buyGroup);
        buyLayout->setObjectName("buyLayout");
        buyPromptLabel = new QLabel(buyGroup);
        buyPromptLabel->setObjectName("buyPromptLabel");
        buyPromptLabel->setWordWrap(true);

        buyLayout->addWidget(buyPromptLabel);

        buyButtonsLayout = new QHBoxLayout();
        buyButtonsLayout->setObjectName("buyButtonsLayout");
        BuyDecisonYes_Button = new QPushButton(buyGroup);
        BuyDecisonYes_Button->setObjectName("BuyDecisonYes_Button");

        buyButtonsLayout->addWidget(BuyDecisonYes_Button);

        BuyDecsionNo_Button = new QPushButton(buyGroup);
        BuyDecsionNo_Button->setObjectName("BuyDecsionNo_Button");

        buyButtonsLayout->addWidget(BuyDecsionNo_Button);


        buyLayout->addLayout(buyButtonsLayout);


        actionLayout->addWidget(buyGroup);

        logGroup = new QGroupBox(centralwidget);
        logGroup->setObjectName("logGroup");
        logLayout = new QVBoxLayout(logGroup);
        logLayout->setObjectName("logLayout");
        logTextEdit = new QTextEdit(logGroup);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setReadOnly(true);

        logLayout->addWidget(logTextEdit);


        actionLayout->addWidget(logGroup);


        mainLayout->addLayout(actionLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Monopoly Client", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Monopoly", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 24px; font-weight: 600;", nullptr));
        connectionStatusLabel->setText(QCoreApplication::translate("MainWindow", "Offline", nullptr));
        connectionStatusLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #b00020; font-weight: 600;", nullptr));
        playerGroup->setTitle(QCoreApplication::translate("MainWindow", "Spieler", nullptr));
        playerIdLabel->setText(QCoreApplication::translate("MainWindow", "Player ID", nullptr));
        playerIdValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        positionLabel->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        positionValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        moneyLabel->setText(QCoreApplication::translate("MainWindow", "Geld", nullptr));
        moneyValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        gameGroup->setTitle(QCoreApplication::translate("MainWindow", "Spielstatus", nullptr));
        currentPlayerLabel->setText(QCoreApplication::translate("MainWindow", "Am Zug", nullptr));
        currentPlayerValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        fieldLabel->setText(QCoreApplication::translate("MainWindow", "Feld", nullptr));
        fieldValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        diceLabel->setText(QCoreApplication::translate("MainWindow", "W\303\274rfel", nullptr));
        diceValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        turnStatusLabel->setText(QCoreApplication::translate("MainWindow", "Zugstatus", nullptr));
        turnStatusValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        actionsGroup->setTitle(QCoreApplication::translate("MainWindow", "Aktionen", nullptr));
        StartGame_Button->setText(QCoreApplication::translate("MainWindow", "Spiel starten", nullptr));
        rollDiceButton->setText(QCoreApplication::translate("MainWindow", "W\303\274rfeln", nullptr));
        EndTurn_Button->setText(QCoreApplication::translate("MainWindow", "Zug beenden", nullptr));
        buyGroup->setTitle(QCoreApplication::translate("MainWindow", "Kaufentscheidung", nullptr));
        buyPromptLabel->setText(QCoreApplication::translate("MainWindow", "Kein Kauf offen.", nullptr));
        BuyDecisonYes_Button->setText(QCoreApplication::translate("MainWindow", "Kaufen", nullptr));
        BuyDecsionNo_Button->setText(QCoreApplication::translate("MainWindow", "Nein danke", nullptr));
        logGroup->setTitle(QCoreApplication::translate("MainWindow", "Spiel-Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
