set(core_SRCS Point.cpp StandardCab.cpp lidor/LuxuryCab.cpp Trip.cpp Driver.cpp
        Passenger.cpp Map.cpp TaxiCenter.cpp lidor/MainFlow.cpp lidor/main.cpp searchAlgo/BfsAlgorithm.cpp
        lidor/BfsCouple.cpp connection/Socket.cpp connection/Udp.cpp clientSide/clientMain.cpp Clock.cpp
        serverSide/serverMain.cpp serverSide/ServerFlow.cpp serverSide/ServerFlow.h clientSide/ClientFlow.cpp clientSide/ClientFlow.h connection/Tcp.cpp connection/Tcp.h threads/ClientThreadFlow.cpp threads/ClientThreadFlow.h threads/SearchThread.cpp threads/SearchThread.h)

project(src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_serialization -lm -lpthread")
add_library(core ${core_SRCS} Color.h Point.cpp Point.h Manufacturer.h StandardCab.cpp
        StandardCab.h Trip.cpp Trip.h MartialStatus.h Driver.cpp
        Driver.h Passenger.cpp Passenger.h Map.cpp Map.h TaxiCenter.cpp TaxiCenter.h
        lidor/MainFlow.cpp lidor/MainFlow.h lidor/main.cpp searchAlgo/BfsAlgorithm.cpp searchAlgo/BfsAlgorithm.h lidor/BfsCouple.cpp
        lidor/BfsCouple.h searchAlgo/GridItem.h searchAlgo/GenericGrid.h connection/Socket.cpp connection/Socket.h connection/Udp.cpp connection/Udp.h
        serverSide/ServerFlow.cpp serverSide/ServerFlow.h Clock.cpp Clock.h serverSide/serverMain.cpp clientSide/ClientFlow.cpp clientSide/ClientFlow.h
        connection/Tcp.cpp connection/Tcp.h threads/ClientThreadFlow.cpp threads/ClientThreadFlow.h ../easylogging++.h ThreadPoolDemo/ThreadPool.h
        ThreadPoolDemo/ThreadPool.cpp ThreadPoolDemo/Job.h ThreadPoolDemo/Job.cpp ThreadPoolDemo/main.cpp)
add_executable(exe lidor/main.cpp)
add_executable(server serverSide/serverMain.cpp)
add_executable(client clientSide/clientMain.cpp)
add_executable(mainThread ThreadPoolDemo/main.cpp)
target_link_libraries(exe core -lm)
target_link_libraries(server core)
target_link_libraries(client core)
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(mainThread core)