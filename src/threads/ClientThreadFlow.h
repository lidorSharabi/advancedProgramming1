//
// Created by lsharabi on 13/01/17.
//

#ifndef MYPROJECTNAME_CLIENTINFO_H
#define MYPROJECTNAME_CLIENTINFO_H


#include "../Driver.h"
#include "../connection/Tcp.h"
#include "../TaxiCenter.h"
class ServerFlow;

class ClientThreadFlow {
private:

    Driver *client;
    Tcp *tcp;
    int clientDescriptor;
    ServerFlow *server;
    pthread_mutex_t lock_driveOneStep;
    pthread_mutex_t lock_addDriverToTaxiCenter;

    Driver* loadDriver() ;

    void bindCabToDriver();


public:
    Driver *getClient();

    ServerFlow *getServer();

    int getClientDescriptor();

    void setClientDescriptor(int clientDescriptor);

    ClientThreadFlow(ServerFlow *server, int clientDescriptor, Tcp *tcp);

    Tcp *getTcp();

    void setClient(Driver *client);

    int currentOperation();

    bool operationListIsNotEmpty();

    void startClientThread();

    static void* calculateTripPath(void* trip);

    void sendTripToClient();
};


#endif //MYPROJECTNAME_CLIENTINFO_H
