#include "taxfield.h"
#include "player.h"

void TaxField::onLand(Player& player) {
    player.pay(taxAmount);
}
