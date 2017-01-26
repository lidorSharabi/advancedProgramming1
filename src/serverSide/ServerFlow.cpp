#include <stdlib.h>
#include "ServerFlow.h"
#include "../../easylogging++.h"

using namespace std;

void ServerFlow::runServerFlow(int argc, char *argv[]) {
    int inputOperation;
    char dummy;
    Trip *trip;
    //creating map and taxi center
    initializeServer();
    //initialize connection
    Tcp *tcp = new Tcp(true, atoi(argv[1]), "127.0.0.1");
    this->tcp = tcp;
    //after initialize the server is ready to accept clients
    tcp->initialize();
    threadPool = ThreadPool(BFS_THEARDS);
    //start getting operation inputs
    scanf("%d\n", &inputOperation);
    while (inputOperation != 7) {
        if (inputOperation != 1
            && inputOperation != 2
            && inputOperation != 3
            && inputOperation != 4
            && inputOperation != 9) {
            LOG(INFO) << "not valid operation input";
            cout << -1 << endl;
            continue;
        }
        switch (inputOperation) {
            case 1://accept drivers
                acceptClients();
                break;
            case 2:
                //load trip and if it's a valid trip add it to the taxi center
                loadNewTrip();
                break;
            case 3: //load taxi and if it's a valid taxi add it to the taxi center
                loadNewCab();
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
        scanf("\n%d\n", &inputOperation);
    }
    //send driver 7 operation to end themselves
    SendEndOperationToClients();
    //waiting for all the clients thread to end
    waitingForThreadsToEnd();
    //free all allocated memory
    taxiCenter->freeAllocatedMemory();
    tcp->~Tcp();
}

Manufacturer ServerFlow::getManufacturerBySymbol(char symbol) {
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
            return Manufacturer::NOT_VALID_MANUFACTURER;
    }
}

Color ServerFlow::getColorBySymbol(char symbol) {
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
            return Color::NOT_VALID_COLOR;
    }
}

void ServerFlow::loadNewTrip() {
    int id, startX, startY, endX, endY, numOfPassengers, startingTime;
    double tariff;
    bool valid = true;
    string str;
    vector<string> splitedStr;
    getline(cin, str);
    boost::split(splitedStr, str, boost::is_any_of(","));
    if (splitedStr.size() == 8) {
        if (isNumber(splitedStr[0]) && isNumber(splitedStr[1])
            && isNumber(splitedStr[2]) && isNumber(splitedStr[3])
            && isNumber(splitedStr[4]) && isNumber(splitedStr[5])
            && isNumber(splitedStr[7])) {
            id = atoi(splitedStr[0].c_str());
            startX = atoi(splitedStr[1].c_str());
            startY = atoi(splitedStr[2].c_str());
            endX = atoi(splitedStr[3].c_str());
            endY = atoi(splitedStr[4].c_str());
            numOfPassengers = atoi(splitedStr[5].c_str());
            startingTime = atoi(splitedStr[7].c_str());
            Map *map = taxiCenter->getMap();
            if (!map->isValid(Point(startX, startY)) || map->isObstacle(startX, startY)) {
                LOG(INFO) << "exit loadNewTrip() function: the start point is not a valid point";
                valid = false;
            }
            if (!map->isValid(Point(endX, endY)) || map->isObstacle(endX, endY)) {
                LOG(INFO) << "exit loadNewTrip() function: the end point is not a valid point";
                valid = false;
            }
            string tariffStr = splitedStr[6];
            boost::split(splitedStr, splitedStr[6], boost::is_any_of("."));
            if (splitedStr.size() != 2 || !isNumber(splitedStr[0]) || !isNumber(splitedStr[1])) {
                LOG(INFO) << "exit loadNewTrip() function: could'nt convert tariff to double";
                valid = false;
            } else {
                tariff = strtod(tariffStr.c_str(), NULL);
            }
            if (id < 0 || numOfPassengers < 0 || startingTime < 0 || tariff < 0) {
                LOG(INFO) << "exit loadNewTrip() function: at least one of the following is negative"
                        "\nid/numOfPassengers/startingTime/tariff";
                valid = false;
            }
        } else {
            LOG(INFO) << "exit loadNewTrip() function: at least one of the param isn't a integer"
                    "\nnot including tariff member";
            valid = false;
        }
    } else {
        LOG(INFO) << "exit loadNewTrip() function: the amount of argument for trip is " << splitedStr.size() <<
                  ",\nwhich is not valid";
        valid = false;
    }
    if (!valid) {
        cout << -1 << endl;
        LOG(INFO) << "FAIL: add trip to the taxi center";
    } else {
        taxiCenter->addTrip(new Trip(id, startX, startY, endX, endY, numOfPassengers,
                                     tariff, startingTime));
        LOG(INFO) << "SUCCESS: trip add to the taxi center";
    }
}

