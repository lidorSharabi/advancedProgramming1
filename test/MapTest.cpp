#include "gtest/gtest.h"
#include "../src/Map.h"
#include <list>

using namespace std;
class MapTest: public::testing::Test
{
protected:

    Point p1, p3, p4;
    Point * p2;
    std::list <Point*> obs;
    virtual void SetUp() {
        cout<<"Setting up"<<endl;

    }

    virtual void TearDown() {
        cout<<"Tearing down"<<endl;
    }

public:
    MapTest(): p1(0,0),p2(new Point(2,2)),p3(3,4),p4(4,3) {
        obs.push_back(p2);
    }
};

TEST_F(MapTest, SanityChecks){
    Map map(4,5,obs);
    ASSERT_TRUE(map.isObstacle(p2->getX(), p2->getY()))<<
        "p2 is an obstacle, should be true"<<std::endl;
    ASSERT_FALSE(map.isObstacle(p1.getX(), p1.getY()))<<
        "p1 is'nt an obstacle, should be false"<<std::endl;
}

TEST_F(MapTest, strangeChecks){
    Map map(4,4,obs);
    EXPECT_FALSE(map.isValid(p3))<<
         "p3 is'nt exist on map because of his y value,"
         "should be false"<<std::endl;
    EXPECT_FALSE(map.isValid(p4))<<
         "p3 is'nt exist on map, because of his x value,"
         "should be false"<<std::endl;
    EXPECT_TRUE(map.isValid(*p2))<<
         "p2 is exist on map, should be true"<<std::endl;

}