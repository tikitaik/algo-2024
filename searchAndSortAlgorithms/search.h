# include <iostream>

template <typename T> int linearSearch(T arr[], int size, T goal) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == goal) {
            std::cout << "element found at index " << i << '\n';
            return i;
        }
    }

    std::cout << "element could not be found\n";
    return -1;
}

template <typename T> int binarySearch(T arr[], int size, T goal) {
    int low = 0, high = size - 1, mid;

    while (low <= high) {

        mid = (high + low) / 2;

        if (arr[mid] == goal) {
            std::cout << "element found at " << mid << '\n';
            return mid;
        }
        else if (arr[mid] < goal) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        } 
    }

    std::cout << "element not in list\n";
    return -1;
}
