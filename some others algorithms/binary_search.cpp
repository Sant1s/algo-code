#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target) {
  if (begin >= end) {
    return false;
  }
  size_t left_border = 0;
  size_t right_border = end - begin - 1;
  int middle;
  while (left_border <= right_border) {
    middle = ((right_border + left_border) / 2);
    if (*(begin + middle) == target) {
      return true;
    }
    if (*(begin + middle) < target) {
      left_border = middle + 1;
    }
    if (*(begin + middle) > target) {
      right_border = middle - 1;
    }
  }
  return false;
}

int main() {
  int n, q;
  std::cin >> n;
  int* array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  std::cin >> q;
  int i, j, t;
  for (int k = 0; k < q; ++k) {
    std::cin >> i >> j >> t;
    if (BinarySearch(array + i, array + j, t)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  delete[] array;
}
