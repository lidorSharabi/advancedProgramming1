//
// Created by lsharabi on 02/12/16.
//

#ifndef MYPROJECTNAME_TAXICENTER_H
#define MYPROJECTNAME_TAXICENTER_H

#include "Driver.h"
#include "Point.h"
#include "Clock.h"
#include "connection/Udp.h"
#include "connection/Tcp.h"

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

    void bindTripsToDrivers();

public:
    void requestForDriverLocation(int driverId);

    TaxiCenter(Map *map);

    list<StandardCab *> getCabs();

    list<Trip *> getTrips();

    StandardCab callAndSendCab(Passenger g);

    void addDriver(Driver *driver);

    void addCab(StandardCab *cab);

    void addTrip(Trip *t);

    void startAllDriving();

    list<Driver *> getDrivers();

    void freeAllocatedMemory();

    Map *getMap();

    int increaseClock();

    void bindCabsToDrivers();

};


#endif //MYPROJECTNAME_TAXICENTER_H
