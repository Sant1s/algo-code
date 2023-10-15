#include <iostream>
#include <vector>

const int64_t kBase = 1e9;
int64_t Palindrome(const std::vector<int64_t>& arr) {
  std::vector<std::vector<int64_t>> dp_arr(arr.size(),
                                           std::vector<int64_t>(arr.size(), 1));
  for (size_t i = 0; i < arr.size() - 1; ++i) {
    dp_arr[i][i + 1] = int64_t(arr[i] == arr[i + 1]) + 2;
  }
  for (size_t i = arr.size() - 1; i < arr.size(); --i) {
    for (size_t j = i + 2; j < arr.size(); ++j) {
      dp_arr[i][j] = dp_arr[i + 1][j] + dp_arr[i][j - 1] - dp_arr[i + 1][j - 1];
      if (arr[i] == arr[j]) {
        dp_arr[i][j] += dp_arr[i + 1][j - 1] + 1;
      }
      dp_arr[i][j] = (dp_arr[i][j] < 0) ? ((kBase + dp_arr[i][j]) % kBase)
                                        : (dp_arr[i][j] % kBase);
    }
  }
  return dp_arr[0][arr.size() - 1];
}

int main() {
  size_t size = 0;
  std::cin >> size;
  std::vector<int64_t> array_of_num(size, 0);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array_of_num[i];
  }
  std::cout << Palindrome(array_of_num) << '\n';
  return 0;
}
