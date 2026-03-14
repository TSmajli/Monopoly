#include "cardfield.h"
#include "player.h"
#include <QRandomGenerator>
#include <QVector>

void CardField::onLand(Player& player) {
    struct Card {
        QString message;
        int amount; // positiv = erhalten, negativ = zahlen
    };

    static const QVector<Card> cards = {
        {"Zu spaet zum Unterricht!  Zahle 50$",  -50},
        {"Hausaufgaben gemacht!  Erhalte 40$",    40},
        {"Test bestanden!  Erhalte 80$",           80},
        {"Im Unterricht geschlafen!  Zahle 60$",  -60},
        {"Handy im Unterricht erwischt!  Zahle 40$", -40},
        {"Frueher Schulschluss!  Erhalte 50$",     50},
        {"Fehler im Code gefunden!  Erhalte 70$",  70},
        {"Hausaufgaben vergessen!  Zahle 35$",     -35},
        {"Vorzeigeschueler des Monats!  Erhalte 100$", 100},
        {"Schule geschwanzt!  Zahle 80$",          -80},
        {"Klassensprecher gewaehlt!  Erhalte 60$",   60},
        {"Nachsitzen!  Zahle 30$",                 -30},
    };

    const int idx = static_cast<int>(QRandomGenerator::global()->bounded(static_cast<quint32>(cards.size())));
    const Card &card = cards[idx];

    if (card.amount > 0) {
        player.receive(card.amount);
    } else if (card.amount < 0) {
        player.pay(-card.amount);
    }

    lastCardMessage = QString("[Unterrichtskarte] %1").arg(card.message);
}


