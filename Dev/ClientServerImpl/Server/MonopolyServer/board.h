#pragma once
#include <QVector>
#include "field.h"

class Board {
public:
    QVector<Field*> fields;
    Field* getField(int index) const;
    int size() const;
};