StandardCab *ServerFlow::loadNewCab() {
    int id, taxiType;
    char dummy, manufacturer, color;
    Manufacturer manufacturer1;
    Color color1;
    bool valid = true;
    string str;
    vector<string> splitedStr;
    getline(cin, str);
    boost::split(splitedStr, str, boost::is_any_of(","));
    if (splitedStr.size() == 4) {
        if (!isNumber(splitedStr[0]) || !isNumber(splitedStr[1])) {
            LOG(INFO) << "exit loadNewCab() function: at least one of the param isn't a integer";
            valid = false;
        }
        id = atoi(splitedStr[0].c_str());
        taxiType = atoi(splitedStr[1].c_str());
        if (id < 0 || (taxiType != 0 && taxiType != 1)) {
            LOG(INFO) << "exit loadNewCab() function: either id is negative or taxi type is different from 0/1";
            valid = false;
        }
        manufacturer1 = getManufacturerBySymbol(splitedStr[2].at(0));
        color1 = getColorBySymbol(splitedStr[3].at(0));
        if (manufacturer1 == NOT_VALID_MANUFACTURER || color1 == NOT_VALID_COLOR) {
            LOG(INFO) << "exit loadNewCab() function: either manufacturer or color isn't valid";
            valid = false;
        }
    }
    else {
        LOG(INFO) << "exit loadNewCab() function: the amount of argument for cab is " << splitedStr.size() <<
                  ",\nwhich is not valid";
        valid = false;
    }
    if (!valid) {
        cout << -1 << endl;
        LOG(INFO) << "FAIL: add taxi to the taxi center";
    } else {
        taxiCenter->addCab(new StandardCab(
                id, manufacturer1, color1, taxiType));
        LOG(INFO) << "SUCCESS: taxi add to the taxi center";
    }
}

int ServerFlow::loadDriverId() {
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
        if (pthread_create(&pthread, NULL, clientThread, (void *) clientInfo)) {
            LOG(INFO) << "client thread failed";
        }
        numOfDrivers--;
    }
}

void *ServerFlow::clientThread(void *clientInfo) {
    ClientThreadFlow *clientInfo1 = (ClientThreadFlow *) clientInfo;
    clientInfo1->getTcp()->sendData(
            "first server message", clientInfo1->getClientDescriptor(), true);
    clientInfo1->startClientThread();
    return NULL;
}

void ServerFlow::initializeServer() {
    int width, height, numOfObstacles, x, y, iter = 0;
    char dummy;
    string str;
    std::list<Point *> obstacles;
    vector<string> splitedStr;
    bool noValid = true, validObstacle = true;

    while (noValid) {
        iter++;
        //delete all the elements from the list (destroy them)
        obstacles.clear();
        if (iter > 1) {
            cout << -1 << endl;
        }
        getline(cin, str);
        //check validations on map param
        boost::split(splitedStr, str, boost::is_any_of(" "));
        /*
         * if atoi() return 0 it might be because the convert failed or because
         * the string is represent 0
         * either way it's not a valid input
         */
        width = atoi(splitedStr[0].c_str());
        height = atoi(splitedStr[1].c_str());
        if (splitedStr.size() == 0 || splitedStr.size() > 2 || (width <= 0 || height <= 0)) {
            LOG(INFO) << "something wrong with map size param";
            continue;
        }
        //check validations on amount obstacles param
        getline(cin, str);
        if (!isNumber(str)) {
            LOG(INFO) << "something wrong with num Of Obstacles param";
            continue;
        }
        numOfObstacles = atoi(str.c_str());
        //check validations on obstacles param, split every obstacle by ','
        if (numOfObstacles > 0) {
            for (int i = 0; i < numOfObstacles; i++) {
                if (validObstacle) {
                    getline(cin, str);
                    boost::split(splitedStr, str, boost::is_any_of(","));
                    //first check it the inputs are integers and after that convert them to int
                    if (isNumber(splitedStr[0]) && isNumber(splitedStr[1])) {
                        x = atoi(splitedStr[0].c_str());
                        y = atoi(splitedStr[1].c_str());
                    } else {
                        validObstacle = false;
                        LOG(INFO) << "something wrong with obstacle param";
                        continue;
                    }
                    if (splitedStr.size() != 2 || x < 0 || x >= width || y < 0 || y >= height) {
                        validObstacle = false;
                        LOG(INFO) << "something wrong with valid obstacle param";
                        continue;
                    } else obstacles.push_back(new Point(x, y));
                }
            }
            if (!validObstacle) {
                validObstacle = true;
                continue;
            }
        }
        noValid = false;
    }
    //create map
    Map *map = new Map(width, height, obstacles);
    taxiCenter = new TaxiCenter(map);
}

TaxiCenter *ServerFlow::getTaxiCenter() {
    return taxiCenter;
}

void ServerFlow::SendEndOperationToClients() {
    std::list<Driver *>::const_iterator driverIter;
    std::list<Driver *> drivers = taxiCenter->getDrivers();
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter) {
        (*driverIter)->operations.push_back(7);
    }
}

void ServerFlow::waitingForThreadsToEnd() {
    std::list<Driver *>::const_iterator driverIter;
    std::list<Driver *> drivers = taxiCenter->getDrivers();
    bool done;
    while (true) {
        done = true;
        for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter) {
            if ((*driverIter)->operations.size() > 0) {
                done = false;
            }
        }
        if (done) {
            return;
        }
    }
}

bool ServerFlow::isNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}