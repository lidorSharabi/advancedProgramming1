#include "BfsCouple.h"

BfsCouple::BfsCouple(GridItem* son, BfsCouple* parent) {
    this->gridItem = son;
    this->bfsCouple = parent;
}

BfsCouple* BfsCouple::getBfsCouple() {
    return this->bfsCouple;
}

GridItem* BfsCouple::getGridItem() {
    return this->gridItem;
}

BfsCouple::~BfsCouple() {
}