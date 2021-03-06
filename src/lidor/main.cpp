#include "MainFlow.h"
#include "../searchAlgo/BfsAlgorithm.h"
#include "../Map.h"

using namespace std;
using namespace boost::archive;

#include "../../easylogging++.h"
_INITIALIZE_EASYLOGGINGPP
int main() {

    //delete before submitting
    std::cout << "ex2 - src main" << std::endl;
    /*MainFlow run;
    run.runMainFlow();*/

    std::list<Point*> pointList;
    LOG(INFO) << "START";
    Map p(1000,1000, pointList);
    LOG(INFO) << "END";
    Point* a = new Point(0,0);
    Point b = *a;
    b.setX(2);
    a->setX(3);
    cout << *a<< endl << b << endl;
    Color c = Color::BLUE;
    if (c == BLUE){
        cout <<"lilili";
    }
    int num = 0, num1;
    string str;
    vector<string> splitedStr;

    getline(cin, str);
    boost::split(splitedStr, str, boost::is_any_of(" "));
    while (splitedStr.size()){
    double d = strtod(splitedStr[num].c_str(), NULL);
    //cout << splitedStr.size() << endl;
    cout << d << endl;
    num++;
    }
    /*num ;
    //cin >> num1 ;
    cin >> string1 ;
    getline(cin, string1);
    //vector<string> a = boost::split();
    if (cin.fail()){
        cout << "fail" <<endl;
    }
    //cout << num << endl;
    //cout << num1 << endl;
    cout << string1 << endl;
    //cout<< strcmp("add", "aee");
    std::list<Point*> pointList;
    pointList.push_back(new Point(1,1));
    Map* map = new Map(1000,1000, pointList);
    BfsAlgorithm bfsAlgorithm;
    cout << "start cal bfs" << endl;
    bfsAlgorithm.findDestination(new Point(0,0), new Point(2,1), map);
    bfsAlgorithm.findDestination(new Point(0,0), new Point(3,1), map);
*/
    /*GridItem* c = new Point(1,2);
    //c->printGridItem();
    Driver *gp = new Driver(0, 0, SINGLE, 0, 0);
    //StandardCab *gp = new StandardCab(222,Manufacturer ::FIAT,Color ::BLUE, 0);
    //gp->bindCabToDriver(standardCab);
    //Trip *gp = new Trip(new Point(0,0), new Point(0,2));
    //vector<Point*> a;
    //p->setPointsPath(a);


    cout << *gp << endl;
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

    Driver* gp2;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> gp2;
*//*

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
    *//*

    //cout << *gp2 << endl;
    cout <<"###################################" <<endl;
    cout << *gp2 << endl;
    //cout << (*gp) << endl;

    //delete gp;
    //delete gp2;
*/
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


