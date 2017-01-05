#include <cstdlib>
#include "Passenger.h"

Passenger::Passenger(int x, int y, int x2, int y2)
        : source(new Point (x,y)), destination(new Point (x2,y2)) {}

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
    delete(source);
    delete(destination);
}

