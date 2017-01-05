#ifndef MYPROJECTNAME_GRIDITEM_H
#define MYPROJECTNAME_GRIDITEM_H
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
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/serialization.hpp>

using namespace std;
/*
 * an abstract class (interface) of an item on a grid with 2 pure virtual functions.
 * the item knows who his neighbors, and if another item is equal to him.
 */
class GridItem {
public:
    //checks if GridItem is in a list
    virtual bool isInVisitedList(std::list<GridItem*> l) = 0;
    //checks if 2 GridItems are equals - if yes, return true, else - false
    virtual bool operator ==(const GridItem& gi) const = 0;
    //print gridItem derived class
    virtual void printGridItem() = 0;
    virtual void deleteGridItem() = 0;
private:
    //serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {}
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(GridItem)
#endif //MYPROJECTNAME_GRIDITEM_H
