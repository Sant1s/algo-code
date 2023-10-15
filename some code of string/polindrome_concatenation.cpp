#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

std::string Reverse(const std::string& word) {
  std::string ret_value = word;
  std::reverse(ret_value.begin(), ret_value.end());
  return ret_value;
}

std::unordered_map<std::string, size_t> GetWordsReversedHashMap(
    const std::vector<std::string>& words) {
  std::unordered_map<std::string, size_t> ret_value;
  for (size_t i = 0; i < words.size(); ++i) {
    ret_value[Reverse(words[i])] = i;
  }
  return ret_value;
}

std::set<std::pair<int, int>> PalindromicConcatenation(
    const std::vector<std::string>& words) {
  std::unordered_map<std::string, size_t> hashmap_reverse =
      GetWordsReversedHashMap(words);
  std::set<std::pair<int, int>> ret_value;
  std::string left;
  std::string right;
  for (size_t i = 0; i < words.size(); ++i) {
    for (size_t j = 0; j < words[i].size(); ++j) {
      left = words[i].substr(0, j + 1);
      right = words[i].substr(j + 1);

      if (hashmap_reverse.contains(left)) {
        if (right == Reverse(right) && hashmap_reverse[left] != i) {
          ret_value.emplace(i, hashmap_reverse[left]);
        }
      }

      if (hashmap_reverse.contains(right)) {
        if (left == Reverse(left) && hashmap_reverse[right] != i) {
          ret_value.emplace(hashmap_reverse[right], i);
        }
      }
    }
  }
  return ret_value;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t words_amount = 0;
  std::cin >> words_amount;
  std::vector<std::string> words(words_amount);
  for (auto& iter : words) {
    std::cin >> iter;
  }
  std::set<std::pair<int, int>> answer = PalindromicConcatenation(words);
  std::cout << answer.size() << '\n';
  for (const auto& iter : answer) {
    std::cout << iter.first + 1 << ' ' << iter.second + 1 << '\n';
  }
  return 0;
}
