#include "Point.h"
#include <boost/serialization/export.hpp>

using namespace std;

Point::Point(int f, int s) {
    this->x = f;
    this->y = s;
}

Point::~Point() {
}

int Point::getX() {
    return this->x;
}

int Point::getY() {
    return this->y;
}

bool Point::isInVisitedList(std::list<GridItem *> l) {
    //std::list<GridItem*>::iterator iter;
    std::list<GridItem *>::const_iterator iter;
    for (iter = l.begin(); iter != l.end(); iter++) {
        if (this == *iter) {
            return true;
        }
    }
    return false;
}


std::ostream& operator<< (std::ostream &os, const Point &p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

bool Point::operator==(const Point &point) const {
    return ((this->x == point.x) && (this->y == point.y));;
}

bool Point::operator!=(const Point &point) const {
    return !(*this == point);
}

bool Point::operator ==(const GridItem& gi) const {
    Point& p = (Point&) gi;
    return ((this->x== p.getX()) && (this->y==p.getY()));;
}

void Point::setX(int x) {
    Point::x = x;
}

void Point::setY(int y) {
    Point::y = y;
}

void Point::printGridItem() {
cout << "(" << this->x << "," << this->y << ")" << endl;
}

void Point::deleteGridItem(){
    delete(this);
}
BOOST_CLASS_EXPORT(Point)