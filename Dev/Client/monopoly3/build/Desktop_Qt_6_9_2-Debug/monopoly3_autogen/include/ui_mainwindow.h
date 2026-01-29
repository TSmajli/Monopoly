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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *gameView;
    QWidget *Spieleraktivitaet_3;
    QWidget *Spielerfarbe_3;
    QTextEdit *textEdit_3;
    QWidget *Brettspiel_2;
    QWidget *Feld29_3;
    QWidget *widget_46;
    QWidget *Feld4_3;
    QWidget *Feld6_3;
    QWidget *widget_47;
    QWidget *Feld27_3;
    QWidget *widget_48;
    QWidget *Feld26_3;
    QWidget *widget_49;
    QWidget *Feld8_3;
    QWidget *widget_50;
    QWidget *Feld18_3;
    QWidget *widget_51;
    QWidget *Feld36_3;
    QWidget *Feld10_4;
    QWidget *Feld10_5;
    QLabel *label_18;
    QLabel *label_19;
    QWidget *Feld16_3;
    QWidget *widget_52;
    QWidget *Feld25_3;
    QWidget *Feld11_3;
    QLabel *label_20;
    QLabel *label_21;
    QWidget *Feld12_3;
    QLabel *label_12;
    QWidget *Feld7_3;
    QLabel *label_23;
    QLabel *label_24;
    QWidget *Feld5_3;
    QLabel *label_25;
    QWidget *Feld23_3;
    QWidget *widget_53;
    QWidget *Feld17_3;
    QWidget *widget_54;
    QWidget *Feld15_3;
    QLabel *label_26;
    QWidget *Feld19_3;
    QWidget *widget_55;
    QWidget *Feld33_3;
    QLabel *label_27;
    QLabel *label_28;
    QWidget *Feld39_3;
    QWidget *widget_56;
    QWidget *Feld30_3;
    QWidget *Feld32_3;
    QWidget *widget_57;
    QWidget *Feld24_3;
    QWidget *widget_58;
    QWidget *Feld1_3;
    QWidget *widget_59;
    QWidget *Feld31_3;
    QWidget *widget_60;
    QWidget *Feld2_3;
    QLabel *label_29;
    QLabel *label_30;
    QWidget *Feld0_3;
    QLabel *label_31;
    QWidget *Feld37_3;
    QWidget *widget_61;
    QWidget *Feld34_3;
    QWidget *widget_62;
    QWidget *Feld22_3;
    QWidget *Feld21_3;
    QWidget *widget_63;
    QWidget *Feld28_3;
    QLabel *label_34;
    QLabel *label_11;
    QWidget *Feld38_3;
    QWidget *Feld9_3;
    QWidget *widget_64;
    QWidget *Feld35_3;
    QWidget *Feld14_3;
    QWidget *widget_65;
    QWidget *Feld3_3;
    QWidget *widget_66;
    QWidget *Feld20_3;
    QWidget *Feld13_3;
    QWidget *widget_67;
    QPushButton *wurfeln;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_10;
    QPushButton *rollDiceButton;
    QLabel *diceResult;
    QWidget *Spieleranzeige_3;
    QWidget *Spieler_3;
    QWidget *Spielerfarbe_7;
    QLabel *Geld_5;
    QLabel *Geld_6;
    QPushButton *backButton;
    QPushButton *buyButton;
    QPushButton *readyButton;
    QPushButton *buyProperty;
    QPushButton *sellButton;
    QWidget *widget_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_48;
    QWidget *csvView;
    QWidget *startView;
    QWidget *widget;
    QPushButton *player1;
    QPushButton *player2;
    QLabel *label;
    QPushButton *player3;
    QPushButton *player4;
    QPushButton *addPlayer;
    QLabel *label_2;
    QLineEdit *playerNameInput;
    QPushButton *startButton;
    QLabel *startLabel;
    QPushButton *importCSVbutton;
    QPushButton *ServerButton;
    QWidget *widget_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1078);
        MainWindow->setMinimumSize(QSize(1920, 1078));
        MainWindow->setMaximumSize(QSize(1920, 1080));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #4e6a84;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        gameView = new QWidget();
        gameView->setObjectName("gameView");
        gameView->setEnabled(true);
        Spieleraktivitaet_3 = new QWidget(gameView);
        Spieleraktivitaet_3->setObjectName("Spieleraktivitaet_3");
        Spieleraktivitaet_3->setGeometry(QRect(10, 30, 500, 800));
        Spieleraktivitaet_3->setMinimumSize(QSize(500, 800));
        Spieleraktivitaet_3->setMaximumSize(QSize(500, 800));
        Spieleraktivitaet_3->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;\n"
"border: 2px #84b6e6;\n"
"\n"
""));
        Spielerfarbe_3 = new QWidget(Spieleraktivitaet_3);
        Spielerfarbe_3->setObjectName("Spielerfarbe_3");
        Spielerfarbe_3->setGeometry(QRect(20, 20, 30, 30));
        Spielerfarbe_3->setStyleSheet(QString::fromUtf8("background-color: white;\n"
""));
        textEdit_3 = new QTextEdit(Spieleraktivitaet_3);
        textEdit_3->setObjectName("textEdit_3");
        textEdit_3->setGeometry(QRect(70, 20, 401, 31));
        textEdit_3->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"font-weight: 800;\n"
