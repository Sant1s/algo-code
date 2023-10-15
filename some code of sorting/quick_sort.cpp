#include <iostream>
#include <vector>

void QuickSort(std::vector<int>& vec, int begin, int end) {
  int pointer_1 = begin;
  int pointer_2 = end;
  int pivot = vec[rand() % (end - begin + 1) + begin];
  while (pointer_1 <= pointer_2) {
    while (vec[pointer_1] < pivot) {
      ++pointer_1;
    }
    while (vec[pointer_2] > pivot) {
      --pointer_2;
    }
    if (pointer_1 <= pointer_2) {
      std::swap(vec[pointer_1], vec[pointer_2]);
      ++pointer_1;
      --pointer_2;
    }
  }
  if (pointer_2 > begin) {
    QuickSort(vec, begin, pointer_2);
  }
  if (pointer_1 < end) {
    QuickSort(vec, pointer_1, end);
  }
}

int main() {
  std::vector<int> vector;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int number;
    std::cin >> number;
    vector.push_back(number);
  }
  int size = vector.size();
  QuickSort(vector, 0, size - 1);
  for (int i = 0; i < n; i++) {
    std::cout << vector[i] << std::endl;
  }
}
