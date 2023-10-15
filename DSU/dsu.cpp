// 84164486

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class DSU {
 public:
  void Unite(T elem1, T elem2) {
    if (elem1 == elem2) {
      return;
    }
    elem1 = FindLeader(elem1);
    elem2 = FindLeader(elem2);
    if (elem1 == elem2) {
      return;
    }
    if (ranks_[elem1] > ranks_[elem2]) {
      std::swap(elem1, elem2);
    }
    ranks_[elem2] += ranks_[elem1];
    pow_[elem2] += pow_[elem1];
    parents_[elem1] = elem2;
  }

  DSU(T elem) {
    parents_.resize(elem);
    ranks_.resize(elem);
    pow_.resize(elem, 0);
    for (size_t i = 0; i < elem; ++i) {
      parents_[i] = i;
      ranks_[i] = 1;
    }
  }

  size_t GetPower(T elem) { return pow_[FindLeader(elem)]; }

  void AddPower(size_t pow, T elem1) { pow_[FindLeader(elem1)] += pow; }

 private:
  int FindLeader(T elem) {
    if (parents_[elem] == elem) {
      return elem;
    }
    return FindLeader(parents_[elem]);
  }
  std::vector<T> parents_;
  std::vector<T> ranks_;
  std::vector<size_t> pow_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t size;
  size_t answers;
  std::cin >> size >> answers;
  DSU<size_t> dsu(size);
  size_t ans = 0;
  size_t vertex1 = 0;
  size_t vertex2 = 0;
  size_t power = 0;
  for (size_t i = 0; i < answers; ++i) {
    std::cin >> ans;
    if (ans == 2) {
      std::cin >> vertex1;
      std::cout << dsu.GetPower(vertex1 - 1) << '\n';
    }
    if (ans == 1) {
      std::cin >> vertex1 >> vertex2 >> power;
      dsu.Unite(vertex1 - 1, vertex2 - 1);
      if (vertex1 != vertex2) {
        dsu.AddPower(power, vertex1 - 1);
      }
    }
  }
  return 0;
}
