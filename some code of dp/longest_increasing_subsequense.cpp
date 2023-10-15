#include <iostream>
#include <vector>

size_t LIS(const std::vector<int>& array) {
  std::vector<int> answer;
  std::vector<int>::iterator current;
  for (auto i : array) {
    current = std::lower_bound(answer.begin(), answer.end(), i);
    if (current == answer.end()) {
      answer.push_back(i);
      continue;
    }
    *current = i;
  }
  return answer.size();
}

int main() {
  size_t size;
  std::cin >> size;
  std::vector<int> array(size, 0);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  std::cout << LIS(array);
  return 0;
}

