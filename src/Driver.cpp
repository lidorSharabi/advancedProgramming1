#include "Driver.h"
#include "Map.h"

int Driver::getId() {
    return id;
}

int Driver::getAge() {
    return age;
}

MartialStatus Driver::getMartialStatus() {
    return martialStatus;
}

int Driver::getSeniority() {
    return seniority;
}

double Driver::getSatisfaction() {
    if (numOfPassengers != 0)
        return sumOfSatisfaction/numOfPassengers;
    return 0;
}

int Driver::getNumOfPassengers() {
    return numOfPassengers;
}

StandardCab* Driver::getCab() {
    return this->cab;
}

list<Passenger*> Driver::getPassengersList() {
    return passengersl;
}

void Driver::updateRankDriver(int rank) {
    this->sumOfSatisfaction += rank;
}

void Driver::addCab(StandardCab *cab) {
    this->cab = cab;
}

void Driver::addNewPassenger(Passenger *passenger) {
    this->passengersl.push_back(passenger);
    this->numOfPassengers++;
}

void Driver::removePassenger(Passenger *passenger) {
    this->passengersl.remove(passenger);
    this->numOfPassengers--;
}

Driver::Driver(int id, int age, MartialStatus martialStatus, int seniority, int cabId)
        : id(id), age(age),
          martialStatus(martialStatus),
          seniority(seniority),
          cabId(cabId) {
    //as default set values to 0
    numOfPassengers = sumOfSatisfaction = 0;
    currentLocation = new Point (0,0);
    availbale = true;
}

GridItem* Driver::getCurrentLocation() {
    return currentLocation;
}

void Driver::driveOneStep(Map* map) {
    for (int i = 0; i < cab->getSpeed(); i++) {
        //assuming trip exist
        if (!(trip->getPointsPath().empty())){
            if (map != NULL) {
                map->updateDriverLocation(this, currentLocation);
            }
            else
            {
                //means that the sever is responsibale to delete the grid item
                currentLocation->deleteGridItem();
            }
            currentLocation = trip->getPointsPath().back();
            trip->getPointsPath().pop_back();
        }
    }
    if (trip->getPointsPath().empty()){
        availbale = true;
    }
}

bool Driver::isAvailbale() const {
    return availbale;
}

void Driver::setAvailbale(bool availbale) {
    Driver::availbale = availbale;
}

Driver::~Driver() {
    freePassengers();
}

void Driver::freePassengers() {
    while (!passengersl.empty()){
        delete(passengersl.front());
        passengersl.pop_front();
    }
}

void Driver::addNumOfPassengers(int num) {
    numOfPassengers += num;
}

std::ostream &operator<<(std::ostream &os, const Driver &driver) {
    os << "id: " << driver.id << std::endl <<
       "age: " << driver.age << std::endl <<
       "martialStatus: " << driver.martialStatus << std::endl <<
       "seniority: " << driver.seniority << std::endl <<
       "numOfPassengers: " << driver.numOfPassengers <<std::endl <<
       "sumOfSatisfaction: " << driver.sumOfSatisfaction << std::endl <<
       "currentLocation: " ;
        (driver.currentLocation)->printGridItem();
       os << "availbale : " << driver.availbale ;
    if (driver.cab != NULL) os <<std::endl << "driver cab : " << *(driver.cab);
    return os;
}

Trip *Driver::getTrip() {
    return trip;
}

void Driver::setTrip(Trip *trip) {
    Driver::trip = trip;
}

void Driver::setCurrentLocation(GridItem *gridItem) {
    currentLocation = gridItem;
}

void Driver::setCabId(int cabId) {
    Driver::cabId = cabId;
}