"font-size : 15px;"));
        Brettspiel_2 = new QWidget(gameView);
        Brettspiel_2->setObjectName("Brettspiel_2");
        Brettspiel_2->setGeometry(QRect(530, 30, 800, 800));
        Brettspiel_2->setStyleSheet(QString::fromUtf8("background-color: #4e6a84;\n"
"border:3px solid black;"));
        Feld29_3 = new QWidget(Brettspiel_2);
        Feld29_3->setObjectName("Feld29_3");
        Feld29_3->setGeometry(QRect(124, 674, 63, 126));
        Feld29_3->setMinimumSize(QSize(63, 126));
        Feld29_3->setMaximumSize(QSize(63, 126));
        Feld29_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_46 = new QWidget(Feld29_3);
        widget_46->setObjectName("widget_46");
        widget_46->setGeometry(QRect(0, 0, 63, 25));
        widget_46->setMinimumSize(QSize(63, 25));
        widget_46->setMaximumSize(QSize(63, 25));
        widget_46->setBaseSize(QSize(63, 20));
        widget_46->setStyleSheet(QString::fromUtf8("background-color: #fce300;"));
        Feld4_3 = new QWidget(Brettspiel_2);
        Feld4_3->setObjectName("Feld4_3");
        Feld4_3->setGeometry(QRect(307, 0, 63, 126));
        Feld4_3->setMinimumSize(QSize(63, 126));
        Feld4_3->setMaximumSize(QSize(63, 126));
        Feld4_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        Feld6_3 = new QWidget(Brettspiel_2);
        Feld6_3->setObjectName("Feld6_3");
        Feld6_3->setGeometry(QRect(429, 0, 63, 126));
        Feld6_3->setMinimumSize(QSize(63, 126));
        Feld6_3->setMaximumSize(QSize(63, 126));
        Feld6_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_47 = new QWidget(Feld6_3);
        widget_47->setObjectName("widget_47");
        widget_47->setGeometry(QRect(0, 101, 63, 25));
        widget_47->setMinimumSize(QSize(63, 25));
        widget_47->setMaximumSize(QSize(63, 25));
        widget_47->setBaseSize(QSize(63, 20));
        widget_47->setStyleSheet(QString::fromUtf8("background-color: #9AD9F5;"));
        Feld27_3 = new QWidget(Brettspiel_2);
        Feld27_3->setObjectName("Feld27_3");
        Feld27_3->setGeometry(QRect(246, 674, 63, 126));
        Feld27_3->setMinimumSize(QSize(63, 126));
        Feld27_3->setMaximumSize(QSize(63, 126));
        Feld27_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_48 = new QWidget(Feld27_3);
        widget_48->setObjectName("widget_48");
        widget_48->setGeometry(QRect(0, 0, 63, 25));
        widget_48->setMinimumSize(QSize(63, 25));
        widget_48->setMaximumSize(QSize(63, 25));
        widget_48->setBaseSize(QSize(63, 20));
        widget_48->setStyleSheet(QString::fromUtf8("background-color: #fce300;"));
        Feld26_3 = new QWidget(Brettspiel_2);
        Feld26_3->setObjectName("Feld26_3");
        Feld26_3->setGeometry(QRect(307, 674, 63, 126));
        Feld26_3->setMinimumSize(QSize(63, 126));
        Feld26_3->setMaximumSize(QSize(63, 126));
        Feld26_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_49 = new QWidget(Feld26_3);
        widget_49->setObjectName("widget_49");
        widget_49->setGeometry(QRect(0, 0, 63, 25));
        widget_49->setMinimumSize(QSize(63, 25));
        widget_49->setMaximumSize(QSize(63, 25));
        widget_49->setBaseSize(QSize(63, 20));
        widget_49->setStyleSheet(QString::fromUtf8("background-color: #fce300;"));
        Feld8_3 = new QWidget(Brettspiel_2);
        Feld8_3->setObjectName("Feld8_3");
        Feld8_3->setGeometry(QRect(552, 0, 63, 126));
        Feld8_3->setMinimumSize(QSize(63, 126));
        Feld8_3->setMaximumSize(QSize(63, 126));
        Feld8_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_50 = new QWidget(Feld8_3);
        widget_50->setObjectName("widget_50");
        widget_50->setGeometry(QRect(0, 101, 63, 25));
        widget_50->setMinimumSize(QSize(63, 25));
        widget_50->setMaximumSize(QSize(63, 25));
        widget_50->setBaseSize(QSize(63, 20));
        widget_50->setStyleSheet(QString::fromUtf8("background-color: #9AD9F5;"));
        Feld18_3 = new QWidget(Brettspiel_2);
        Feld18_3->setObjectName("Feld18_3");
        Feld18_3->setGeometry(QRect(674, 552, 126, 63));
        Feld18_3->setMinimumSize(QSize(126, 63));
        Feld18_3->setMaximumSize(QSize(126, 63));
        Feld18_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_51 = new QWidget(Feld18_3);
        widget_51->setObjectName("widget_51");
        widget_51->setGeometry(QRect(0, 0, 25, 63));
        widget_51->setMinimumSize(QSize(25, 63));
        widget_51->setMaximumSize(QSize(25, 63));
        widget_51->setBaseSize(QSize(63, 20));
        widget_51->setStyleSheet(QString::fromUtf8("background-color: #F7941D;"));
        Feld36_3 = new QWidget(Brettspiel_2);
        Feld36_3->setObjectName("Feld36_3");
        Feld36_3->setGeometry(QRect(0, 308, 126, 63));
        Feld36_3->setMinimumSize(QSize(126, 63));
        Feld36_3->setMaximumSize(QSize(126, 63));
        Feld36_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        Feld10_4 = new QWidget(Brettspiel_2);
        Feld10_4->setObjectName("Feld10_4");
        Feld10_4->setGeometry(QRect(674, 1, 126, 126));
        Feld10_4->setMinimumSize(QSize(126, 126));
        Feld10_4->setMaximumSize(QSize(126, 126));
        Feld10_4->setStyleSheet(QString::fromUtf8("background-color: lightgray;"));
        Feld10_5 = new QWidget(Feld10_4);
        Feld10_5->setObjectName("Feld10_5");
        Feld10_5->setGeometry(QRect(0, 56, 70, 70));
        Feld10_5->setMinimumSize(QSize(70, 70));
        Feld10_5->setMaximumSize(QSize(50, 50));
        Feld10_5->setStyleSheet(QString::fromUtf8("background-color: lightgray;"));
        label_18 = new QLabel(Feld10_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(5, 28, 61, 31));
        label_18->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_18->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_18->setTextFormat(Qt::TextFormat::AutoText);
        label_18->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        label_19 = new QLabel(Feld10_4);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(30, 20, 71, 31));
        label_19->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_19->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_19->setTextFormat(Qt::TextFormat::AutoText);
        label_19->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        Feld16_3 = new QWidget(Brettspiel_2);
        Feld16_3->setObjectName("Feld16_3");
        Feld16_3->setGeometry(QRect(674, 429, 126, 63));
        Feld16_3->setMinimumSize(QSize(126, 63));
        Feld16_3->setMaximumSize(QSize(126, 63));
        Feld16_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_52 = new QWidget(Feld16_3);
        widget_52->setObjectName("widget_52");
        widget_52->setGeometry(QRect(0, 0, 25, 63));
        widget_52->setMinimumSize(QSize(25, 63));
        widget_52->setMaximumSize(QSize(25, 63));
        widget_52->setBaseSize(QSize(63, 20));
        widget_52->setStyleSheet(QString::fromUtf8("background-color: #F7941D;"));
        Feld25_3 = new QWidget(Brettspiel_2);
        Feld25_3->setObjectName("Feld25_3");
        Feld25_3->setGeometry(QRect(368, 674, 63, 126));
        Feld25_3->setMinimumSize(QSize(63, 126));
        Feld25_3->setMaximumSize(QSize(63, 126));
        Feld25_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        Feld11_3 = new QWidget(Brettspiel_2);
        Feld11_3->setObjectName("Feld11_3");
        Feld11_3->setGeometry(QRect(674, 490, 126, 64));
        Feld11_3->setMinimumSize(QSize(126, 64));
        Feld11_3->setMaximumSize(QSize(126, 64));
        Feld11_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        label_20 = new QLabel(Feld11_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 12, 45, 42));
        label_20->setMinimumSize(QSize(0, 42));
        label_20->setMaximumSize(QSize(45, 25));
        label_20->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"background-color: transparent;\n"
