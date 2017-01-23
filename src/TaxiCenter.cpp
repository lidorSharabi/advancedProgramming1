#include "TaxiCenter.h"
#include "Map.h"
#include "../easylogging++.h"

TaxiCenter::TaxiCenter(Map *map) : map(map) {}

StandardCab TaxiCenter::callAndSendCab(Passenger g) {
    return StandardCab(0, Manufacturer::TESLA, Color::RED, 1);
}

void TaxiCenter::addDriver(Driver *driver) {
    drivers.push_back(driver);
    //update map to contian the location of the new driver
    map->updateDriverLocation(driver, driver->getCurrentLocation());
}

void TaxiCenter::addCab(StandardCab *cab) {
    cabs.push_back(cab);
}

void TaxiCenter::addTrip(Trip *t) {
    trips.push_back(t);
}

list<StandardCab *> TaxiCenter::getCabs() {
    return cabs;
}

list<Trip *> TaxiCenter::getTrips() {
    return trips;
}

void TaxiCenter::requestForDriverLocation(int driverId) {
    std::list<Driver *>::const_iterator iter;
    for (iter = drivers.begin(); iter != drivers.end(); ++iter) {
        if (driverId == (*iter)->getId()) {
            //push the  driver operations list "4" which print his location
            (*iter)->operations.push_back(4);
            break;
        }
    }
}

void TaxiCenter::startAllDriving() {
    //send trips to drivers
    bindTripsToDrivers();
    //move drivers who have trip
    std::list<Driver *>::const_iterator driverIter;
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter)
    {
        if (!((*driverIter)->isAvailbale())
            && (*driverIter)->getTrip()->getStartingTime() < clock.getCurrentTime())
        {
            //add client operation 9 to move one step
            (*driverIter)->operations.push_back(9);
        }
    }
}

void TaxiCenter::bindTripsToDrivers() {
    //create iterators for trips and drivers lists
    std::list<Trip *>::const_iterator tripIter;
    std::list<Driver *>::const_iterator driverIter;
    //for each trip look for suitable driver (same start locations)
    for (tripIter = trips.begin(); tripIter != trips.end(); ++tripIter) {
        Point *start = (Point*)(*tripIter)->getStart();
        std::list<Driver *> driversAt = map->getDriverAt(*start);
        for (driverIter = driversAt.begin(); driverIter != driversAt.end(); ++driverIter){
            if (!(*tripIter)->isSent()
                && (*tripIter)->getStartingTime() == clock.getCurrentTime()
                && *((*tripIter)->getStart()) == *((*driverIter)->getCurrentLocation())
                && (*driverIter)->isAvailbale())
            {
                //set the driver to be taken
                (*driverIter)->setAvailbale(false);
                (*tripIter)->setSent(true);
                (*driverIter)->addNumOfPassengers((*tripIter)->getNumOfPassengers());
                (*driverIter)->setTrip(*tripIter);
                //add client operation 5 to calculate his trip path
                (*driverIter)->operations.push_back(5);
                break;
            }
        }
    }
}

void TaxiCenter::freeUnnecessaryTrips() {
    std::list<Trip *>::const_iterator tripIter;
    //delete all the trips that were send
    for (tripIter = trips.begin(); tripIter != trips.end();) {
        if ((*tripIter)->isSent()){
            Trip* temp = *tripIter;
            delete(temp);
            tripIter = trips.erase(tripIter);
        }
        else ++tripIter;
    }
}

void TaxiCenter::freeAllocatedMemory() {
    freeDrivers();
    freeCabs();
    freeTrips();
    delete(map);
}

void TaxiCenter::freeDrivers() {
    while (!drivers.empty()){
        delete(drivers.front());
        drivers.pop_front();
    }
}

void TaxiCenter::freeCabs() {
    while (!cabs.empty()){
        delete(cabs.front());
        cabs.pop_front();
    }
}

void TaxiCenter::freeTrips() {
    while (!trips.empty()){
        delete(trips.front());
        trips.pop_front();
    }
}

Map *TaxiCenter::getMap() {
    return map;
}

int TaxiCenter::increaseClock() {
    return clock.move();
}


void TaxiCenter::bindCabsToDrivers() {
    std::list<Driver *>::const_iterator driverIter;
    std::list<StandardCab *>::const_iterator cabsIter;
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter) {
        for (cabsIter = cabs.begin(); cabsIter != cabs.end();){
            (*driverIter)->bindCabToDriver(*cabsIter);
            //sending client operation string, to add/bind new cab to the driver
            //lido tcp->sendData("add new cab", 12);
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << ((*cabsIter));
            s.flush();

            //lidor tcp->sendData(serial_str, serial_str.size());
            ++cabsIter;
            break;
        }

    }
}

list<Driver *> TaxiCenter::getDrivers() {
    return drivers;
}

