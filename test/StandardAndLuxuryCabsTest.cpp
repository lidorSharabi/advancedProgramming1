//
// Created by lsharabi on 02/12/16.
//

#include "gtest/gtest.h"
#include "../src/StandardCab.h"
#include "../src/lidor/LuxuryCab.h"
using namespace std;
class StandardAndLuxuryCabsTest: public::testing::Test
{
protected:

    StandardCab sCab;
    LuxuryCab lCab;

    virtual void SetUp() {
        cout<<"Setting up"<<endl;
    }

    virtual void TearDown() {
        cout<<"Tearing down"<<endl;
    }

public:
    StandardAndLuxuryCabsTest(): sCab(1,Manufacturer::SUBARO,Color::GREEN),
    lCab(12,Manufacturer ::TESLA,Color::BLUE){}
};

TEST_F(StandardAndLuxuryCabsTest, SanityChecks){
    ASSERT_GT(lCab.getTarrif(100),sCab.getTarrif(100))<<
            "the default coefficient of tarrif for LuxuryCab is higher than"
            "StandardCab"<<std::endl;
    ASSERT_GT(lCab.getSpeed(),sCab.getSpeed())<<
            "the default coefficient of speed for LuxuryCab is higher than"
            "StandardCab"<<std::endl;
    ASSERT_TRUE(lCab.getTarrif(10) == 20)<<
            "the coefficient of LuxuryCab is 2"<<std::endl;
    ASSERT_TRUE(sCab.getTarrif(10) == 10)<<
            "the coefficient of StandardCab is 1"<<std::endl;
}

TEST_F(StandardAndLuxuryCabsTest, StrangeChecks){
    ASSERT_TRUE(lCab.getTarrif(10) == 20)<<
             "the coefficient of LuxuryCab is 2"<<std::endl;
    ASSERT_TRUE(sCab.getTarrif(10) == 10)<<
             "the coefficient of StandardCab is 1"<<std::endl;
}