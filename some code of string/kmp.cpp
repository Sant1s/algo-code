#include <iostream>
#include <string>
#include <vector>

std::vector<int> PrefixFunction(const std::string& str) {
  std::vector<int> prefix(str.length(), 0);
  int current = 0;
  for (size_t i = 0; i < str.length() - 1; i++) {
    current = prefix[i];
    while (current > 0 && str[current] != str[i + 1]) {
      current = prefix[current - 1];
    }
    if (str[i + 1] == str[current]) {
      prefix[i + 1] = current + 1;
    }
  }
  return prefix;
}

std::vector<int> KnutMorrisPratt(const std::string& str,
                                 const std::string& ptr) {
  std::vector<int> answer;
  std::vector<int> prefix = PrefixFunction(ptr + '#' + str);
  for (size_t i = 0; i < str.length(); ++i) {
    if (prefix[ptr.length() + i + 1] == ptr.length()) {
      answer.push_back(i - ptr.length());
    }
  }
  return answer;
}

int main() {
  std::string string;
  std::string pattern;
  std::cin >> string;
  std::cin >> pattern;
  std::vector<int> answer = KnutMorrisPratt(string, pattern);
  for (const auto& iter : answer) {
    std::cout << iter + 1 << '\n';
  }
  return 0;
}