"\n"
""));
        label_20->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/lehren(1).png")));
        label_20->setScaledContents(true);
        label_20->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        label_21 = new QLabel(Feld11_3);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(70, 20, 51, 31));
        label_21->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_21->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;\n"
"color:black;"));
        label_21->setTextFormat(Qt::TextFormat::AutoText);
        label_21->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        Feld12_3 = new QWidget(Brettspiel_2);
        Feld12_3->setObjectName("Feld12_3");
        Feld12_3->setGeometry(QRect(674, 186, 126, 63));
        Feld12_3->setMinimumSize(QSize(126, 63));
        Feld12_3->setMaximumSize(QSize(126, 63));
        Feld12_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        label_12 = new QLabel(Feld12_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(40, 0, 51, 61));
        label_12->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/water-dispenser.png")));
        label_12->setScaledContents(true);
        Feld7_3 = new QWidget(Brettspiel_2);
        Feld7_3->setObjectName("Feld7_3");
        Feld7_3->setGeometry(QRect(490, 0, 64, 126));
        Feld7_3->setMinimumSize(QSize(64, 126));
        Feld7_3->setMaximumSize(QSize(64, 126));
        Feld7_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        label_23 = new QLabel(Feld7_3);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(1, 76, 60, 51));
        label_23->setMinimumSize(QSize(0, 42));
        label_23->setMaximumSize(QSize(70, 70));
        label_23->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        label_23->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;\n"
"\n"
""));
        label_23->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/lehren.png")));
        label_23->setScaledContents(true);
        label_24 = new QLabel(Feld7_3);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(5, 10, 51, 31));
        label_24->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_24->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_24->setTextFormat(Qt::TextFormat::AutoText);
        label_24->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        label_24->raise();
        label_23->raise();
        Feld5_3 = new QWidget(Brettspiel_2);
        Feld5_3->setObjectName("Feld5_3");
        Feld5_3->setGeometry(QRect(368, 0, 63, 126));
        Feld5_3->setMinimumSize(QSize(63, 126));
        Feld5_3->setMaximumSize(QSize(63, 126));
        Feld5_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        label_25 = new QLabel(Feld5_3);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(8, 70, 51, 31));
        label_25->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_25->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_25->setTextFormat(Qt::TextFormat::AutoText);
        label_25->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        Feld23_3 = new QWidget(Brettspiel_2);
        Feld23_3->setObjectName("Feld23_3");
        Feld23_3->setGeometry(QRect(490, 674, 64, 126));
        Feld23_3->setMinimumSize(QSize(64, 126));
        Feld23_3->setMaximumSize(QSize(64, 126));
        Feld23_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_53 = new QWidget(Feld23_3);
        widget_53->setObjectName("widget_53");
        widget_53->setGeometry(QRect(1, 0, 63, 25));
        widget_53->setMinimumSize(QSize(63, 25));
        widget_53->setMaximumSize(QSize(63, 25));
        widget_53->setBaseSize(QSize(63, 20));
        widget_53->setStyleSheet(QString::fromUtf8("background-color: #ED1B24;"));
        Feld17_3 = new QWidget(Brettspiel_2);
        Feld17_3->setObjectName("Feld17_3");
        Feld17_3->setGeometry(QRect(674, 125, 126, 63));
        Feld17_3->setMinimumSize(QSize(126, 63));
        Feld17_3->setMaximumSize(QSize(126, 63));
        Feld17_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_54 = new QWidget(Feld17_3);
        widget_54->setObjectName("widget_54");
        widget_54->setGeometry(QRect(0, 0, 25, 63));
        widget_54->setMinimumSize(QSize(25, 63));
        widget_54->setMaximumSize(QSize(25, 63));
        widget_54->setBaseSize(QSize(63, 20));
        widget_54->setStyleSheet(QString::fromUtf8("background-color: #D93A96;"));
        Feld15_3 = new QWidget(Brettspiel_2);
        Feld15_3->setObjectName("Feld15_3");
        Feld15_3->setGeometry(QRect(674, 368, 126, 63));
        Feld15_3->setMinimumSize(QSize(126, 63));
        Feld15_3->setMaximumSize(QSize(126, 63));
        Feld15_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        label_26 = new QLabel(Feld15_3);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 10, 61, 41));
        label_26->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_26->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_26->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label_26->setTextFormat(Qt::TextFormat::AutoText);
        label_26->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        Feld19_3 = new QWidget(Brettspiel_2);
        Feld19_3->setObjectName("Feld19_3");
        Feld19_3->setGeometry(QRect(674, 613, 126, 63));
        Feld19_3->setMinimumSize(QSize(126, 63));
        Feld19_3->setMaximumSize(QSize(126, 63));
        Feld19_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_55 = new QWidget(Feld19_3);
        widget_55->setObjectName("widget_55");
        widget_55->setGeometry(QRect(0, 0, 25, 63));
        widget_55->setMinimumSize(QSize(25, 63));
        widget_55->setMaximumSize(QSize(25, 63));
        widget_55->setBaseSize(QSize(63, 20));
        widget_55->setStyleSheet(QString::fromUtf8("background-color: #F7941D;"));
        Feld33_3 = new QWidget(Brettspiel_2);
        Feld33_3->setObjectName("Feld33_3");
        Feld33_3->setGeometry(QRect(0, 491, 126, 63));
        Feld33_3->setMinimumSize(QSize(126, 63));
        Feld33_3->setMaximumSize(QSize(126, 63));
        Feld33_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        label_27 = new QLabel(Feld33_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(70, 10, 45, 42));
        label_27->setMinimumSize(QSize(0, 42));
        label_27->setMaximumSize(QSize(45, 25));
        label_27->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"background-color: transparent;\n"
