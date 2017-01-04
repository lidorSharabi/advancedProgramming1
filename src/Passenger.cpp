#include <cstdlib>
#include "Passenger.h"

Passenger::Passenger(Point *source, Point *destination)
        : source(source), destination(destination) {}

Point *Passenger::getSource() {
    return source;
}

Point *Passenger::getDestination() {
    return destination;
}

int Passenger::rankDriver() {
    return rand() % 5 + 1;
    }

Passenger::~Passenger() {
}

