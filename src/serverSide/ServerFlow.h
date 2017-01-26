#ifndef MYPROJECTNAME_SERVERFLOW_H
#define MYPROJECTNAME_SERVERFLOW_H

#include "../Manufacturer.h"
#include "../Color.h"
#include "../Trip.h"
#include "../StandardCab.h"
#include "../Clock.h"
#include "../connection/Udp.h"
#include "../Driver.h"
#include "../TaxiCenter.h"
#include "../Map.h"
#include "../threads/ClientThreadFlow.h"
#include "../ThreadPoolDemo/ThreadPool.h"

#define BFS_THEARDS 5

class ServerFlow {
private:
    TaxiCenter *taxiCenter;
    Tcp* tcp;
    ThreadPool threadPool;
private:

    Manufacturer getManufacturerBySymbol(char symbol);

    Color getColorBySymbol(char symbol);

    void loadNewTrip();

    StandardCab *loadNewCab();

    int loadDriverId();

    void initializeServer();

    void acceptClients();

    static void* clientThread(void* clientInfo);

    void SendEndOperationToClients();

    void waitingForThreadsToEnd();

    bool isNumber(const std::string& s);

public:

    void runServerFlow(int argc, char *argv[]);

    TaxiCenter *getTaxiCenter();
};


#endif //MYPROJECTNAME_SERVERFLOW_H
