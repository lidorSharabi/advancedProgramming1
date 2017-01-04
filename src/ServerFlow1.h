//
// Created by lsharabi on 01/01/17.
//

#ifndef MYPROJECTNAME_SERVERFLOW_H
#define MYPROJECTNAME_SERVERFLOW_H

#include "TaxiCenter.h"
#include "Udp.h"

class ServerFlow {
private:
    TaxiCenter *taxiCenter;

private:
    Manufacturer getManufacturerBySymbol(char symbol);

    Color getColorBySymbol(char symbol);

    Trip *loadNewTrip();

    StandardCab *loadNewCab();

    int loadDriverId();

    void loadAllDrivers(int numOfDrivers, Udp* udp);

    void initializeServer(Udp* udp);

public:
    void runServerFlow();
};

#endif //MYPROJECTNAME_SERVERFLOW_H
