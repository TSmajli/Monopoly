#include "board.h"

Field* Board::getField(int index) const {
    return fields[index];
}

int Board::size() const {
    return fields.size();
}
