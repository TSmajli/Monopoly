#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;



private slots:
    void
    on_startButton_clicked();
    void
    on_backButton_clicked();
    void
    on_buyButton_clicked();
    void
     on_sellButton_clicked();
    void
    on_addPlayer_clicked();
    void
    on_rollDiceButton_clicked();
};
#endif // MAINWINDOW_H

