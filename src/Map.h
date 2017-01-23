#ifndef MYPROJECTNAME_MAP_H
#define MYPROJECTNAME_MAP_H

#include <list>
#include <vector>
#include "Point.h"
#include "GenericGrid.h"
#include "Driver.h"


using namespace std;

class Map : public GenericGrid {
private:
    int height;
    int width;
    std::list<Point *> obstacles;
    vector<vector<Point *>> pointsGrid;
    vector<vector<std::list<Driver *>>> driversGrid;

private:
    void createGridPoints();

    void freeObstacles();

    void freePointsGrid();

public:
    int getWidth();

    int getHeight();

    list<GridItem *>* getNeighbors(GridItem* gridItem);

    Map(int height, int width, list<Point *> obstacles);

    virtual ~Map();

    Point *getPointAt(int x, int y);

    void updateDriverLocation(Driver *driver, GridItem *dst);

    bool isValid(Point p);

    bool isObstacle(int i, int j);

    std::list<Driver *> getDriverAt(Point point);
};

#endif //MYPROJECTNAME_MAP_H