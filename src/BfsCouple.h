//
// Created by lsharabi on 03/12/16.
//

#ifndef MYPROJECTNAME_BFSCOUPLE_H
#define MYPROJECTNAME_BFSCOUPLE_H

#include "GridItem.h"
/*
 * holds 2 references - one to GridItem on a grid,
 * and second to another BfsCouple, which represents the GridItem's "father" on a grid.
 */
class BfsCouple {
private:
    GridItem* gridItem;
    BfsCouple* bfsCouple;

public:
    //constructor
    BfsCouple(GridItem* son, BfsCouple* parent);
    //destructor
    ~BfsCouple();
    //return a pointer to a BfsCouple the object holds
    BfsCouple* getBfsCouple();
    //return a pointer to a GridItem the object holds
    GridItem* getGridItem();
};


#endif //MYPROJECTNAME_BFSCOUPLE_H
