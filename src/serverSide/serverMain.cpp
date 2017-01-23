#include "ServerFlow.h"
#include "../../easylogging++.h"
_INITIALIZE_EASYLOGGINGPP
int main(int argc, char *argv[]){
    ServerFlow serverFlow = ServerFlow();
    //start server flow
    serverFlow.runServerFlow(argc, argv);
    return 0;
}