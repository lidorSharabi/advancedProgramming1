#include "TaxiCenter.h"
#include "Map.h"

TaxiCenter::TaxiCenter(Map *map) : map(map) {}

StandardCab TaxiCenter::callAndSendCab(Passenger g) {
    return StandardCab(0, Manufacturer::TESLA, Color::RED, 1);
}

void TaxiCenter::addDriver(Driver *driver) {
    drivers.push_back(driver);
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

void TaxiCenter::findDriverLocation(int driverId) {
    std::list<Driver *>::const_iterator iter;
    for (iter = drivers.begin(); iter != drivers.end(); ++iter) {
        if (driverId == (*iter)->getId()) {
            (*iter)->getCurrentLocation()->printGridItem();
            break;
        }
    }
}

void TaxiCenter::startAllDriving(Udp* udp) {
    //send trips to drivers
    bindTripsToDrivers(udp);
    //move drivers who have trip
    std::list<Driver *>::const_iterator driverIter;
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter)
    {
        if (!((*driverIter)->isAvailbale())
            && (*driverIter)->getTrip()->getStartingTime() < clock.getCurrentTime())
        {
            (*driverIter)->driveOneStep(map);
            //sending client message to move his driver
            udp->sendData("move driver", 11);
        }
    }
}

void TaxiCenter::bindTripsToDrivers(Udp* udp) {
    char buffer[1024];
    //create iterators for trips and drivers lists
    std::list<Trip *>::const_iterator tripIter;
    std::list<Driver *>::const_iterator driverIter;
    //for each trip look for suitable driver (same start locations)
    for (tripIter = trips.begin(); tripIter != trips.end(); ++tripIter) {
        for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter){
            if (!(*tripIter)->isSent()
                && (*tripIter)->getStartingTime() == clock.getCurrentTime()
                && *((*tripIter)->getStart()) == *((*driverIter)->getCurrentLocation())
                && (*driverIter)->isAvailbale())
            {
                //set the driver to be taken
                (*driverIter)->setAvailbale(false);
                (*tripIter)->setSent(true);
                (*tripIter)->getPointsPath().pop_back();
                (*driverIter)->addNumOfPassengers((*tripIter)->getNumOfPassengers());
                (*driverIter)->setTrip(*tripIter);
                udp->sendData("add trip", 9);
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << ((*tripIter));
                s.flush();
                udp->sendData(serial_str, serial_str.size());

                /*std::string serial_str1;
                boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                boost::archive::binary_oarchive oa1(s1);
                oa1 << (*tripIter)->getPointsPath();
                s1.flush();
                udp->sendData(serial_str1, serial_str1.size());
                */break;
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


void TaxiCenter::bindCabsToDrivers(Udp* udp) {
    std::list<Driver *>::const_iterator driverIter;
    std::list<StandardCab *>::const_iterator cabsIter;
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter) {
        for (cabsIter = cabs.begin(); cabsIter != cabs.end();){
            (*driverIter)->addCab(*cabsIter);
            //sending client operation string, to add/bind new cab to the driver
            udp->sendData("add new cab", 12);
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << ((*cabsIter));
            s.flush();

            udp->sendData(serial_str, serial_str.size());
            ++cabsIter;
            break;
        }

    }
}

