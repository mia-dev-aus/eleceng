#include <assert.h>
#include "tests.h"
#include "array.h"

void get_max_index_test() {
    int len1{0};
    int arr1[0]{};
    assert(get_max_index(arr1, len1) == -1 && "get_max_index(arr1, len1) != -1");
    int len2{3};
    int arr2[3]{1, 2, 1};
    assert(get_max_index(arr2, len2) == 1 && "get_max_index(arr2, len2) != 1");
    int len3{9};
    int arr3[9]{1, 2, 9, 1, 1, 1, 9, 0, 0};
    assert(get_max_index(arr3, len3) == 2 && "get_max_index(arr3, len3) != 2");
    int len4{4};
    int arr4[4]{1, 1, 3, 4};
    assert(get_max_index(arr4, len4) == 3 && "get_max_index(arr4, len4) != 3");
}
