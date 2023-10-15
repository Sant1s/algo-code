#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

const size_t kSimple = 2e32 - 1;
const size_t kBase = 29;

std::vector<size_t> CountDegrees(size_t size) {
  std::vector<size_t> ret_value(size, 1);
  for (int64_t i = size - 2; i >= 0; --i) {
    ret_value[i] = ret_value[i + 1] * kBase;
  }
  return ret_value;
}

size_t Hash(const std::string& str, size_t ptr_size, size_t step,
            const std::vector<size_t>& degrees) {
  size_t ret_value = 0;
  for (size_t i = step; i < ptr_size; ++i) {
    ret_value += (str[i] - 'a') * degrees[i - step];
  }
  for (size_t i = 0; i < step; ++i) {
    ret_value += (str[i] - 'a') * degrees[ptr_size - step + i];
  }
  return ret_value % kSimple;
}

std::unordered_set<size_t> CountRotatesHashes(
    const std::string& ptr, const std::vector<size_t>& degrees) {
  std::unordered_set<size_t> ret_value;
  size_t current = Hash(ptr, ptr.size(), 0, degrees);
  ret_value.insert(current);
  for (size_t i = 0; i < ptr.size(); ++i) {
    current -= (ptr[i] - 'a') * degrees[0];
    current *= kBase;
    current = current + ptr[i] - 'a';
    ret_value.insert(current);
  }
  return ret_value;
}

void Solution() {
  std::string pattern;
  std::string string;
  std::cin >> pattern;
  std::cin >> string;
  size_t answer = 0;
  std::vector<size_t> degrees = CountDegrees(pattern.size());
  std::unordered_set<size_t> rotates = CountRotatesHashes(pattern, degrees);
  if (pattern.size() > string.size()) {
    std::cout << answer;
    return;
  }
  size_t str_hash = Hash(string, pattern.size(), 0, degrees);
  for (size_t i = 0; i < string.size(); ++i) {
    if (rotates.contains(str_hash)) {
      ++answer;
    }
    str_hash -= (string[i] - 'a') * degrees[0];
    str_hash *= kBase;
    str_hash += string[i + pattern.size()] - 'a';
  }
  std::cout << answer;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solution();
  return 0;
}
