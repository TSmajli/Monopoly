#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QJsonObject>
#include <QMap>
#include <QVector>
#include <QColor>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class NetworkClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    NetworkClient *network;
    int myPlayerId = -1;
    int pendingBuyFieldIndex = -1;
    int pendingBuyPlayerId = -1;
    int pendingEndTurnPlayerId = -1;
    bool gameStarted = false;
    bool gameFinished = false;
    int winnerId = -1;
    int currentPlayerId = -1;
    QString currentFieldName;
    int currentFieldIndex = -1;
    QMap<int, QString> playerNames;
    QMap<int, int> playerPositions;
    QMap<int, QJsonObject> fieldInfoByIndex;
    QVector<QWidget *> boardFields;
    QMap<QWidget *, QString> fieldBaseStyles;
    bool localReady = false;
    QMap<int, QLabel *> playerTokens;
    QMap<int, QColor> playerColors;
    QJsonObject lastStateSnapshot;
    QMap<int, QLabel *> houseMarkers;
    bool suppressWinViewOnce = false;
    bool logViewActive = false;

    struct LogEntry {
        QDateTime timestamp;
        QString playerName;
        QString message;
    };
    QVector<LogEntry> logEntries;

    void appendLog(const QString &message, const QString &playerName);
    void refreshLogView();
    void saveLogToCsv(const QString &filePath);
    void loadLogFromCsv(const QString &filePath);
    QString resolvePlayerName(int playerId) const;
    void updateBoardHighlights();
    void updateFieldInfo(int index);
    void updatePlayerTokens();
    void updateHouseBuyAvailability();
    void updateHouseMarkers();
    void setConnectionStatus(const QString &text, const QString &color);
    void setAwaitingBuyDecision(bool awaiting);
    void setAwaitingEndTurn(bool awaiting);
    void ensureDiceEnabled(bool enabled);

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
