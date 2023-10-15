#include <iostream>
#include <vector>

int Partition(std::vector<int>& array, int begin, int end) {
  if (begin != end) {
    std::swap(array[begin + rand() % (end - begin)], array[end]);
  }
  int pivot = array[end];
  int index = begin - 1;
  for (int i = begin; i < end + 1; i++) {
    if (array[i] <= pivot) {
      std::swap(array[++index], array[i]);
    }
  }
  return index;
}

void QuickSelect(std::vector<int>& array, int key) {
  int left = 0;
  int right = array.size() - 1;
  if (right - left == 1) {
    std::cout << array[key] << std::endl;
  } else {
    while (true) {
      int middle = Partition(array, left, right);
      if (middle == key) {
        std::cout << array[key] << std::endl;
        break;
      }
      (middle < key) ? left = middle + 1 : right = middle - 1;
    }
  }
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> vector(n);
  std::cin >> vector[0] >> vector[1];
  for (int i = 2; i < n; i++) {
    vector[i] = (vector[i - 1] * 123 + vector[i - 2] * 45) % (10000000 + 4321);
  }
  QuickSelect(vector, k - 1);
}
