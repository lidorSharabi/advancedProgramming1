#ifndef MYPROJECTNAME_BFSALGORITHM_H
#define MYPROJECTNAME_BFSALGORITHM_H

#include "GridItem.h"
#include "GenericGrid.h"
#include "BfsCouple.h"
#include <vector>
/*
 * A class which hold a BFS algorithm.
 * the class find a path from source to destination in a generic grid.
 */

class BfsAlgorithm {
public:
    /*
     * gets 2 pointers to GridItems - source and destination, and a generic grid,
     * and find the path in the grid.
     */
    vector<GridItem*> findDestination(GridItem* source, GridItem* destination,
                         GenericGrid* grid);
private:
    /*
     * prints the path from source to destination.
     * the function gets pointer to BfsCouple - an object which hold a GridItem,
     * and a reference to another BfsCouple - the "father" of the GridItem on the grid.
     */
    vector<GridItem*> pathToDestination(GridItem* gridItem);
    /*
     * deletes all the items which allocated in the memory while program.
     * gets a pointer to deque which holds all the BfsCouple which created.
     */
    void resetBfsAlgorithm(list<GridItem *> q);

    void printPath(vector<GridItem*> path);
};


#endif //MYPROJECTNAME_BFSALGORITHM_H