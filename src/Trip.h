//
// Created by lsharabi on 02/12/16.
//

#ifndef MYPROJECTNAME_TRIP_H
#define MYPROJECTNAME_TRIP_H

#include "Point.h"
#include "Manufacturer.h"
#include "Color.h"
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
#include <boost/serialization/vector.hpp>

using namespace boost::archive;

class Trip {
private:
    int id;
    int totalMetersPassed;
    GridItem *start;
    GridItem *end;
    int numOfPassengers;
    double tarrif;
    bool sent;
    int startingTime;
    vector<GridItem*> pointsPath;

private:
    friend class boost::serialization::access;

    //serialization Standardcab members
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & totalMetersPassed;
        ar & start;
        ar & end;
        ar & numOfPassengers;
        ar & tarrif;
        ar & sent;
        ar & startingTime;
        ar & pointsPath;
    }

public:
    bool isSent() const;
    void setSent(bool sent);

public:

    Trip(int id, int start_x, int start_y, int end_x, int end_y,
         int numOfPassengers, double tarrif, int startingTime);
    Trip(GridItem *start, GridItem *end , int id= 0);

    Trip(): id(0){}
    int getId();

    int getTotalMetersPassed();


    GridItem *getStart();

    GridItem *getEnd();

    int getNumOfPassengers();

    double getTarrif();

    void updateMetersPassed(int m = 1);

    int getStartingTime();

    void setTariff(int tariff);

    vector<GridItem*> &getPointsPath();

    void setPointsPath(vector<GridItem*> path);

    //overload the operator << to print a trip
    friend std::ostream &operator<<(std::ostream &os, const Trip &trip);
};

#endif //MYPROJECTNAME_TRIP_H