"\n"
""));
        label_27->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/lehren(2).png")));
        label_27->setScaledContents(true);
        label_28 = new QLabel(Feld33_3);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 20, 51, 31));
        label_28->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_28->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_28->setTextFormat(Qt::TextFormat::AutoText);
        label_28->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        Feld39_3 = new QWidget(Brettspiel_2);
        Feld39_3->setObjectName("Feld39_3");
        Feld39_3->setGeometry(QRect(0, 124, 126, 64));
        Feld39_3->setMinimumSize(QSize(126, 64));
        Feld39_3->setMaximumSize(QSize(126, 64));
        Feld39_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_56 = new QWidget(Feld39_3);
        widget_56->setObjectName("widget_56");
        widget_56->setGeometry(QRect(101, 0, 25, 64));
        widget_56->setMinimumSize(QSize(25, 64));
        widget_56->setMaximumSize(QSize(25, 64));
        widget_56->setBaseSize(QSize(64, 20));
        widget_56->setStyleSheet(QString::fromUtf8("background-color: #0064a8;"));
        Feld30_3 = new QWidget(Brettspiel_2);
        Feld30_3->setObjectName("Feld30_3");
        Feld30_3->setGeometry(QRect(0, 674, 126, 126));
        Feld30_3->setMinimumSize(QSize(126, 126));
        Feld30_3->setMaximumSize(QSize(126, 126));
        Feld30_3->setStyleSheet(QString::fromUtf8("background-color: lightgray;"));
        Feld32_3 = new QWidget(Brettspiel_2);
        Feld32_3->setObjectName("Feld32_3");
        Feld32_3->setGeometry(QRect(0, 552, 126, 63));
        Feld32_3->setMinimumSize(QSize(126, 63));
        Feld32_3->setMaximumSize(QSize(126, 63));
        Feld32_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_57 = new QWidget(Feld32_3);
        widget_57->setObjectName("widget_57");
        widget_57->setGeometry(QRect(101, 0, 25, 63));
        widget_57->setMinimumSize(QSize(25, 63));
        widget_57->setMaximumSize(QSize(25, 63));
        widget_57->setBaseSize(QSize(63, 20));
        widget_57->setStyleSheet(QString::fromUtf8("background-color: #1fb25a;"));
        Feld24_3 = new QWidget(Brettspiel_2);
        Feld24_3->setObjectName("Feld24_3");
        Feld24_3->setGeometry(QRect(429, 674, 63, 126));
        Feld24_3->setMinimumSize(QSize(63, 126));
        Feld24_3->setMaximumSize(QSize(63, 126));
        Feld24_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_58 = new QWidget(Feld24_3);
        widget_58->setObjectName("widget_58");
        widget_58->setGeometry(QRect(1, 0, 63, 25));
        widget_58->setMinimumSize(QSize(63, 25));
        widget_58->setMaximumSize(QSize(63, 25));
        widget_58->setBaseSize(QSize(63, 20));
        widget_58->setStyleSheet(QString::fromUtf8("background-color: #ED1B24;"));
        Feld1_3 = new QWidget(Brettspiel_2);
        Feld1_3->setObjectName("Feld1_3");
        Feld1_3->setGeometry(QRect(124, 0, 63, 126));
        Feld1_3->setMinimumSize(QSize(63, 126));
        Feld1_3->setMaximumSize(QSize(63, 126));
        Feld1_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_59 = new QWidget(Feld1_3);
        widget_59->setObjectName("widget_59");
        widget_59->setGeometry(QRect(0, 101, 63, 25));
        widget_59->setMinimumSize(QSize(63, 25));
        widget_59->setMaximumSize(QSize(63, 25));
        widget_59->setBaseSize(QSize(63, 20));
        widget_59->setStyleSheet(QString::fromUtf8("background-color: #955436;"));
        Feld31_3 = new QWidget(Brettspiel_2);
        Feld31_3->setObjectName("Feld31_3");
        Feld31_3->setGeometry(QRect(0, 613, 126, 63));
        Feld31_3->setMinimumSize(QSize(126, 63));
        Feld31_3->setMaximumSize(QSize(126, 63));
        Feld31_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_60 = new QWidget(Feld31_3);
        widget_60->setObjectName("widget_60");
        widget_60->setGeometry(QRect(101, 0, 25, 63));
        widget_60->setMinimumSize(QSize(25, 63));
        widget_60->setMaximumSize(QSize(25, 63));
        widget_60->setBaseSize(QSize(63, 20));
        widget_60->setStyleSheet(QString::fromUtf8("background-color: #1fb25a;"));
        Feld2_3 = new QWidget(Brettspiel_2);
        Feld2_3->setObjectName("Feld2_3");
        Feld2_3->setGeometry(QRect(185, 0, 63, 126));
        Feld2_3->setMinimumSize(QSize(63, 126));
        Feld2_3->setMaximumSize(QSize(63, 126));
        Feld2_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        label_29 = new QLabel(Feld2_3);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(8, 70, 45, 42));
        label_29->setMinimumSize(QSize(0, 42));
        label_29->setMaximumSize(QSize(45, 25));
        label_29->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"background-color: transparent;\n"
