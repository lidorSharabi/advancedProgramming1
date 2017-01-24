#include <iostream>
#include <deque>
#include "BfsAlgorithm.h"

using namespace std;

vector<GridItem*> BfsAlgorithm:: findDestination(GridItem* source, GridItem* destination,
                            GenericGrid* grid) {
    //creates deque - for finding the destination
    deque<GridItem*> Q;
    //creates a list of visited GridItems, to avoid duplicates in the deque
    std::list<GridItem*> visitedList;
    vector<GridItem*> trace;
    //update his "father" as NULL and set him as visited
    source->setFather(NULL);
    source->setVisited(true);
    //insert the source GridItem to the visited items
    visitedList.push_back(source);
    //push the source to the front of the deque
    Q.push_back(source);
    GridItem *current = source;
    //if current GridItem isn't destination, add its neighbors to deque
    while (!(*destination == *current)) {
        std::list<GridItem*> Neighbors = *(grid->getNeighbors(current));
        std::list<GridItem*>::const_iterator iter;
        /*
         * add each neighbor to the deque if it hasn't been visited yet,
         * and update its "father" as current GridItem
         */
        for (iter = Neighbors.begin(); iter != Neighbors.end(); ++iter) {
            if (!(*iter)->isVisited()){
                (*iter)->setVisited(true);
                (*iter)->setFather(current);
                visitedList.push_back(*iter);
                Q.push_back(*iter);
            }
        }
        //pop current item and update the current to the next item
        Q.pop_front();
        current = Q.front();
    }
    //get path to destination
    trace = pathToDestination(current);
    //reset all objects
    resetBfsAlgorithm(visitedList);
    //return the path
    return trace;
}
vector<GridItem*> BfsAlgorithm::pathToDestination(GridItem* gridItem) {
    vector<GridItem*> trace;
    while(gridItem->getFather() != NULL){
        trace.push_back(gridItem);
        gridItem = gridItem->getFather();
    }
    trace.push_back(gridItem);
    return trace;
}

void BfsAlgorithm::printPath(vector<GridItem*> path){
    //printing recursively the path from source to destination
    while (!path.empty()) {
        path.back()->printGridItem();
        path.pop_back();
    }
}
void BfsAlgorithm::resetBfsAlgorithm(std::list<GridItem *> q){
    //delete all the bfsCouple objects in the garbage deque
    while(!q.empty()){
        q.front()->setFather(NULL);
        q.front()->setVisited(false);
        q.pop_front();
    }
}