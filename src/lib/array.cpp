#include "array.h"

// Finds the index of the element in an array with the greatest value.
int getMaxIndex(int array[], int length) {
    // Invalid case
    if (length == 0) {
        return -1;
    }

	// Middle of array
	int mid{getMidIndex(length)};
	int max{array[mid]};
	int maxIndex{mid};
	for (int i{1}; mid + i < length; ++i) {
		// Check left
		if (mid - 1 >= 0 && array[mid - i] > max) {
			max = array[mid - i];
			maxIndex = mid - i;
		} 
		
		// Check right
		if (array[mid + i] > max) {
			max = array[mid + i];
			maxIndex = mid + i;
		} 
	}

	return maxIndex;
}

int getMidIndex(int length) {
    return length / 2 - 1 + (length % 2);
}
