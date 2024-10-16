# include <iostream>

template <typename T> T* insertionSort (T arr[], int size) {
   for (int i = 1; i < size; i++) {
       T key = arr[i];
       int j = i - 1;

       while (j >= 0 && arr[j] > key) {
           arr[j + 1] = arr[j];
           j = j - 1;
       }

       arr[j + 1] = key;
   } 

   return arr;
}

template <typename T> T* merge (T* arrOne, int oneSize, T* arrTwo, int twoSize) {
    std::cout << oneSize << " " << twoSize << '\n';
    std::cout << "arrOne : ";
    for (int i = 0; i < oneSize; i++) {
        std::cout << arrOne[i] << ", ";
    }
    std::cout << '\n';
    std::cout << "arrTwo : ";
    for (int i = 0; i < twoSize; i++) {
        std::cout << arrTwo[i] << ", ";
    }
    std::cout << '\n';
    
    int i = 0;
    int j = 0;
    int k = 0;
    T* merged = new T;
    
    while (i < oneSize && j < twoSize) {
        std::cout << i << " : arrOne[i] = " << arrOne[i] << ", " << j << " : arrTwo[j] = " << arrTwo[j]<< '\n';
        if (arrOne[i] <= arrTwo[j]) {
            merged[k] = arrOne[i];
            i++;
        }
        else {
            merged[k] = arrTwo[j];
            j++;
        }

        k++;
    }
    
    if (i < oneSize) {
        while (i < oneSize) {
            merged[k] = arrOne[i];
            i++;
            k++;
        }
    }
    else {
        while (j < twoSize) {
            merged[k] = arrTwo[j];
            j++;
            k++;
        }
    }

    for (int i = 0; i < oneSize + twoSize; i++) {
        std::cout << merged[i] << ", ";
    }
    std::cout << '\n';

    return merged;
}

template <typename T> T* mergeSort (T* arr, int low, int high) {

    if (low == high) {
        return &arr[low];
    }
    else {
        int range = high - low;
        int lowMid = range / 2 + low;
        int highMid = lowMid + 1;

        return merge(mergeSort(arr, low, lowMid), lowMid - low + 1, mergeSort(arr, highMid, high), high - highMid + 1);
    }
}
