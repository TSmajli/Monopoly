#pragma once
#include "field.h"

class TaxField : public Field {
public:
    int taxAmount;

    void onLand(Player& player) override;
};
