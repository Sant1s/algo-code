#include <iostream>
#include <map>
#include <vector>

class SuffixAutomaton {
 protected:
  struct State {
    size_t length;
    int64_t link;
    bool terminated;
    std::vector<int64_t> next;
    State()
        : length(0),
          link(-1),
          terminated(false),
          next(std::vector<int64_t>(26, -2)) {}
  };

 public:
  SuffixAutomaton() : last_(0) {}
  void AddChar(char letter);
  bool Find(const std::string& string);

 private:
  std::vector<State> suffix_auto_;
  int64_t last_;
};

void SuffixAutomaton::AddChar(char letter) {
  if (suffix_auto_.empty()) {
    suffix_auto_.push_back(State());
  }
  size_t current = suffix_auto_.size();
  suffix_auto_.push_back(State());
  suffix_auto_[current].length = suffix_auto_[last_].length + 1;
  int64_t parent;
  for (parent = last_;
       parent != -1 && suffix_auto_[parent].next[letter - 'a'] == -2;
       parent = suffix_auto_[parent].link) {
    suffix_auto_[parent].next[letter - 'a'] = current;
  }
  if (parent == -1) {
    suffix_auto_[current].link = 0;
  } else {
    int64_t q_position = suffix_auto_[parent].next[letter - 'a'];
    if (suffix_auto_[parent].length + 1 == suffix_auto_[q_position].length) {
      suffix_auto_[current].link = q_position;
    } else {
      int64_t clone = suffix_auto_.size();
      suffix_auto_.push_back(State());
      suffix_auto_[clone].length = suffix_auto_[q_position].length + 1;
      suffix_auto_[clone].next = suffix_auto_[q_position].next;
      suffix_auto_[clone].link = suffix_auto_[q_position].link;
      for (; parent != -1 &&
             suffix_auto_[parent].next[letter - 'a'] == q_position;
           parent = suffix_auto_[parent].link) {
        suffix_auto_[parent].next[letter - 'a'] = clone;
      }
      suffix_auto_[q_position].link = suffix_auto_[current].link = clone;
    }
  }
  last_ = current;
}
bool SuffixAutomaton::Find(const std::string& string) {
  if (suffix_auto_.empty()) {
    return string.empty();
  }
  int64_t current = 0;
  for (const auto& iter : string) {
    if (suffix_auto_[current].next[std::tolower(iter) - 'a'] == -2) {
      return false;
    }
    current = suffix_auto_[current].next.at(std::tolower(iter) - 'a');
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  SuffixAutomaton suffix_auto;
  char command;
  std::string word;
  while (std::cin >> command >> word) {
    if (command == '?') {
      (suffix_auto.Find(word)) ? std::cout << "YES\n" : std::cout << "NO\n";
    }
    if (command == 'A') {
      for (const auto& iter : word) {
        suffix_auto.AddChar(std::tolower(iter));
      }
    }
  }
  return 0;
}
