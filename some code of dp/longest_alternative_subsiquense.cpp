#include <iostream>
#include <vector>

std::vector<int64_t> LongestAlternatingSubsequence(std::vector<int64_t>& array) {
  if (array.size() <= 2) {
    return array;
  }
  std::vector<size_t> dp_arr(array.size() - 1, 0);
  for (size_t i = 0; i < array.size() - 1; ++i) {
    dp_arr[i] = (array[i] < array[i + 1]) ? 1 : 0;
  }

  std::vector<int64_t> first_sequence;
  size_t current_sign = dp_arr[0];
  size_t current_idx = 0;
  first_sequence.push_back(array[0]);
  for (size_t i = 1; i < dp_arr.size(); ++i) {
    if (current_sign != dp_arr[i]) {
      first_sequence.push_back(array[i]);
      current_sign = dp_arr[i];
      current_idx = i;
    }
  }
  if (current_idx != 0 && dp_arr[current_idx] != dp_arr[current_idx - 1]) {
    first_sequence.push_back(array[current_idx + 1]);
  }

  if (first_sequence.size() == 1) {
    first_sequence.push_back(array[1]);
  }
  return first_sequence;
}

void PrintSequence(std::vector<int64_t>& array) {
  std::cout << array.size() << '\n';
  for (size_t i = 0; i < array.size(); ++i) {
    std::cout << array[i] << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t size = 0;
  std::cin >> size;
  std::vector<int64_t> arr(size, 0);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
  std::vector<int64_t> longest_alternating_sequence = LongestAlternatingSubsequence(arr);
  PrintSequence(longest_alternating_sequence);
  return 0;
}
