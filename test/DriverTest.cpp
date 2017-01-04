#include "gtest/gtest.h"
#include "../src/Driver.h"
#include "../src/Map.h"
#include "../src/TaxiCenter.h"

class DriverTest: public::testing::Test
{
protected:
    Driver driver1, driver2;
    Passenger *passenger1, *passenger2;
    StandardCab* cab;
    Point *src1, *des1, *src2, *des2;
    std::list <Point*> l;

    virtual void SetUp() {
        cout<<"Setting up"<<endl;
        driver1.addNewPassenger(passenger2);
        driver2.addNewPassenger(passenger1);
        driver2.removePassenger(passenger1);
        driver1.addCab(cab);
        driver1.updateRankDriver(passenger1->rankDriver());
    }

    virtual void TearDown() {
        cout<<"Tearing down"<<endl;
    }

public:
    DriverTest(): driver1(20544886,22,MartialStatus::SINGLE,4,1),
                  driver2(2054454,30,MartialStatus::MARRIED,10,2),
                  cab(new StandardCab(1, Manufacturer::FIAT, Color::GREEN)),
                  src1(new Point(0, 0)),
                    des1(new Point(1, 1)),
                    src2(new Point(0, 0)),
                    des2(new Point(1, 2)),
                    passenger1(new Passenger(src1, des2)),
                    passenger2(new Passenger(src1, des1)){}
};

TEST_F(DriverTest, SanityChecks){
    ASSERT_GT(driver1.getPassengersList().size(),driver2.getPassengersList().size())<<
          "checks the add/remove passenger,"
          "driver1 a should be 1 and driver b 0 passengers"<<std::endl;
    ASSERT_EQ((driver1.getCab())->getColor(), Color::GREEN)<<
          "the cab color of driver a should be RED"<<std::endl;
    ASSERT_TRUE(driver1.getNumOfPassengers() == 1)<<
           "driver a has zero trip"<<std::endl;
}

TEST_F(DriverTest, StrangeChecks){
    Map* map = new Map(3,3,l);
    driver1.driveOneStep(des2,map);
    Trip* trip = new Trip(1,0,0,1,1,3,22);
    TaxiCenter taxiCenter(map);
    taxiCenter.addDriver(&driver1);
    taxiCenter.addDriver(&driver2);
    taxiCenter.addTrip(trip);
    taxiCenter.startAllDriving();
    driver1.updateRankDriver(passenger1->rankDriver());
    EXPECT_TRUE(*(driver1.getCurrentLocation()) == *des2)<<
          "means driver b get to his dst"<<std::endl;
    EXPECT_TRUE(*(driver2.getCurrentLocation()) == *des1)<<
        "checks if startAllDriving func moved driver2 to this point"<<std::endl;
    EXPECT_LT(driver2.getSatisfaction(), driver1.getSatisfaction())<<
           "diver2 a ranked 0 times, while driver1 ranked once"<<std::endl;
    EXPECT_EQ(driver2.getNumOfPassengers(), 3);
}