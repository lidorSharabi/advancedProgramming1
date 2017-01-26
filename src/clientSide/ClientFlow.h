//
// Created by lsharabi on 02/01/17.
//

#ifndef MYPROJECTNAME_CLIENTFLOW_H
#define MYPROJECTNAME_CLIENTFLOW_H


#include "../Driver.h"

class ClientFlow {
    Driver* driver;

public:
    void runClientFlow(int argc, char *argv[]);
private:
    MartialStatus getMartialStatusBySymbol(char symbol);

    Driver* loadNewDriver();

    void deleteAllocatedMemory();

    void freeTrips(std::list<Trip*> trips);

    bool isNumber(const std::string &s);
};


#endif //MYPROJECTNAME_CLIENTFLOW_H
