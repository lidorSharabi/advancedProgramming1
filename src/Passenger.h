//
// Created by lsharabi on 02/12/16.
//

#ifndef MYPROJECTNAME_PASSENGER_H
#define MYPROJECTNAME_PASSENGER_H

#include "Point.h"

class Passenger {
private:
    Point* source;
    Point* destination;

public:
    Passenger(int x, int y, int x2, int y2);
    int rankDriver();
    Point* getSource();
    Point* getDestination();
    virtual ~Passenger();
};


#endif //MYPROJECTNAME_PASSENGER_H
