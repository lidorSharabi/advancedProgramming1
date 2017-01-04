#ifndef MYPROJECTNAME_SERVERFLOW_H
#define MYPROJECTNAME_SERVERFLOW_H

#include "Manufacturer.h"
#include "Color.h"
#include "Trip.h"
#include "StandardCab.h"
#include "Clock.h"
#include "Udp.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "Map.h"

class ServerFlow {
private:
    TaxiCenter *taxiCenter;

private:
    Manufacturer getManufacturerBySymbol(char symbol);

    Color getColorBySymbol(char symbol);

    Trip *loadNewTrip();

    StandardCab *loadNewCab();

    int loadDriverId();

    void loadAllDrivers(Udp& udp);

    void initializeServer();

public:
    void runServerFlow(int argc, char *argv[]);
};


#endif //MYPROJECTNAME_SERVERFLOW_H
