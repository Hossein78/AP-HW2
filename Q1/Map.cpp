#include "Map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

Map::Map(int** Arr,int N) {
    n=N;
    DistanceC.resize(static_cast<long long unsigned>(fact(n*2-2)/fact(n-1)/fact(n-1)));
    arr=new int* [n];
    for (int i = 0; i <n ; ++i) {
        arr[i]=new int [n];
        for (int j = 0; j <n ; ++j) {
            arr[i][j]=Arr[i][j];
        }
    }
}

int Map::findRouteA() {
    int row{0},column{0};
    for (int i = 0; i <(n-1)*2 ; i++) {
        if (column==n-1){
            DistanceA += std::abs(arr[row+1][column] - arr[row][column]);
            row++;
            showpathA+="0";
            continue;
        }
        if (row ==n-1){
            DistanceA += std::abs(arr[row][column + 1] - arr[row][column]);
            column++;
            showpathA+="1";
            continue;
        }
        int down=std::abs(arr[row+1][column] - arr[row][column]);
        int right=std::abs(arr[row][column+1] - arr[row][column]);
        if (down<=right) {
            DistanceA += std::abs(arr[row+1][column] - arr[row][column]);
            row++;
            showpathA+="0";
        } else {
            DistanceA += std::abs(arr[row][column + 1] - arr[row][column]);
            column++;
            showpathA+="1";
        }
    }
    return DistanceA;
}

int Map::findRouteB() {
    int row{0},column{0};
    for (int i = 0; i <(n-1)*2 ; i++) {
        if (row==n-1 && column==n-1)
            break;
        if (column==n-1){
            DistanceB += std::abs(arr[row+1][column] - arr[row][column]);
            row++;
            showpathB+="0";
            continue;
        }
        if (row ==n-1){
            DistanceB += std::abs(arr[row][column + 1] - arr[row][column]);
            column++;
            showpathB+="1";
            continue;
        }
        int down=std::abs(arr[row+1][column] - arr[row][column]);
        int right=std::abs(arr[row][column+1] - arr[row][column]);
        int diagonal=std::abs(arr[row+1][column+1] - arr[row][column]);
        if (down<=right && down<=diagonal) {
            DistanceB += std::abs(arr[row+1][column] - arr[row][column]);
            row++;
            showpathB+="0";
        }
        else if (right<=down && right<=diagonal){
            DistanceB += std::abs(arr[row][column + 1] - arr[row][column]);
            column++;
            showpathB+="1";
        }
        else if(diagonal<=right && diagonal<=down){
            DistanceB += std::abs(arr[row+1][column + 1] - arr[row][column]);
            column++;
            row++;
            showpathB+="2";
        }
    }
    return DistanceB;
}

int Map::findRouteC() {
    std::string my_path{};
    for (int i = 1; i < n * 2 - 1; ++i) {
        if (i<=n-1)
            my_path+="0";
        else
            my_path+="1";
    }
    std::string* path{new std::string [fact(n*2-2)/fact(n-1)/fact(n-1)]};
    long long int counter{};

    while (std::next_permutation(my_path.begin(),my_path.end())) {
        int row{0},column{0};
        path[counter]=my_path;
        for (int i = 0; i <(n-1)*2 ; i++) {
            if (my_path[i] == '0') {
                DistanceC[counter] += std::abs(arr[row+1][column] - arr[row][column]);
                row++;
            }
            if (my_path[i] == '1') {
                DistanceC[counter] += std::abs(arr[row][column + 1] - arr[row][column]);
                column++;
            }
        }
        counter++;
    }

    int row{0},column{0};
    path[counter]=my_path;
    for (int i = 0; i <(n-1)*2 ; i++) {
        if (my_path[i] == '0') {
            DistanceC[counter] += std::abs(arr[row+1][column] - arr[row][column]);
            row++;
        }
        if (my_path[i] == '1') {
            DistanceC[counter] += std::abs(arr[row][column + 1] - arr[row][column]);
            column++;
        }
    }
    showpathC = path[Min(DistanceC)];
    std::sort(DistanceC.begin(),DistanceC.end());
    return DistanceC[0];
}

void Map::showMap() {
    std::cout<<"The map : "<<std::endl;
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j <n ; ++j) {
            std::cout<<arr[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
}

void Map::findRoute() {
    std::cout<<"The distance of the A way : "<<findRouteA()<<std::endl;
    std::cout<<"The distance of the B way : "<<findRouteB()<<std::endl;
    std::cout<<"The distance of the C way : "<<findRouteC()<<std::endl;
}

void Map::showRoute(){
    // path A
    std::vector<std::vector<char>> pathRoad;
    pathRoad.resize(static_cast<unsigned>(n));
    for (int i = 0; i < n; ++i) {
        pathRoad[i].resize(static_cast<unsigned>(n));
        for (int j = 0; j < n ; ++j) {
            pathRoad[i][j]='-';
        }
    }
    pathRoad[0][0]='*';
    int row{},column{};
    std::cout<< "The path of the A : "<<std::endl;
    for (int i = 0; i < showpathA.length() ; ++i) {
        if (showpathA[i]=='0') {
            pathRoad[row+1][column]='*';
            row++;
        }
        if (showpathA[i]=='1') {
            pathRoad[row][column+1]='*';
            column++;
        }
    }
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n ; ++j) {
            std::cout<<pathRoad[i][j]<< " ";
        }
        std::cout<<std::endl;
    }

    //path B
    for (int i = 0; i < n; ++i) {
        pathRoad[i].resize(static_cast<unsigned>(n));
        for (int j = 0; j < n ; ++j) {
            pathRoad[i][j]='-';
        }
    }
    pathRoad[0][0]='*';
    row=column=0;
    std::cout<< "The path of the B : "<<std::endl;
    for (int i = 0; i < showpathB.length() ; ++i) {
        if (showpathB[i]=='0') {
            pathRoad[row+1][column]='*';
            row++;
        }
        if (showpathB[i]=='1') {
            pathRoad[row][column+1]='*';
            column++;
        }
        if (showpathB[i]=='2'){
            pathRoad[row+1][column+1]='*';
            row++;
            column++;
        }
    }
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n ; ++j) {
            std::cout<<pathRoad[i][j]<< " ";
        }
        std::cout<<std::endl;
    }

    // path C
    pathRoad.resize(static_cast<unsigned>(n));
    for (int i = 0; i < n; ++i) {
        pathRoad[i].resize(static_cast<unsigned>(n));
        for (int j = 0; j < n ; ++j) {
            pathRoad[i][j]='-';
        }
    }
    pathRoad[0][0]='*';
    row=column=0;
    std::cout<< "The path of the C : "<<std::endl;
    for (int i = 0; i < showpathC.length() ; ++i) {
        if (showpathC[i]=='0') {
            pathRoad[row+1][column]='*';
            row++;
        }
        if (showpathC[i]=='1') {
            pathRoad[row][column+1]='*';
            column++;
        }
    }
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n ; ++j) {
            std::cout<<pathRoad[i][j]<< " ";
        }
        std::cout<<std::endl;
    }
}

int Map::Min(std::vector<int> x) {
    int min[1][2];
    min[0][0]=INFINITY;
    min[0][1]=INFINITY;
    for (int i = 0; i < x.size() ; ++i) {
        if (x[i]<min[0][0]) {
            min[0][0] = x[i];
            min[0][1] = i;
        }
    }
    return min[0][1];
}

long long int Map::fact(int n) {
    if (n==0)
        return 1;
    return n*fact(n-1);
}