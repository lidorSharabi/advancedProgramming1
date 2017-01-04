#include "gtest/gtest.h"
#include "../src/Passenger.h"

using namespace std;

class PassengerTest: public::testing::Test
{
protected:
    Passenger passenger;
    Point p1 ,p2;
    virtual void SetUp(){
        cout<<"Setting up"<<endl;
    }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
    }
public:
    PassengerTest(): p1(0,1), p2(2,0), passenger(&p1,&p2){}
};


TEST_F(PassengerTest,SanityChecks){
    int rank = passenger.rankDriver();
    ASSERT_TRUE(rank > 0 && rank <=5)<<
         "rank should be between 1-5"<<std::endl;
};


