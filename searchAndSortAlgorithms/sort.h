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
