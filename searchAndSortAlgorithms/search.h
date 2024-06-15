# include <iostream>

template <typename T> int linearSearch(T arr[], int size, T checkpoint) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == checkpoint) {
            std::cout << "element found at index " << i << '\n';
            return i;
        }
    }

    std::cout << "element could not be found\n";
    return -1;
}

template <typename T> int binarySearch(T arr[], int size, T checkpoint) {
    int low = 0, high = size - 1, mid;

    while (low <= high) {

        mid = (high + low) / 2;

        if (arr[mid] == checkpoint) {
            std::cout << "element found at " << mid << '\n';
            return mid;
        }
        else if (arr[mid] < checkpoint) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        } 
    }

    std::cout << "element not in list\n";
    return -1;
}
