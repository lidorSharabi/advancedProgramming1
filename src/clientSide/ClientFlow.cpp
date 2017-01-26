#include "ClientFlow.h"
#include "../connection/Tcp.h"
#include "../Map.h"
#include "../../easylogging++.h"

using namespace std;
using namespace boost::archive;

void ClientFlow::runClientFlow(int argc, char *argv[]) {
    StandardCab *newCab;
    std::list<Trip *> tripsList;
    int cab;
    string ip = argv[1];
    char buffer[40000];
    if (strcmp(argv[1], "localhost") == 0) {
        ip = "127.0.0.1";
    }
    Tcp tcp(false, atoi(argv[2]), ip);
    tcp.initialize();

    //check the connection work well
    memset(buffer, 0, sizeof(buffer));
    tcp.reciveData(buffer, sizeof(buffer), 0);
    LOG(INFO) << buffer;

    //serialize driver
    Driver *driver = loadNewDriver();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    //send driver to server
    tcp.sendData(serial_str, serial_str.size());
    //waiting for operation value
    memset(buffer, 0, sizeof(buffer));
    tcp.reciveData(buffer, sizeof(buffer), 0);
    while (strcmp(buffer, "exit") != 0) {
        //print the recive operation
        LOG(INFO) << buffer;
        //add cab to driver
        if (strcmp(buffer, "add new cab") == 0) {
            LOG(INFO) << "CASE ADD NEW CAB";
            memset(buffer, 0, sizeof(buffer));
            tcp.reciveData(buffer, sizeof(buffer), 0);
            boost::iostreams::basic_array_source<char> device1(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s21(device1);
            boost::archive::binary_iarchive ia1(s21);
            ia1 >> newCab;
            driver->bindCabToDriver(newCab);
        }
        //add trip
        if (strcmp(buffer, "add trip") == 0) {
            //add trip to the driver
            LOG(INFO) << "CASE ADD NEW TRIP";
            Trip *newTrip;
            memset(buffer, 0, sizeof(buffer));
            tcp.reciveData(buffer, sizeof(buffer), 0);
            boost::iostreams::basic_array_source<char> device1(buffer, sizeof(buffer));
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s21(device1);
            boost::archive::binary_iarchive ia1(s21);
            ia1 >> newTrip;
            //add newTrip to the list of trip and set this trip fot the driver
            tripsList.push_back(newTrip);
            driver->setTrip(newTrip);
        }
        //moving driver
        if (strcmp(buffer, "move driver") == 0) {
            LOG(INFO) << "CASE ADD NEW TRIP";
            //NULL input means this is cient
            driver->driveOneStep(NULL);
            Point *p = (Point *) driver->getCurrentLocation();
            LOG(INFO) << (*p);
        }
        memset(buffer, 0, sizeof(buffer));
        tcp.reciveData(buffer, sizeof(buffer), 0);
    }
    //delete All allocated Memory
    deleteAllocatedMemory();
    driver->getCab()->~StandardCab();
    freeTrips(tripsList);
    driver->~Driver();
    tcp.~Tcp();
}

void ClientFlow::freeTrips(std::list<Trip *> trips) {
    while (!trips.empty()) {
        delete (trips.front());
        trips.pop_front();
    }
}

MartialStatus ClientFlow::getMartialStatusBySymbol(char symbol) {
    switch (symbol) {
        case 'S':
            return MartialStatus::SINGLE;
        case 'M':
            return MartialStatus::MARRIED;
        case 'D':
            return MartialStatus::DIVORCED;
        case 'W':
            return MartialStatus::WIDDOWED;
        default:
            return MartialStatus::NOT_VALID_MARTIALSTATUS;
    }
}

void ClientFlow::deleteAllocatedMemory() {

}

Driver *ClientFlow::loadNewDriver() {
    int id, age, experience, vehicle_id;
    char status, dummy;
    bool valid = true;
    MartialStatus martialStatus;
    string str;
    vector<string> splitedStr;
    getline(cin, str);
    boost::split(splitedStr, str, boost::is_any_of(","));
    if (splitedStr.size() == 5) {
        if (!isNumber(splitedStr[0]) || !isNumber(splitedStr[1])
            || !isNumber(splitedStr[3]) || !isNumber(splitedStr[4])) {
            LOG(INFO) << "exit loadNewDriver() function: at least one of the param isn't a integer";
            exit(1);
        }
        id = atoi(splitedStr[0].c_str());
        age = atoi(splitedStr[1].c_str());
        experience = atoi(splitedStr[3].c_str());
        vehicle_id = atoi(splitedStr[4].c_str());
        if (id < 0 || age < 0 || experience < 0 || vehicle_id < 0) {
            LOG(INFO) << "exit loadNewDriver() function: at least one of the param is negative";
            exit(1);
        }
        martialStatus = getMartialStatusBySymbol(splitedStr[2].at(0));
        if (martialStatus == NOT_VALID_MARTIALSTATUS) {
            LOG(INFO) << "exit loadNewDriver() function: martialStatus isn't valid";
            exit(1);
        }
    } else {
        LOG(INFO) << "exit loadNewDriver() function: the amount of argument for driver is " << splitedStr.size() <<
                  ",\nwhich is not valid";
        exit(1);
    }
    LOG(INFO) << "SUCCESS: load client driver";
    return new Driver(id, age, martialStatus, experience, vehicle_id);
}

bool ClientFlow::isNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}