#ifndef MYPROJECTNAME_SREACHTHREAD_H
#define MYPROJECTNAME_SREACHTHREAD_H

#include "../Trip.h"
#include "../Map.h"

class SearchThread {
private:
    Trip* trip;
    Map* map;

public:
    SearchThread(Trip* trip, Map* map);
    
    void runBfsAlgorithm();
};


#endif //MYPROJECTNAME_SREACHTHREAD_H
