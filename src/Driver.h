#ifndef MYPROJECTNAME_DRIVER_H
#define MYPROJECTNAME_DRIVER_H

#include "MartialStatus.h"
#include "StandardCab.h"
#include "Trip.h"
#include "Passenger.h"
#include "Point.h"
#include "GridItem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
//#include <boost/serialization/list.hpp>

using namespace boost::archive;

class Map;

class Driver {
private:
    int id;
    int age;
    MartialStatus martialStatus;
    int seniority;
    int numOfPassengers;
    int sumOfSatisfaction;
    StandardCab *cab;
    std::list<Passenger *> passengersl;
    int cabId;
    GridItem *currentLocation;
    bool availbale;
    Trip *trip;

public:

    list<int> operations;

    Trip *getTrip();

    void setTrip(Trip *trip);

private:

    friend class boost::serialization::access;

    //serialization Point x, y members
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & age;
        ar & martialStatus;
        ar & seniority;
        ar & numOfPassengers;
        ar & sumOfSatisfaction;
        //ar & cab;
        //ar & passengersl;
        ar & cabId;
        ar & currentLocation;
        ar & availbale;
    }

    void freePassengers();

public:
    Driver(int id, int age, MartialStatus martialStatus, int seniority, int cabId);

    Driver() : id(0), age(0), martialStatus(SINGLE), seniority(0), cabId(0), cab(NULL) {}

    ~Driver();

    GridItem* getCurrentLocation();

    void setCurrentLocation(GridItem* gridItem);

    void updateRankDriver(int rank);

    int getId();

    int getAge();

    MartialStatus getMartialStatus();

    int getSeniority();

    double getSatisfaction();

    int getNumOfPassengers();

    StandardCab *getCab();

    list<Passenger *> getPassengersList();

    void bindCabToDriver(StandardCab *cab);

    void addNewPassenger(Passenger *passenger);

    void removePassenger(Passenger *passenger);

    void driveOneStep(Map *map);

    bool isAvailbale() const;

    void setCabId(int cabId);

    void setAvailbale(bool availbale);

    void addNumOfPassengers(int num);

    //overload the operator << to print a cab
    friend std::ostream &operator<<(std::ostream &os, const Driver &driver);
};


#endif //MYPROJECTNAME_DRIVER_H
