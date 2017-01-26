//
// Created by lsharabi on 03/12/16.
//

#include "gtest/gtest.h"
#include "../src/searchAlgo/BfsAlgorithm.h"
#include "../src/Map.h"

using namespace std;
class BfsAlgorithmTest: public::testing::Test
{
protected:
    Point *p1, *p2, *p3;
    std::list <Point*> obs;
    stack<GridItem*> st;


    virtual void SetUp(){
        cout<<"Setting up"<<endl;
        }
    virtual void TearDown(){
        cout<<"Tearing down"<<endl;
    }
public:
    BfsAlgorithmTest(): p1(new Point(1,2)),p2(new Point(3,4)), p3(new Point(0,0)){}
};

TEST_F(BfsAlgorithmTest,SanityChecks){
    Map map(5,5,obs);
    BfsAlgorithm bfsAlgo;
    st = bfsAlgo.findDestination(p3,p3,&map);
    Point p11(0,0);
    Point p111(0,0);
    ASSERT_TRUE(*p2 == (*(st.top())))<<"the first point should be (0,0)"<<endl;
    ASSERT_EQ(*p2,Point(1,0))<<"the second point should be (1,0)"<<endl;
    ASSERT_EQ(*p3, Point(1,1))<<"the third point should be (1,1)"<<endl;
}