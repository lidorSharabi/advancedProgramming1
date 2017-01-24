#include <stdlib.h>
#include "ServerFlow.h"
#include "../../easylogging++.h"

using namespace std;

void ServerFlow::runServerFlow(int argc, char *argv[]) {
    int inputOperation;
    char dummy;
    Trip *trip;
    //initialize connection
    Tcp* tcp = new Tcp(true, atoi(argv[2]), "127.0.0.1");
    this->tcp= tcp;
    //after initialize the server is ready to accept clients
    tcp->initialize();
    //creating map and taxi center
    initializeServer();

    //start getting operation inputs
    scanf("%d", &inputOperation);
    while (inputOperation != 7) {
        switch (inputOperation) {
            case 1://accept drivers
                acceptClients();
                break;
            case 2:
                taxiCenter->addTrip(loadNewTrip());
                break;
            case 3: //insert vehicle
                taxiCenter->addCab(loadNewCab());
                break;
            case 4: //add request for driver location
                taxiCenter->requestForDriverLocation(loadDriverId());
                break;
            case 9: //moving the clock one step ahead
                taxiCenter->increaseClock();
                //start driving
                taxiCenter->startAllDriving();
                break;
        }
        scanf("\n%d", &inputOperation);
    }
    //send driver 7 operation to end themselves
    SendEndOperationToClients();
    //waiting for all the clients thread to end
    waitingForThreadsToEnd();
    //free all allocated memory
    taxiCenter->freeAllocatedMemory();
    tcp->~Tcp();
}

Manufacturer ServerFlow::getManufacturerBySymbol(char symbol){
    switch (symbol) {
        case 'H':
            return Manufacturer::HONDA;
        case 'S':
            return Manufacturer::SUBARO;
        case 'T':
            return Manufacturer::TESLA;
        case 'F':
            return Manufacturer::FIAT;
        default:
            return Manufacturer::HONDA;
    }
}

Color ServerFlow::getColorBySymbol(char symbol){
    switch (symbol) {
        case 'R':
            return Color::RED;
        case 'B':
            return Color::BLUE;
        case 'G':
            return Color::GREEN;
        case 'P':
            return Color::PINK;
        case 'W':
            return Color::WHITE;
        default:
            return Color::RED;
    }
}

Trip* ServerFlow::loadNewTrip(){
    int id, startX, startY, endX, endY, numOfPassengers, startingtime;
    double tariff;
    char dummy;
    scanf("%d%c%d%c%d%c%d%c%d%c%d%c%lf%c%d", &id, &dummy, &startX, &dummy, &startY,
          &dummy, &endX, &dummy, &endY, &dummy, &numOfPassengers, &dummy, &tariff,
          &dummy, &startingtime);
    return new Trip(id,startX, startY, endX, endY, numOfPassengers,
                    tariff , startingtime);
}

StandardCab* ServerFlow::loadNewCab(){
    int id, taxiType;
    char dummy, manufacturer, color;
    scanf("%d%c%d%c%c%c%c", &id, &dummy, &taxiType, &dummy,
          &manufacturer, &dummy, &color);
        return new StandardCab(
                id, getManufacturerBySymbol(manufacturer),getColorBySymbol(color), taxiType);
}

int ServerFlow::loadDriverId(){
    int id;
    scanf("%d", &id);
    return id;
}

void ServerFlow::acceptClients() {
    int numOfDrivers;
    //numOfDrivers represent the amount of the drivers/clients
    scanf("%d", &numOfDrivers);
    while (numOfDrivers) {
        pthread_t pthread;
        int clientDes = this->tcp->acceptClient();
        ClientThreadFlow *clientInfo = new ClientThreadFlow(this, clientDes, this->tcp);
        if (pthread_create(&pthread, NULL, clientThread, (void*)clientInfo))
        {
            LOG(INFO) << "client thread failed";
        }
        numOfDrivers--;
    }
}

void* ServerFlow::clientThread(void* clientInfo){
    ClientThreadFlow *clientInfo1 = (ClientThreadFlow*) clientInfo;
    clientInfo1->getTcp()->sendData(
            "first server message", clientInfo1->getClientDescriptor(), true);
    clientInfo1->startClientThread();
    return NULL;
}

void ServerFlow::initializeServer(){
    int width, height, numOfObstacles, x, y;
    char dummy;
    std::list<Point*> obstacles;

    //calculating map inputs
    scanf("%d%c%d", &width, &dummy, &height);
    scanf("%d", &numOfObstacles);
    if (numOfObstacles > 0) {
        for (int i = 0; i < numOfObstacles; i++) {
            scanf("%d%c%d", &x, &dummy, &y);
            obstacles.push_back(new Point(x, y));
        }
    }
    //create map
    Map* map = new Map(width, height, obstacles);
    taxiCenter = new TaxiCenter(map);
}

TaxiCenter *ServerFlow::getTaxiCenter() {
    return taxiCenter;
}

void ServerFlow::SendEndOperationToClients() {
    std::list<Driver *>::const_iterator driverIter;
    std::list<Driver *> drivers = taxiCenter->getDrivers();
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter)
    {
        (*driverIter)->operations.push_back(7);
    }
}

void ServerFlow::waitingForThreadsToEnd(){
    std::list<Driver *>::const_iterator driverIter;
    std::list<Driver *> drivers = taxiCenter->getDrivers();
    bool done;
    while(true){
        done = true;
        for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter){
            if ((*driverIter)->operations.size() > 0){
                done = false;
            }
        }
        if (done){
            return;
        }
    }
}