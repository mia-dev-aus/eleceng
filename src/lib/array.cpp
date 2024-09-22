#include "array.h"

// Finds the index of the element in an array with the greatest value.
int get_max_index(int array[], int length) {
    // Invalid case
    if (length == 0) {
        return -1;
    }

	// Middle of array
	int mid{get_mid_index(length)};
	int max{array[mid]};
	int max_index{mid};
	for (int i{1}; mid + i < length; ++i) {
		// Check left
		if (mid - 1 >= 0 && array[mid - i] > max) {
			max = array[mid - i];
			max_index = mid - i;
		} 
		
		// Check right
		if (array[mid + i] > max) {
			max = array[mid + i];
			max_index = mid + i;
		} 
	}

	return max_index;
}

int get_mid_index(int length) {
    return length / 2 - 1 + (length % 2);
}
