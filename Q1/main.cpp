#include <iostream>
#include <time.h>
#include "Map.h"

int main(){
    int number{5};
    int** arr{new int* [number]};
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = 0; i <number ; ++i) {
        arr[i]=new int [number];
        for (int j = 0; j <number ; ++j) {
            arr[i][j]=rand()%100+1;
        }
    }
    Map x{arr,number};
    x.showMap();
    x.findRoute();
    x.showRoute();
    return 0;
}