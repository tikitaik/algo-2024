# pragma once
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

template<typename T> T* bubbleSort(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[j + 1] < arr[j] && j + 1 < size) {
               int temp = arr[j];
               arr[j] = arr[j + 1]; 
               arr[j + 1] = temp;
            }
        }

template <typename T> T* merge (T* arrOne, int oneSize, T* arrTwo, int twoSize) {
    
    int i = 0;
    int j = 0;
    int k = 0;
    T* merged = new T[oneSize + twoSize];
    
    while (i < oneSize && j < twoSize) {
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
    
    if (j == twoSize) {
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

        T* arrOne = mergeSort(arr, low, lowMid);
        T* arrTwo = mergeSort(arr, highMid, high);

        return merge(arrOne, lowMid - low + 1, arrTwo, high - highMid + 1);
    }
}

template <typename T> int partition(T* arr, int low, int high) {
    T pivot = arr[high];
    int i = low;
    int j = high;

    std::cout << "low : " << low << '\n';
    std::cout << "high : " << high << '\n';
    std::cout << "pivot : " << pivot << '\n';

    while (i < j) {

        while (arr[i] <= pivot && i < high) {
            i++;
        }

        while (arr[j] >= pivot && j > low) {
            j--;
        }

       if (i < j) {
           T temp = arr[i];
           arr[i] = arr[j];
           arr[j] = temp;
       } 
    }

    T temp = arr[j];
    arr[j] = arr[high];
    arr[high] = temp;

    std::cout << j << '\n';
    return j; 
}

template <typename T> T* quicksort(T* arr, int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high);

        quicksort(arr, low, pIndex - 1);
        quicksort(arr, pIndex + 1, high);
    }

    return arr;
}
