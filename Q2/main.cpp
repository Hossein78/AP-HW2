#include <iostream>
#include "libArr.h"
#include "libVec.h"
#include <chrono>
#include <cmath>

template <typename Type>
double runTime(long int (Type::*)(int), int n);

int main() {
    long int (libArr::*my_pointer_to_function_Arr) (int) = &libArr::counter;
    long int (libVec::*my_pointer_to_function_Vec) (int) = &libVec::counter;
    for (int i = 1; i < std::pow(10,7); i*=10) {
        std::cout<<"elapsed time for Arr at "<<i<<" numbers : "<<runTime(my_pointer_to_function_Arr,i)<<" milli seconds "<<std::endl;
        std::cout<<"elapsed time for Vec at "<<i<<" numbers : "<<runTime(my_pointer_to_function_Vec,i)<<" milli seconds \n"<<std::endl;
    }
    return 0;
}

template <typename Type>
double runTime(long int (Type::*func)(int), int n) {
    Type a;
    auto start = std::chrono::system_clock::now();
    (a.*func)(n);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds.count()*1000;
}
