//
// Created by lsharabi on 02/01/17.
//

#ifndef MYPROJECTNAME_CLIENTFLOW_H
#define MYPROJECTNAME_CLIENTFLOW_H


#include "Driver.h"

class ClientFlow {
    Driver* driver;

public:
    void runClientFlow(int argc, char *argv[]);

    MartialStatus getMartialStatusBySymbol(char symbol);

    Driver* loadNewDriver();

    void deleteAllocatedMemory();
};


#endif //MYPROJECTNAME_CLIENTFLOW_H
