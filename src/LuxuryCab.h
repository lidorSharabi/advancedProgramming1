//
// Created by lsharabi on 02/12/16.
//

#ifndef MYPROJECTNAME_LUXURYCAB_H
#define MYPROJECTNAME_LUXURYCAB_H

#include "StandardCab.h"
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
#include <boost/serialization/stack.hpp>
#include <boost/serialization/export.hpp>

using namespace boost::archive;

class LuxuryCab{
private:

    /*friend class boost::serialization::access;

    //serialization LuxuryCab members
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<StandardCab>(*this);
    }*/
public:
    LuxuryCab(int cabId, Manufacturer carManufacturer, Color color, int cabType);

    LuxuryCab(){}

    virtual void updateMeters();
};


#endif //MYPROJECTNAME_LUXURYCAB_H
