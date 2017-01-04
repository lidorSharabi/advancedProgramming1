#ifndef MYPROJECTNAME_STANDARTCAB_H
#define MYPROJECTNAME_STANDARTCAB_H

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

using namespace boost::archive;

class StandardCab {

protected:
    int cabId;
    int sumOfMeters;
    Manufacturer carManufacturer;
    Color color;
    int speed;
    int tariffCoefficient;

    friend class boost::serialization::access;

    //serialization Standardcab members
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & cabId;
        ar & sumOfMeters;
        ar & carManufacturer;
        ar & color;
        ar & speed;
        ar & tariffCoefficient;
    }

public:

    StandardCab(int cabId, Manufacturer carManufacturer, Color color, int cabType);

    StandardCab():cabId(1), carManufacturer(Manufacturer::FIAT), color(Color::RED),
                   speed(1){}

    virtual ~StandardCab();

    int getCabId();

    int getSumOfMeters();

    Manufacturer getCarManufacturer();

    Color getColor();

    int getSpeed();

    double getTarrif(int tariff);

    virtual void updateMeters();

    //overload the operator << to print a cab
    friend std::ostream &operator<<(std::ostream &os, const StandardCab &standardCab);
};

#endif //MYPROJECTNAME_STANDARTCAB_H
