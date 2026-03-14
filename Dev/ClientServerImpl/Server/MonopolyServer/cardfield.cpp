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
        {"Zu spaet zum Unterricht!  Zahle 30$",  -30},
        {"Hausaufgaben gemacht!  Erhalte 20$",    20},
        {"Test bestanden!  Erhalte 50$",           50},
        {"Im Unterricht geschlafen!  Zahle 40$",  -40},
        {"Handy im Unterricht erwischt!  Zahle 25$", -25},
        {"Frueher Schulschluss!  Erhalte 30$",     30},
        {"Fehler im Code gefunden!  Erhalte 40$",  40},
        {"Hausaufgaben vergessen!  Zahle 20$",     -20},
        {"Vorzeigeschueler des Monats!  Erhalte 60$", 60},
        {"Schule geschwanzt!  Zahle 50$",          -50},
        {"Klassensprecher gewaehlt!  Erhalte 35$",   35},
        {"Nachsitzen!  Zahle 15$",                 -15},
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
