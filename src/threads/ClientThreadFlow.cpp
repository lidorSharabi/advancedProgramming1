#include "ClientThreadFlow.h"
#include "../serverSide/ServerFlow.h"
#include "SearchThread.h"
#include "../../easylogging++.h"

using namespace std;
ClientThreadFlow::ClientThreadFlow(ServerFlow *server, int clientDescriptor, Tcp *tcp) :
        server(server), clientDescriptor(clientDescriptor), tcp(tcp) {
    if (pthread_mutex_init(&lock_driveOneStep, 0)){
        LOG(INFO) << "failed initialize lock_driveOneStep mutex";
    }
    if (pthread_mutex_init(&lock_addDriverToTaxiCenter, 0)){
        LOG(INFO)<< "failed initialize lock_addDriverToTaxiCenter mutex";
    }
}

int ClientThreadFlow::getClientDescriptor() {
    return clientDescriptor;
}

void ClientThreadFlow::setClientDescriptor(int clientDescriptor) {
    ClientThreadFlow::clientDescriptor = clientDescriptor;
}

Tcp *ClientThreadFlow::getTcp() {
    return tcp;
}


bool ClientThreadFlow::operationListIsNotEmpty() {
    return client->operations.size() > 0;
}

void ClientThreadFlow::setClient(Driver *client) {
    ClientThreadFlow::client = client;
}

Driver *ClientThreadFlow::getClient() {
    return client;
}

ServerFlow *ClientThreadFlow::getServer() {
    return server;
}

int ClientThreadFlow::currentOperation() {
    if (operationListIsNotEmpty()) {
        return client->operations.front();
    }
    else {
        //to do maybe change to logging
        LOG(INFO) << "currentOperation(): operation list is empty or driver is not set";
        return -1;
    }
}

void ClientThreadFlow::startClientThread() {
    pthread_mutex_lock(&lock_addDriverToTaxiCenter);
    setClient(loadDriver());
    bindCabToDriver();
    pthread_mutex_unlock(&lock_addDriverToTaxiCenter);
    LOG(INFO) << "driver id: " << (*client).getId() << " added";
    while(true){
        if (operationListIsNotEmpty()) {
            switch (currentOperation()) {
                case 4: //request for driver location
                    client->getCurrentLocation()->printGridItem();
                    break;
                case 5: //calculate trip
                    {
                    pthread_t pthread;
                    SearchThread *searchThread =
                            new SearchThread(client->getTrip(), server->getTaxiCenter()->getMap());
                    if (pthread_create(&pthread, NULL, calculateTripPath, (void *) searchThread)) {
                        LOG(INFO) << "calculate trips path thread failed";
                    }
                    //waiting for calculateTripPath thread to end
                    pthread_join(pthread, NULL);
                    //sending trip
                    sendTripToClient();
                    }
                    break;
                case 7: //send end operation to the client and ending thread
                    tcp->sendData("exit", clientDescriptor, true);
                    client->operations.pop_front();
                    return;
                case 9: //move driver by one move according his taxi car
                    pthread_mutex_lock(&lock_driveOneStep);
                    client->driveOneStep(server->getTaxiCenter()->getMap());
                    pthread_mutex_unlock(&lock_driveOneStep);
                    //sending client message to move his driver
                    tcp->sendData("move driver", clientDescriptor, true);
                    break;
            }
            client->operations.pop_front();
        }
    }
}


Driver* ClientThreadFlow::loadDriver() {
    Driver *newDriver;
    char buffer[40000];
    //de - serialize driver
    tcp->reciveData(buffer, sizeof(buffer), clientDescriptor);
    boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> newDriver;
    server->getTaxiCenter()->addDriver(newDriver);
    return newDriver;
}

void ClientThreadFlow::bindCabToDriver(){
    list<Driver *>::const_iterator driverIter;
    list<StandardCab *>::const_iterator cabsIter;
    std::list<Driver*> drivers = server->getTaxiCenter()->getDrivers();
    std::list<StandardCab*> cabs = server->getTaxiCenter()->getCabs();
    for (driverIter = drivers.begin(); driverIter != drivers.end(); ++driverIter) {
        for (cabsIter = cabs.begin(); cabsIter != cabs.end(); ++cabsIter){
            if ((*driverIter)->getId() == client->getId()) {
                (*driverIter)->bindCabToDriver(*cabsIter);
                //sending client operation string, to bind new cab to the driver
                tcp->sendData("add new cab", clientDescriptor, true);
                std::string serial_str;
                boost::iostreams::back_insert_device <std::string> inserter(serial_str);
                boost::iostreams::stream <boost::iostreams::back_insert_device<std::string>> s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << ((*cabsIter));
                s.flush();
                //send cab to client
                tcp->sendData(serial_str, clientDescriptor);
                break;
            }
        }

    }
}

void *ClientThreadFlow::calculateTripPath(void* searchThread) {
    SearchThread* searchThread1 = (SearchThread*) searchThread;
    searchThread1->runBfsAlgorithm();
    return NULL;
}


void ClientThreadFlow::sendTripToClient(){
    tcp->sendData("add trip", clientDescriptor, true);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << (client->getTrip());
    s.flush();
    tcp->sendData(serial_str, clientDescriptor);
}

