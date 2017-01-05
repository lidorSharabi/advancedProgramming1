//
// Created by lsharabi on 02/12/16.
//

#include "Trip.h"
#include "Point.h"


Trip::Trip(int id, int start_x, int start_y, int end_x, int end_y,
           int numOfPassengers, double tarrif, int startingTime) :
        id(id), numOfPassengers(numOfPassengers),
        tarrif(tarrif), startingTime(startingTime) {
    start = new Point(start_x, start_y);
    end = new Point(end_x, end_y);
    sent = false;
}

Trip::Trip(GridItem *start, GridItem *end , int id) :
        id(id), start(start), end(end) {
    sent = false;
}

void Trip::updateMetersPassed(int m) {
    totalMetersPassed += m;
}

int Trip::getId() {
    return id;
}

int Trip::getTotalMetersPassed() {
    return totalMetersPassed;
}

GridItem* Trip::getStart() {
    return start;
}

GridItem*Trip::getEnd() {
    return end;
}

int Trip::getNumOfPassengers() {
    return numOfPassengers;
}

double Trip::getTarrif() {
    return tarrif;
}

void Trip::setTariff(int tariff) {
    this->tarrif = tariff;
}

bool Trip::isSent() const {
    return sent;
}

void Trip::setSent(bool sent) {
    Trip::sent = sent;
}

void Trip::setPointsPath(vector<GridItem*> path) {
    this->pointsPath = path;
}

std::ostream &operator<<(std::ostream &os, const Trip &trip) {
    os << "id: " << trip.id << std::endl <<
       "totalMetersPassed: " << trip.totalMetersPassed << std::endl <<
       "start: "; (trip.start)->printGridItem();
       "end: " ; (trip.end)->printGridItem() ;
       os << "numOfPassengers: " << trip.numOfPassengers << std::endl <<
       "tarrif: " << trip.tarrif << std::endl <<
       "sent : " << trip.sent << std::endl <<
        "starting time: " << trip.startingTime;
    return os;
}

int Trip::getStartingTime() {
    return startingTime;
}

vector<GridItem *> &Trip::getPointsPath() {
    return pointsPath;
}

Trip::~Trip() {
    delete(start);
    delete(end);
}

/*
void printPointsPath(){
    std::list<Driver *>::const_iterator driverIter;
    //set all the drivers to be available for others trips
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter) {
        if (!(*driverIter)->isAvailbale()) {
            (*driverIter)->setAvailbale(true);
        }
    }
}
*/

