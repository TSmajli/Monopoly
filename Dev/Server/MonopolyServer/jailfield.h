#pragma once
#include "field.h"

class JailField : public Field {
public:
    void onLand(Player& player) override;
};
