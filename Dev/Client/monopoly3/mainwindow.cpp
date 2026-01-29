#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->startButton->setText("Spiel Starten");

     ui->startLabel->setAttribute(Qt::WA_TransparentForMouseEvents);


     ui->ServerButton->setStyleSheet(
         "QPushButton {"
             "background-color:#252850;"
             "border-radius:10px;"
              "color:white;"
        "}"
        "QPushButton:hover {"
        "  background-color: #191970;"
        "}"
        );

     ui->importCSVbutton->setStyleSheet(
         "QPushButton {"
         "background-color:#252850;"
         "border-radius:10px;"
         "color:white;"
         "border-width:2px;"
         "border-color:black;"
         "}"

         "QPushButton:hover {"
         "  background-color: #191970;"
         "}"
         );

    ui->addPlayer->setStyleSheet(
        "QPushButton {"
             "border-radius: 13px;"
        "background-color:#469536;"
         "border-width:2px;"
        " border-color:transparent;"
         "color:white;"
        " font: 25pt ;"
        " font-weight:bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #38772B;"
        "}"
        );

     ui->startButton->setStyleSheet(
        "QPushButton:hover {"
        "  background-color: #38772B;"
        "}"
        "QPushButton {"
        "border-radius: 20px;"
        "background-color:#469536;"
        "}"
        );

        ui->rollDiceButton->setStyleSheet(
            "QPushButton:hover {"
            "  background-color: #38772B;"
            "}"
            "QPushButton {"
            "border-radius: 20px;"
            "background-color:#469536;"
            "}"
        );


}
MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_startButton_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->gameView);
}
void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startView);
}

void MainWindow::on_buyButton_clicked()
{
  ui->Feld1_3->setStyleSheet("background-color: #00cc44;");
}
void MainWindow::on_sellButton_clicked()
{
    ui->Feld1_3->setStyleSheet("background-color: #275EA8;");
}
void MainWindow::on_addPlayer_clicked()
{
    QString name = ui->playerNameInput->text();

    if (name.isEmpty())
    {
        ui->player1->setText("Spieler 1");
    }
    else
    {
        ui->player1->setText(name);
    }
}
void MainWindow::on_rollDiceButton_clicked()
{
    ui->diceResult->setText("420");
}

