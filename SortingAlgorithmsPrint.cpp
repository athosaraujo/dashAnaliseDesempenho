#include <iostream>
#include <chrono>
#include <fstream>
#define N 10000
int qspartition(int arr[], int start, int end) {

  int pivot = arr[start];
  int count = 0;
  for (int i = start + 1; i <= end; i++) {
    if (arr[i] <= pivot)
      count++;
  }

  int pivotIndex = start + count;
  std::swap(arr[pivotIndex], arr[start]);

  int i = start, j = end;

  while (i < pivotIndex && j > pivotIndex) {

    while (arr[i] <= pivot) {
      i++;
    }

    while (arr[j] > pivot) {
      j--;
    }

    if (i < pivotIndex && j > pivotIndex) {
      std::swap(arr[i++], arr[j--]);
    }
  }

  return pivotIndex;
}

void quickSort(int arr[], int start, int end) {

  if (start >= end)
    return;

  int p = qspartition(arr, start, end);

  quickSort(arr, start, p - 1);

  quickSort(arr, p + 1, end);
}

void bubbleSort(int arr[], int n) {
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }

    if (swapped == false)
      break;
  }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void printArray(int A[], int size){
    for (int i = 0; i < size; i++)
       std::cout << A[i] << " ";
    std::cout << std::endl;
}

int main() {
  std::ofstream outFile("sample10000.csv");
  
  auto startTime = std::chrono::high_resolution_clock::now();
  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

  int arr[N];
  for (int i = 0; i < N; i++) {
    arr[i] = std::rand() % N;
  }
  int n = N;

  int qsarr[N];
  int bsarr[N];
  int msarr[N];


  std::cout << "Array não sorteado:\n";
  printArray(arr,n);
  
  for(int i=0;i<10;i++){
    std::copy(std::begin(arr), std::end(arr), std::begin(qsarr));
    startTime = std::chrono::high_resolution_clock::now();
    quickSort(qsarr, 0, n-1);
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    outFile << n <<",quicksort," << duration.count() << "\n";
  } 

  for(int i=0;i<10;i++){
    std::copy(std::begin(arr), std::end(arr), std::begin(bsarr));
    startTime = std::chrono::high_resolution_clock::now();
    bubbleSort(bsarr,n); 
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    outFile << n <<",bubblesort," << duration.count() << "\n";
  } 
  for(int i=0;i<10;i++){
    std::copy(std::begin(arr), std::end(arr), std::begin(msarr));
    startTime = std::chrono::high_resolution_clock::now(); 
    mergeSort(msarr, 0, n-1); 
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    outFile << n <<",mergesort," << duration.count() << "\n";
  } 

  return 0;
}
