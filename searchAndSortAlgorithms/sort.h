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