"\n"
""));
        label_29->setTextFormat(Qt::TextFormat::AutoText);
        label_29->setPixmap(QPixmap(QString::fromUtf8(":/Downloads/Unterricht")));
        label_29->setScaledContents(true);
        label_30 = new QLabel(Feld2_3);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(7, 10, 51, 31));
        label_30->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_30->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_30->setTextFormat(Qt::TextFormat::AutoText);
        label_30->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        Feld0_3 = new QWidget(Brettspiel_2);
        Feld0_3->setObjectName("Feld0_3");
        Feld0_3->setGeometry(QRect(0, 0, 126, 126));
        Feld0_3->setMinimumSize(QSize(126, 126));
        Feld0_3->setMaximumSize(QSize(126, 126));
        Feld0_3->setStyleSheet(QString::fromUtf8("background-color: lightgray;"));
        label_31 = new QLabel(Feld0_3);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 50, 111, 71));
        label_31->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"font-weight: 800;\n"
"font-size : 15px;"));
        Feld37_3 = new QWidget(Brettspiel_2);
        Feld37_3->setObjectName("Feld37_3");
        Feld37_3->setGeometry(QRect(0, 247, 126, 63));
        Feld37_3->setMinimumSize(QSize(126, 63));
        Feld37_3->setMaximumSize(QSize(126, 63));
        Feld37_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_61 = new QWidget(Feld37_3);
        widget_61->setObjectName("widget_61");
        widget_61->setGeometry(QRect(101, 0, 25, 63));
        widget_61->setMinimumSize(QSize(25, 63));
        widget_61->setMaximumSize(QSize(25, 63));
        widget_61->setBaseSize(QSize(63, 20));
        widget_61->setStyleSheet(QString::fromUtf8("background-color: #0064a8;"));
        Feld34_3 = new QWidget(Brettspiel_2);
        Feld34_3->setObjectName("Feld34_3");
        Feld34_3->setGeometry(QRect(0, 430, 126, 63));
        Feld34_3->setMinimumSize(QSize(126, 63));
        Feld34_3->setMaximumSize(QSize(126, 63));
        Feld34_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_62 = new QWidget(Feld34_3);
        widget_62->setObjectName("widget_62");
        widget_62->setGeometry(QRect(101, 0, 25, 63));
        widget_62->setMinimumSize(QSize(25, 63));
        widget_62->setMaximumSize(QSize(25, 63));
        widget_62->setBaseSize(QSize(63, 20));
        widget_62->setStyleSheet(QString::fromUtf8("background-color: #1fb25a;"));
        Feld22_3 = new QWidget(Brettspiel_2);
        Feld22_3->setObjectName("Feld22_3");
        Feld22_3->setGeometry(QRect(552, 674, 63, 126));
        Feld22_3->setMinimumSize(QSize(63, 126));
        Feld22_3->setMaximumSize(QSize(63, 126));
        Feld22_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        Feld21_3 = new QWidget(Brettspiel_2);
        Feld21_3->setObjectName("Feld21_3");
        Feld21_3->setGeometry(QRect(613, 674, 63, 126));
        Feld21_3->setMinimumSize(QSize(63, 126));
        Feld21_3->setMaximumSize(QSize(63, 126));
        Feld21_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_63 = new QWidget(Feld21_3);
        widget_63->setObjectName("widget_63");
        widget_63->setGeometry(QRect(0, 0, 63, 25));
        widget_63->setMinimumSize(QSize(63, 25));
        widget_63->setMaximumSize(QSize(63, 25));
        widget_63->setBaseSize(QSize(63, 20));
        widget_63->setStyleSheet(QString::fromUtf8("background-color: #ED1B24;"));
        Feld28_3 = new QWidget(Brettspiel_2);
        Feld28_3->setObjectName("Feld28_3");
        Feld28_3->setGeometry(QRect(185, 674, 63, 126));
        Feld28_3->setMinimumSize(QSize(63, 126));
        Feld28_3->setMaximumSize(QSize(63, 126));
        Feld28_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        label_34 = new QLabel(Feld28_3);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(12, 5, 41, 16));
        label_34->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_34->setStyleSheet(QString::fromUtf8("font-size:8px;\n"
"border: 0px solid black;"));
        label_34->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label_34->setTextFormat(Qt::TextFormat::AutoText);
        label_34->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        label_11 = new QLabel(Feld28_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(7, 44, 50, 51));
        label_11->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-image: url(:/new/images/images/rechter-pfeil.png);\n"
