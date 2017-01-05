set(core_SRCS Point.cpp StandardCab.cpp LuxuryCab.cpp Trip.cpp Driver.cpp
        Passenger.cpp Map.cpp TaxiCenter.cpp MainFlow.cpp  main.cpp BfsAlgorithm.cpp
        BfsCouple.cpp Socket.cpp Udp.cpp clientMain.cpp Clock.cpp
        serverMain.cpp ServerFlow.cpp ServerFlow.h ClientFlow.cpp ClientFlow.h)

project(src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_serialization")
add_library(core ${core_SRCS} Color.h Point.cpp Point.h Manufacturer.h StandardCab.cpp
        StandardCab.h Trip.cpp Trip.h MartialStatus.h Driver.cpp
        Driver.h Passenger.cpp Passenger.h Map.cpp Map.h TaxiCenter.cpp TaxiCenter.h
        MainFlow.cpp MainFlow.h main.cpp BfsAlgorithm.cpp BfsAlgorithm.h BfsCouple.cpp
        BfsCouple.h GridItem.h GenericGrid.h Socket.cpp Socket.h Udp.cpp Udp.h
        ServerFlow.cpp ServerFlow.h Clock.cpp Clock.h serverMain.cpp)
add_executable(exe main.cpp)
add_executable(server serverMain.cpp)
add_executable(client clientMain.cpp)
target_link_libraries(exe core)
target_link_libraries(server core)
target_link_libraries(client core)