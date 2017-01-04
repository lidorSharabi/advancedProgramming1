#include "gtest/gtest.h"
#include "../src/Point.h"
using namespace std;
class PointTest: public::testing::Test
{
protected:
    Point p1;
    Point p2;
    Point p3;

    virtual void SetUp(){
        cout<<"Setting up"<<endl;
    }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
    }
public:
    PointTest(): p1(1,2),p2(3,4), p3(3,4){}
};


TEST_F(PointTest,SanityChecks){

    ASSERT_NE(p1,p2)<<"p1 is not equal to p2, should return true"<<endl;
    ASSERT_EQ(p2, p3)<< "those points are equal"<<endl;
}


TEST_F(PointTest,StrangeChecks){

    EXPECT_NE(p1,Point(1,1))<<"p1 is equal to this point"<<endl;
    EXPECT_EQ(p2, Point(3,4))<< "those points are equal"<<endl;
}