"background-color:transparent;"));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/toilet.png")));
        label_11->setScaledContents(true);
        Feld38_3 = new QWidget(Brettspiel_2);
        Feld38_3->setObjectName("Feld38_3");
        Feld38_3->setGeometry(QRect(0, 186, 126, 63));
        Feld38_3->setMinimumSize(QSize(126, 63));
        Feld38_3->setMaximumSize(QSize(126, 63));
        Feld38_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        Feld9_3 = new QWidget(Brettspiel_2);
        Feld9_3->setObjectName("Feld9_3");
        Feld9_3->setGeometry(QRect(613, 0, 63, 126));
        Feld9_3->setMinimumSize(QSize(63, 126));
        Feld9_3->setMaximumSize(QSize(63, 126));
        Feld9_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_64 = new QWidget(Feld9_3);
        widget_64->setObjectName("widget_64");
        widget_64->setGeometry(QRect(0, 101, 63, 25));
        widget_64->setMinimumSize(QSize(63, 25));
        widget_64->setMaximumSize(QSize(63, 25));
        widget_64->setBaseSize(QSize(63, 20));
        widget_64->setStyleSheet(QString::fromUtf8("background-color: #9AD9F5;"));
        Feld35_3 = new QWidget(Brettspiel_2);
        Feld35_3->setObjectName("Feld35_3");
        Feld35_3->setGeometry(QRect(0, 369, 126, 63));
        Feld35_3->setMinimumSize(QSize(126, 63));
        Feld35_3->setMaximumSize(QSize(126, 63));
        Feld35_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        Feld14_3 = new QWidget(Brettspiel_2);
        Feld14_3->setObjectName("Feld14_3");
        Feld14_3->setGeometry(QRect(674, 308, 126, 63));
        Feld14_3->setMinimumSize(QSize(126, 63));
        Feld14_3->setMaximumSize(QSize(126, 63));
        Feld14_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;"));
        widget_65 = new QWidget(Feld14_3);
        widget_65->setObjectName("widget_65");
        widget_65->setGeometry(QRect(0, 0, 25, 63));
        widget_65->setMinimumSize(QSize(25, 63));
        widget_65->setMaximumSize(QSize(25, 63));
        widget_65->setBaseSize(QSize(63, 20));
        widget_65->setStyleSheet(QString::fromUtf8("background-color: #D93A96;"));
        Feld3_3 = new QWidget(Brettspiel_2);
        Feld3_3->setObjectName("Feld3_3");
        Feld3_3->setGeometry(QRect(246, 0, 63, 126));
        Feld3_3->setMinimumSize(QSize(63, 126));
        Feld3_3->setMaximumSize(QSize(63, 126));
        Feld3_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_66 = new QWidget(Feld3_3);
        widget_66->setObjectName("widget_66");
        widget_66->setGeometry(QRect(0, 101, 63, 25));
        widget_66->setMinimumSize(QSize(63, 25));
        widget_66->setMaximumSize(QSize(63, 25));
        widget_66->setBaseSize(QSize(63, 20));
        widget_66->setStyleSheet(QString::fromUtf8("background-color: #955436;"));
        Feld20_3 = new QWidget(Brettspiel_2);
        Feld20_3->setObjectName("Feld20_3");
        Feld20_3->setGeometry(QRect(674, 674, 126, 126));
        Feld20_3->setMinimumSize(QSize(126, 126));
        Feld20_3->setMaximumSize(QSize(126, 126));
        Feld20_3->setStyleSheet(QString::fromUtf8("background-color: lightgray;"));
        Feld13_3 = new QWidget(Brettspiel_2);
        Feld13_3->setObjectName("Feld13_3");
        Feld13_3->setGeometry(QRect(674, 247, 126, 63));
        Feld13_3->setMinimumSize(QSize(126, 63));
        Feld13_3->setMaximumSize(QSize(126, 63));
        Feld13_3->setStyleSheet(QString::fromUtf8("background-color: lightblue;"));
        widget_67 = new QWidget(Feld13_3);
        widget_67->setObjectName("widget_67");
        widget_67->setGeometry(QRect(0, 0, 25, 63));
        widget_67->setMinimumSize(QSize(25, 63));
        widget_67->setMaximumSize(QSize(25, 63));
        widget_67->setBaseSize(QSize(63, 20));
        widget_67->setStyleSheet(QString::fromUtf8("background-color: #D93A96;"));
        wurfeln = new QPushButton(Brettspiel_2);
        wurfeln->setObjectName("wurfeln");
        wurfeln->setGeometry(QRect(370, 360, 71, 71));
        wurfeln->setStyleSheet(QString::fromUtf8("border-image: url(:/new/images/images/casino.png);\n"
"\n"
"border-color:transparent;\n"
"border-radius:10px;\n"
"font: 9pt \"Sans Serif\";"));
        label_4 = new QLabel(Brettspiel_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(674, 491, 51, 61));
        label_4->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/Unterricht")));
        label_4->setScaledContents(true);
        label_5 = new QLabel(Brettspiel_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(75, 492, 51, 61));
        label_5->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/lehren(1).png")));
        label_5->setScaledContents(true);
        label_10 = new QLabel(Brettspiel_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 10, 111, 71));
        label_10->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-image: url(:/new/images/images/rechter-pfeil.png);\n"
"background-color:transparent;"));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/rechter-pfeil.png")));
        label_10->setScaledContents(true);
        rollDiceButton = new QPushButton(Brettspiel_2);
        rollDiceButton->setObjectName("rollDiceButton");
        rollDiceButton->setGeometry(QRect(330, 440, 161, 51));
        rollDiceButton->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;"));
        diceResult = new QLabel(Brettspiel_2);
        diceResult->setObjectName("diceResult");
        diceResult->setGeometry(QRect(380, 340, 54, 17));
        Feld29_3->raise();
        Feld4_3->raise();
        Feld27_3->raise();
        Feld26_3->raise();
        Feld8_3->raise();
        Feld18_3->raise();
        Feld36_3->raise();
        Feld10_4->raise();
        Feld16_3->raise();
        Feld25_3->raise();
        Feld11_3->raise();
        Feld12_3->raise();
        Feld7_3->raise();
        Feld5_3->raise();
        Feld23_3->raise();
        Feld17_3->raise();
        Feld15_3->raise();
        Feld19_3->raise();
        Feld33_3->raise();
        Feld39_3->raise();
        Feld30_3->raise();
        Feld32_3->raise();
        Feld24_3->raise();
        Feld1_3->raise();
        Feld31_3->raise();
        Feld2_3->raise();
        Feld0_3->raise();
        Feld37_3->raise();
        Feld34_3->raise();
        Feld22_3->raise();
        Feld21_3->raise();
        Feld28_3->raise();
        Feld38_3->raise();
        Feld9_3->raise();
        Feld35_3->raise();
        Feld14_3->raise();
        Feld3_3->raise();
        Feld20_3->raise();
        Feld13_3->raise();
        wurfeln->raise();
        label_4->raise();
        label_5->raise();
        Feld6_3->raise();
        label_10->raise();
        rollDiceButton->raise();
        diceResult->raise();
        Spieleranzeige_3 = new QWidget(gameView);
        Spieleranzeige_3->setObjectName("Spieleranzeige_3");
        Spieleranzeige_3->setGeometry(QRect(1360, 30, 500, 250));
        Spieleranzeige_3->setMinimumSize(QSize(500, 250));
        Spieleranzeige_3->setMaximumSize(QSize(500, 250));
        Spieleranzeige_3->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;;\n"
