//
// Created by lsharabi on 02/12/16.
//

#ifndef MYPROJECTNAME_TAXICENTER_H
#define MYPROJECTNAME_TAXICENTER_H

#include "Driver.h"
#include "Point.h"
#include "Clock.h"
#include "Udp.h"

class TaxiCenter {
private:

    std::list<Driver *> drivers;
    std::list<StandardCab *> cabs;
    std::list<Trip *> trips;
    Map *map;
    Clock clock;
private:
    void freeDrivers();

    void freeCabs();

    void freeTrips();

    void freeUnnecessaryTrips();

    void bindTripsToDrivers(Udp* udp);

public:
    void findDriverLocation(int driverId);

    TaxiCenter(Map *map);

    list<StandardCab *> getCabs();

    list<Trip *> getTrips();

    StandardCab callAndSendCab(Passenger g);

    void addDriver(Driver *driver);

    void addCab(StandardCab *cab);

    void addTrip(Trip *t);

    void startAllDriving(Udp* udp);

    void freeAllocatedMemory();

    Map *getMap();

    int increaseClock();

    void bindCabsToDrivers(Udp *udp);
};


#endif //MYPROJECTNAME_TAXICENTER_H
