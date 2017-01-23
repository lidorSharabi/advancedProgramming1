#include "gtest/gtest.h"
#include "../src/TaxiCenter.h"
#include "../src/lidor/LuxuryCab.h"
#include "../src/Map.h"

using namespace std;

class TaxiCenterTest: public::testing::Test
{
protected:
    //TaxiCenter taxiCenter;
    Passenger pass1;
    Trip *trip1,*trip2;
    StandardCab* cab1, *cab2;
    LuxuryCab* lux1, *lux2;
    Point *p1 ,*p2, *p3;
    Driver* driver;
    //Map *map;
    std::list<Point*> list;
    virtual void SetUp(){
        cout<<"Setting up"<<endl;
        list.push_back(p1);
        list.push_back(p3);
        }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
    }
public:
    TaxiCenterTest():
    p1(new Point(0,1)), p2(new Point(2,0)), p3(new Point(0,0)),
    driver(new Driver(2,33, MartialStatus::SINGLE,1 ,1)),
    pass1(p1,p2),
    trip1(new Trip(123,p3,p2)), trip2(new Trip(345, p1,p1)),
    cab1(new StandardCab(12, Manufacturer::FIAT, Color::GREEN)),
    cab2(new StandardCab(122, Manufacturer::FIAT, Color::PINK)),
    lux1(new LuxuryCab(12345, Manufacturer::HONDA, Color::GREEN)),
    lux2(new LuxuryCab(12789, Manufacturer::FIAT, Color::GREEN)){}
};


TEST_F(TaxiCenterTest,SanityChecks){
    Map* map = new Map(3,3, list);
    TaxiCenter taxiCenter(map);
    taxiCenter.addCab(cab1);
    taxiCenter.addCab(lux1);
    taxiCenter.addDriver(driver);
    taxiCenter.addTrip(trip1);
    taxiCenter.callAndSendCab(pass1);
    driver->driveOneStep(p2, map );

    ASSERT_TRUE(taxiCenter.getCabs().size() == 2)<<
        "the taxiCenter should have 2 cabs by now"<<endl;
    ASSERT_EQ(*(driver->getCurrentLocation()),*p2)<<
         "the driver location should be point(2,0)"<<endl;
    ASSERT_TRUE(taxiCenter.getTrips().size() == 1)<<
        "the taxiCenter should have noe trip by now"<<endl;
}