""));
        Spieler_3 = new QWidget(Spieleranzeige_3);
        Spieler_3->setObjectName("Spieler_3");
        Spieler_3->setGeometry(QRect(30, 30, 441, 41));
        Spieler_3->setStyleSheet(QString::fromUtf8("background-color: #275EA8;\n"
"border-radius:10px;"));
        Spielerfarbe_7 = new QWidget(Spieler_3);
        Spielerfarbe_7->setObjectName("Spielerfarbe_7");
        Spielerfarbe_7->setGeometry(QRect(5, 6, 30, 30));
        Spielerfarbe_7->setStyleSheet(QString::fromUtf8("background-color: white;\n"
""));
        Geld_5 = new QLabel(Spieler_3);
        Geld_5->setObjectName("Geld_5");
        Geld_5->setGeometry(QRect(353, 10, 71, 20));
        Geld_5->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"font-weight: 800;\n"
"font-size : 15px;"));
        Geld_6 = new QLabel(Spieler_3);
        Geld_6->setObjectName("Geld_6");
        Geld_6->setGeometry(QRect(50, 9, 71, 20));
        Geld_6->setStyleSheet(QString::fromUtf8("border: 0px solid black;\n"
"font-weight: 800;\n"
"font-size : 20px;"));
        backButton = new QPushButton(gameView);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(1690, 320, 161, 31));
        backButton->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;"));
        buyButton = new QPushButton(gameView);
        buyButton->setObjectName("buyButton");
        buyButton->setGeometry(QRect(1690, 380, 161, 51));
        buyButton->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;"));
        readyButton = new QPushButton(gameView);
        readyButton->setObjectName("readyButton");
        readyButton->setGeometry(QRect(1690, 520, 161, 51));
        readyButton->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;"));
        buyProperty = new QPushButton(gameView);
        buyProperty->setObjectName("buyProperty");
        buyProperty->setGeometry(QRect(1690, 590, 161, 51));
        buyProperty->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;"));
        sellButton = new QPushButton(gameView);
        sellButton->setObjectName("sellButton");
        sellButton->setGeometry(QRect(1690, 450, 161, 51));
        sellButton->setStyleSheet(QString::fromUtf8("background-color:#252850;\n"
"border-radius:10px;\n"
"color:white;\n"
""));
        widget_3 = new QWidget(gameView);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(-10, -20, 1971, 1111));
        widget_3->setStyleSheet(QString::fromUtf8("background-image: url(:/new/images/images/Monopoly (11).png);"));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(970, 100, 51, 61));
        label_6->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/Unterricht")));
        label_6->setScaledContents(true);
        label_7 = new QLabel(widget_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(1060, 100, 51, 61));
        label_7->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/Unterricht")));
        label_7->setScaledContents(true);
        label_48 = new QLabel(widget_3);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(600, 110, 60, 51));
        label_48->setMinimumSize(QSize(0, 42));
        label_48->setMaximumSize(QSize(70, 70));
        label_48->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        label_48->setStyleSheet(QString::fromUtf8("border-color:transparent;\n"
"background-color:transparent;\n"
"\n"
""));
        label_48->setPixmap(QPixmap(QString::fromUtf8(":/new/images/images/lehren.png")));
        label_48->setScaledContents(true);
        stackedWidget->addWidget(gameView);
        widget_3->raise();
        Brettspiel_2->raise();
        Spieleranzeige_3->raise();
        backButton->raise();
        buyButton->raise();
        readyButton->raise();
        buyProperty->raise();
        sellButton->raise();
        Spieleraktivitaet_3->raise();
        csvView = new QWidget();
        csvView->setObjectName("csvView");
        stackedWidget->addWidget(csvView);
        startView = new QWidget();
        startView->setObjectName("startView");
        widget = new QWidget(startView);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(740, 60, 391, 531));
        widget->setStyleSheet(QString::fromUtf8("border-radius: 20px;\n"
"background-color:#252850;\n"
"border: 1px solid gray; \n"
"opacity: 0.5;\n"
""));
        player1 = new QPushButton(widget);
        player1->setObjectName("player1");
        player1->setGeometry(QRect(30, 180, 341, 41));
        player1->setStyleSheet(QString::fromUtf8("border-radius: 13px;\n"
"background-color:gray;\n"
"border-width:2px;\n"
"border-color:darkgray;\n"
"text-align: start;\n"
"\n"
""));
        player2 = new QPushButton(widget);
        player2->setObjectName("player2");
        player2->setGeometry(QRect(30, 230, 341, 41));
        player2->setStyleSheet(QString::fromUtf8("border-radius: 13px;\n"
"background-color:gray;\n"
"border-width:2px;\n"
"border-color:darkgray;\n"
"\n"
""));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 321, 51));
        label->setStyleSheet(QString::fromUtf8("color:white;\n"
"font: 38pt;\n"
"font-weight:bold;\n"
"text-align:center;\n"
"border-color:transparent;\n"
"\n"
""));
        player3 = new QPushButton(widget);
        player3->setObjectName("player3");
        player3->setGeometry(QRect(30, 280, 341, 41));
        player3->setStyleSheet(QString::fromUtf8("border-radius: 13px;\n"
"background-color:gray;\n"
"border-width:2px;\n"
"border-color:darkgray;\n"
"\n"
""));
        player4 = new QPushButton(widget);
        player4->setObjectName("player4");
        player4->setGeometry(QRect(30, 330, 341, 41));
        player4->setStyleSheet(QString::fromUtf8("border-radius: 13px;\n"
"background-color:gray;\n"
"border-width:2px;\n"
"border-color:darkgray;\n"
"\n"
""));
        addPlayer = new QPushButton(widget);
        addPlayer->setObjectName("addPlayer");
        addPlayer->setGeometry(QRect(330, 110, 41, 41));
        addPlayer->setStyleSheet(QString::fromUtf8("border-radius: 13px;\n"
"background-color:#469536;\n"
"border-width:2px;\n"
"border-color:transparent\n"
";\n"
"color:white;\n"
"padding-bottom:10px;\n"
"font: 25pt ;\n"
"font-weight:bold;\n"
"\n"
""));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 110, 281, 41));
        label_2->setStyleSheet(QString::fromUtf8("border-radius: 13px;\n"
"font: 12pt;\n"
"font-weight:bold;\n"
"background-color:gray;\n"
"border-width:2px;\n"
"border-color:darkgray;"));
        playerNameInput = new QLineEdit(widget);
        playerNameInput->setObjectName("playerNameInput");
        playerNameInput->setGeometry(QRect(90, 110, 211, 40));
        playerNameInput->setStyleSheet(QString::fromUtf8("color:black;\n"
"font: 13pt ;\n"
"background-color:transparent;\n"
"\n"
"border-color:transparent;"));
        startButton = new QPushButton(widget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(30, 420, 341, 51));
        startButton->setStyleSheet(QString::fromUtf8("border-radius: 20px;\n"
"background-color:#469536;\n"
"\n"
""));
        startLabel = new QLabel(startView);
        startLabel->setObjectName("startLabel");
        startLabel->setEnabled(true);
        startLabel->setGeometry(QRect(890, 490, 111, 31));
        startLabel->setAcceptDrops(false);
        startLabel->setStyleSheet(QString::fromUtf8("Background-color:transparent;\n"
"color:white;\n"
"text-size:18px;\n"
"font: 24pt \"Sans Serif\";\n"
"font-weight: bold;\n"
""));
        importCSVbutton = new QPushButton(startView);
        importCSVbutton->setObjectName("importCSVbutton");
        importCSVbutton->setGeometry(QRect(10, 780, 161, 51));
        importCSVbutton->setStyleSheet(QString::fromUtf8(""));
        ServerButton = new QPushButton(startView);
        ServerButton->setObjectName("ServerButton");
        ServerButton->setGeometry(QRect(1690, 780, 161, 51));
        ServerButton->setStyleSheet(QString::fromUtf8("border-width:3px;\n"
"border-color:black;\n"
""));
        widget_2 = new QWidget(startView);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(-50, 0, 2191, 1111));
        widget_2->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/new/images/images/Monopoly.png);"));
        stackedWidget->addWidget(startView);
        widget_2->raise();
        widget->raise();
        startLabel->raise();
        importCSVbutton->raise();
        ServerButton->raise();

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(tooltip)
        stackedWidget->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Monopoly</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        textEdit_3->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:15px; font-weight:800; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20px;\">Turner hat eine 5 gew\303\274rfelt.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        widget_46->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_47->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_48->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Feld26_3->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_49->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_50->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_51->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:7pt; font-weight:700;\">Berufsschule</span></p><p><br/></p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">Schulfrei</span></p><p><br/></p><p><span style=\" font-size:10pt; font-weight:700;\"><br/></span></p><p><span style=\" font-size:10pt; font-weight:700;\"><br/></span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        widget_52->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_20->setText(QString());
        label_21->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:7pt; font-weight:700;\">Unterricht</span></p></body></html>", nullptr));
        label_12->setText(QString());
        label_23->setText(QString());
        label_24->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:7pt; font-weight:700;\">Unterricht</span></p></body></html>", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "<html>\n"
