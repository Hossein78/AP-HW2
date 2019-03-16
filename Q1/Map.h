#ifndef TEST1_MAP_H
#define TEST1_MAP_H


#include <string>
#include <cmath>
#include <vector>

class Map {
public:
    Map(int**,int);
    void showMap();
    void findRoute();
    void showRoute();

private:
    int findRouteA();
    int findRouteB();
    int findRouteC();
    int Min(std::vector<int>);
    long long int fact(int);

    int n{};
    int** arr;
    std::string showpathA,showpathB,showpathC;
    std::vector<int> DistanceC;
    int DistanceA{},DistanceB{};
};


#endif