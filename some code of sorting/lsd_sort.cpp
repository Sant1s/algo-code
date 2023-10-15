#include <iostream>

void Sort(long long int* arr, int size, const int kIndex) {
  int tmp_count[256];
  for (int i = 0; i < 256; ++i) {
    tmp_count[i] = 0;
  }
  for (int i = 0; i < size; ++i) {
    tmp_count[arr[i] >> (8 * kIndex) & 255]++;
  }
  for (int i = 1; i < 256; ++i) {
    tmp_count[i] += tmp_count[i - 1];
  }
  long long int* tmp = new long long int[size];
  for (int i = size - 1;; --i) {
    --tmp_count[arr[i] >> (8 * kIndex) & 255];
    tmp[tmp_count[arr[i] >> (8 * kIndex) & 255]] = arr[i];
    if (i == 0) {
      break;
    }
  }
  for (int i = 0; i < size; i++) {
    arr[i] = tmp[i];
  }
  delete[] tmp;
}

void LSDSort(long long int* arr, int size) {
  int tmp = sizeof(long long int);
  for (int i = 0; i < tmp; ++i) {
    Sort(arr, size, i);
  }
}

int main() {
  size_t n = 0;
  std::cin >> n;
  long long* array = new long long int[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  LSDSort(array, n);
  for (size_t i = 0; i < n; i++) {
    std::cout << array[i] << " ";
  }
  delete[] array;
}

