#ifndef AP_POINT_H
#define AP_POINT_H

#include "GridItem.h"
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
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
/*
 * class Point describes a point with x and y parameters.
 * point is on a grid, and implements "GridItem" class.
 */
using namespace std;
using namespace boost::archive;

class Point : public GridItem {
private:
    int x, y;

    friend class boost::serialization::access;
    //serialization Point x, y members
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<GridItem>(*this);
        ar & x;
        ar & y;
    }

public:
    //constructor
    Point(int f, int s);

    //destructor
    ~Point();

    //gets the x value of point
    int getX();

    //gets the y value of point
    int getY();

    //returns neighbors of a point in a grid size m*n
    //list<GridItem *> *getNeighbors(int m, int n);

    ////checks if Point is in a list
    bool isInVisitedList(std::list<GridItem *> l);

    //checks if 2 points are equals - if yes, return true, else - false
    bool operator==(const Point &point) const;

    //overload the operator << to print a point
    friend std::ostream &operator<<(std::ostream &os, const Point &p);

    void printGridItem();

    void deleteGridItem();

    void setX(int x);

    void setY(int y);

    //check if the points are different
    bool operator!=(const Point &point) const;

    //checks if 2 points are equals - if yes, return true, else - false
    bool operator==(const GridItem &p) const;

    Point() : x(0), y(0) {}
};


#endif //AP_POINT_H