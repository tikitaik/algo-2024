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
    }

    return arr;
}
