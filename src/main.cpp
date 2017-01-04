#include "MainFlow.h"

using namespace std;
using namespace boost::archive;


int main() {

    //delete before submitting
    std::cout << "ex2 - src main" << std::endl;
    /*MainFlow run;
    run.runMainFlow();*/
    /*
    std::list<Point*> pointList;
    pointList.push_back(new Point(1,1));
    Map map(5,5, pointList);
    BfsAlgorithm bfsAlgorithm;
    bfsAlgorithm.findDestination(new Point(0,0), new Point(0,2), &map).size();*//*
*/
    GridItem* c = new Point(1,2);
    c->printGridItem();
    //Driver *gp = new Driver(123, 22, MARRIED, 12, 222);
    //StandardCab *gp = new StandardCab(222,Manufacturer ::FIAT,Color ::BLUE, 0);
    //gp->addCab(standardCab);
    Trip *gp = new Trip(new Point(0,0), new Point(0,2));
    //vector<Point*> a;
    //p->setPointsPath(a);


    vector<GridItem*> p;
    //p = a;
    p.push_back(new Point(1,1));
    p.push_back(new Point(1,2));
    p.push_back(new Point(1,3));
    //gp->setPointsPath(p);
    //GridItem* gp; //- not good
    //gp = new Point(1,1); //- not good
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << gp;
    s.flush();

    Trip* gp2;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> gp2;
/*

    GridItem* gpp; //- not good
    gpp = new Point(1,1); //- not good
    //std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserterp(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > sp(inserterp);
    boost::archive::binary_oarchive oap(sp);
    oap << gpp;
    sp.flush();

    GridItem* gp2p;
    boost::iostreams::basic_array_source<char> devicep(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2p(devicep);
    boost::archive::binary_iarchive iap(s2p);
    iap >> gp2p;
    */

    //cout << *gp2 << endl;
    cout <<"###################################" <<endl;
    //cout << (*gp) << endl;

    //delete gp;
    //delete gp2;

return 0;
}

/*
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
#include "Point.h"

using namespace std;
using namespace boost::archive;
//std::stringstream ss;

/*class Point {
    int x, y;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }
public:
    Point(int x, int y) : x(x), y(y) {}

    Point() : x(0), y(0) {}
    int getX() {return this->x;}
    int getY() {return this->y;}
    friend std::ostream& operator<< (std::ostream &os, const Point &p);
};

std::ostream& operator<< (std::ostream &os, const Point &p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;

}*/
/*
class GridPoint {
    Point *p;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & p;
    }

public:
    GridPoint(Point *p) : p(p) {};
    GridPoint() : p(NULL) {}
    virtual ~GridPoint() {
        delete p;
    }
    friend std::ostream& operator<< (std::ostream &os, const GridPoint &p);
};

std::ostream& operator<< (std::ostream &os, const GridPoint &p) {
    os << '(' << p.p->getX() << ',' << p.p->getY() << ')';
    return os;
}

class D3GridPoint : public GridPoint {
    int z;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<GridPoint>(*this);
        ar & z;
    }
public:
    D3GridPoint(Point *p, int z) : GridPoint(p), z(z) {};
};



int main() {


    Point *gp =new Point(1,2);

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << gp;
    s.flush();

    cout << serial_str << endl;

    Point *gp2;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> gp2;

    cout << (*gp2);

    delete gp;
    delete gp2;
    return 0;
}*/

/*
class animal
{
public:
    animal() = default;
    animal(int legs) : legs_{legs} {}
    int legs() const { return legs_; }

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version) { ar & legs_; }

    int legs_;
};

void save()
{
    text_oarchive oa{ss};
    animal a{4};
    animal &r = a;
    oa << r;
}

void load()
{
    text_iarchive ia{ss};
    animal a;
    animal &r = a;
    ia >> r;
    std::cout << r.legs() << '\n';
}

int main()
{
    save();
    load();
}
*/


