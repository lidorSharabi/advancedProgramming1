#ifndef MYPROJECTNAME_GENERICGRID_H
#define MYPROJECTNAME_GENERICGRID_H
#include "GridItem.h"
/*
 *  An abstract class (interface) which define a grid with width and height
 */
class GenericGrid {
public:
    virtual int getWidth() =0;
    virtual int getHeight() =0;
    virtual list<GridItem*>* getNeighbors(GridItem* gridItem) = 0;

    //returns neighbors of a GridItem in a grid size m*n
    //virtual list<GridItem*>* getNeighbors(int m, int n) = 0;
};
#endif //MYPROJECTNAME_GENERICGRID_H