"<head/>\n"
"<body>\n"
"<p style=\"line-height: 0.1;\">\n"
"    <span style=\"font-size:8pt;\">Erlanger</span>\n"
"</p>\n"
"<p style=\"line-height: 0.9;\">\n"
"    <span style=\"font-size:8pt;\">Bahnhof</span>\n"
"</p>\n"
"</body>\n"
"</html>", nullptr));
#if QT_CONFIG(tooltip)
        widget_53->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_54->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_26->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt;\">N\303\274rnberger </span></p><p><span style=\" font-size:8pt;\">Bahnhof</span></p><p><br/></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        widget_55->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_27->setText(QString());
        label_28->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:7pt; font-weight:700;\">Unterricht</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        widget_56->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_57->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_58->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_59->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_60->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_29->setText(QString());
        label_30->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:7pt; font-weight:700;\">Unterricht</span></p></body></html>", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:28pt; color:#000000;\">Start</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        widget_61->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_62->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_63->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_34->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt;\">Toilette</span></p><p><span style=\" font-size:9pt;\"><br/></span></p></body></html>", nullptr));
        label_11->setText(QString());
#if QT_CONFIG(tooltip)
        widget_64->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_65->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_66->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_67->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>background-color: #f0f0f0:</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        wurfeln->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_10->setText(QString());
        rollDiceButton->setText(QCoreApplication::translate("MainWindow", "W\303\274rfeln", nullptr));
        diceResult->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        Geld_5->setText(QCoreApplication::translate("MainWindow", "2000DNT", nullptr));
        Geld_6->setText(QCoreApplication::translate("MainWindow", "Turner", nullptr));
        backButton->setText(QCoreApplication::translate("MainWindow", "Einstellungen", nullptr));
        buyButton->setText(QCoreApplication::translate("MainWindow", "Kaufen", nullptr));
        readyButton->setText(QCoreApplication::translate("MainWindow", "Fertig", nullptr));
        buyProperty->setText(QCoreApplication::translate("MainWindow", "Haus kaufen", nullptr));
        sellButton->setText(QCoreApplication::translate("MainWindow", "Verkaufen", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        label_48->setText(QString());
#if QT_CONFIG(tooltip)
        player1->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        player1->setText(QCoreApplication::translate("MainWindow", "Spieler 1", nullptr));
        player2->setText(QCoreApplication::translate("MainWindow", "Spieler 2", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "MONOPOLY", nullptr));
        player3->setText(QCoreApplication::translate("MainWindow", "Spieler 2", nullptr));
        player4->setText(QCoreApplication::translate("MainWindow", "Spieler 2", nullptr));
        addPlayer->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Name:", nullptr));
        playerNameInput->setText(QCoreApplication::translate("MainWindow", "PeterPan", nullptr));
        startButton->setText(QString());
#if QT_CONFIG(tooltip)
        startLabel->setToolTip(QCoreApplication::translate("MainWindow", "label->setAttribute(Qt::WA_TransparentForMouseEvents);", nullptr));
#endif // QT_CONFIG(tooltip)
        startLabel->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        importCSVbutton->setText(QCoreApplication::translate("MainWindow", "CSV Importieren", nullptr));
        ServerButton->setText(QCoreApplication::translate("MainWindow", "Erneut verbinden", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
