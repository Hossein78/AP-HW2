#include "libVec.h"
#include <vector>

long int libVec::counter(int n) {
    long int sum;
    std::vector<int> array(n);
    for (int i = 0; i < n ; ++i) {
        array[i]=i;
    }
    for (int j = 0; j < n ; ++j) {
        sum+=array[j];
    }
    return sum;
}
