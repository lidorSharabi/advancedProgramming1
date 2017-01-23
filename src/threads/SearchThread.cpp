//
// Created by lsharabi on 20/01/17.
//

#include "SearchThread.h"
#include "../BfsAlgorithm.h"

SearchThread::SearchThread(Trip* trip, Map* map):
        trip(trip), map(map){}

void SearchThread::runBfsAlgorithm() {
    BfsAlgorithm bfsAlgorithm;
    trip->setPointsPath(bfsAlgorithm.findDestination(
            trip->getStart(), trip->getEnd(), map));
    trip->getPointsPath().pop_back();
}