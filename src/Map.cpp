#include "Map.h"


Map::Map(int height, int width, list<Point *> obstacles)
        : height(height), width(width), obstacles(obstacles) {
    createGridPoints();
}

int Map::getWidth() {
    return this->width;
}

int Map::getHeight() {
    return this->height;
}


void Map::createGridPoints() {
    pointsGrid.resize(width);
    driversGrid.resize(width);
    for (int i = 0; i < width; i++) {
        pointsGrid[i].resize(height);
        driversGrid[i].resize(height);
        for (int j = 0; j < height; j++){
            if (!isObstacle(i,j)) {
                pointsGrid[i][j] = new Point(i, j);
            }
            else {
                pointsGrid[i][j] = NULL;
            }
        }
    }
}

bool Map::isObstacle(int i,int j){
    Point p(i,j);
    std::list<Point*>::const_iterator iter;
    for (iter = obstacles.begin(); iter != obstacles.end(); iter++) {
        if (p == **iter) {
            return true;
        }
    }
    return false;
}

Point* Map::getPointAt(int x, int y) {
    return pointsGrid[x][y];
}

void Map::updateDriverLocation(Driver* driver, GridItem *dst) {
    Point* dstPoint = (Point*)dst;
    Point* currentLocationPoint = (Point*)driver->getCurrentLocation();
    //remove driver from previous location
    driversGrid[currentLocationPoint->getX()]
    [currentLocationPoint->getY()].remove(driver);
    //add driver to the new location
    driversGrid[dstPoint->getX()][dstPoint->getY()].push_back(driver);
}

Map::~Map() {
    freeObstacles();
    freePointsGrid();
}

void Map::freeObstacles() {
    while (!obstacles.empty()){
        delete(obstacles.front());
        obstacles.pop_front();
    }
}

void Map::freePointsGrid() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            delete (pointsGrid[i][j]);
        }
    }
}

bool Map::isValid(Point p) {
    return !(p.getX() >= width || p.getX() < 0 || p.getY() >= height || p.getY() < 0);
}

list<GridItem *>* Map::getNeighbors(GridItem* gridItem) {
    Point* p = (Point*)(gridItem);
    std::list<GridItem *> *neighbors = new list<GridItem *>;
    //add neighbors by clockwise - 9, 12, 3, 6
    if (p->getY() + 1 < this->height && !isObstacle(p->getX(), p->getY() + 1)) {
        neighbors->push_back(pointsGrid[p->getX()][p->getY() + 1]);
    }
    if (p->getX() + 1 < this->width && !isObstacle(p->getX() + 1, p->getY())) {
        neighbors->push_back(pointsGrid[p->getX() + 1][p->getY()]);
    }
    if (p->getY() - 1 >= 0 && !isObstacle(p->getX(), p->getY() - 1)) {
        neighbors->push_back(pointsGrid[p->getX()][p->getY() - 1]);
    }
    if (p->getX() - 1 >= 0 && !isObstacle(p->getX() - 1, p->getY())) {
        neighbors->push_back(pointsGrid[p->getX() - 1][p->getY()]);
    }
    return neighbors;
}

std::list<Driver *> Map::getDriverAt(Point point) {
    return driversGrid[point.getX()][point.getY()];
}
