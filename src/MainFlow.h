//
// Created by lsharabi on 02/12/16.
//

#ifndef MYPROJECTNAME_MAINFLOW_H
#define MYPROJECTNAME_MAINFLOW_H

#include "TaxiCenter.h"

class MainFlow {
private:
    TaxiCenter* taxiCenter;
public:
    //MainFlow();

private:
    MartialStatus getMartialStatusBySymbol(char symbol);

    Manufacturer getManufacturerBySymbol(char symbol);

    Color getColorBySymbol(char symbol);

    Driver *loadNewDriver();

    Trip *loadNewTrip();

    StandardCab *loadNewCab();

    int loadDriverId();

public:
    void runMainFlow();
};


#endif //MYPROJECTNAME_MAINFLOW_H
