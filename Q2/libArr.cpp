#include "libArr.h"

long int libArr::counter(int n) {
    long int sum;
    int * array{new int [n]};
    for (int i = 0; i < n ; ++i) {
        array[i]=i;
    }
    for (int j = 0; j < n ; ++j) {
        sum+=array[j];
    }
    return sum;
}
