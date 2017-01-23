#include <iostream>
#include <deque>
#include "BfsAlgorithm.h"

using namespace std;

vector<GridItem*> BfsAlgorithm:: findDestination(GridItem* source, GridItem* destination,
                            GenericGrid* grid) {
    //creates 2 deque - one for finding the destination, and second for deleting items in the end.
    deque<BfsCouple*> Q;
    deque<BfsCouple*> garbageQ;
    //creates a list of visited GridItems, to avoid duplicates in the deque
    std::list<GridItem*> visitedList;
    vector<GridItem*> trace;
    //push the source to the front of the deque, and update his "father" as Null
    BfsCouple *current = new BfsCouple(source, NULL);
    BfsCouple* neighbor;
    Q.push_back(current);
    //push the item to the garbage deque also
    garbageQ.push_back(current);
    //insert the GridItem to the visited items
    visitedList.push_back(current->getGridItem());
    //if current GridItem isn't destination, add its neighbors to deque
    while (!(*destination == *current->getGridItem())) {
        std::list<GridItem*> Neighbors = *(grid->getNeighbors(current->getGridItem()));
        std::list<GridItem*>::const_iterator iter;
        //add each neighbor to the deque if it hasn't been visited yet,
        //and update its "father" as current GridItem
        for (iter = Neighbors.begin(); iter != Neighbors.end(); ++iter) {
            neighbor = new BfsCouple(*iter, current);
            if(!(*iter)->isInVisitedList(visitedList)){
                visitedList.push_back(*iter);
                Q.push_back(neighbor);
            }
            garbageQ.push_back(neighbor);
        }
        //pop current item and update the current to the next item
        Q.pop_front();
        current = Q.front();
        //todo delete bfs couple that has been pop - done!!!
    }
    //go to "printPathToDestination" class to print the path to destination
    trace = pathToDestination(current);
    //in the end, delete all items which created
    deleteAll(garbageQ);
    //return the path
    return trace;
}
vector<GridItem*> BfsAlgorithm::pathToDestination(BfsCouple* b) {
    vector<GridItem*> trace;
    while(b->getBfsCouple() != NULL){
        trace.push_back(b->getGridItem());
        b = b->getBfsCouple();
    }
    trace.push_back(b->getGridItem());
    return trace;

}

void BfsAlgorithm::printPath(vector<GridItem*> trace){
    //printing recursively the path from source to destination
    if (!trace.empty()) {
        trace.back()->printGridItem();
        trace.pop_back();
    }
}
void BfsAlgorithm::deleteAll(deque<BfsCouple*> q){
    //delete all the bfsCouple objects in the garbage deque
    while(!q.empty()){
        q.front()->~BfsCouple();
        q.pop_front();
    }
}