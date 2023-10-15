// 75442437
#include <iostream>
#include <vector>

typedef std::vector<int> Vec;
typedef std::vector<Vec> VecVec;
typedef std::vector<VecVec> VecVecVec;

class FenwickTree {
 public:
  FenwickTree(int size) {
    tree_.resize(size);
    for (int i = 0; i < size; ++i) {
      tree_[i].resize(size);
      for (int j = 0; j < size; ++j) {
        tree_[i][j].resize(size, 0);
      }
    }
  }

  void Update(size_t x, size_t y, size_t z, int64_t val) {
    for (size_t i = x; i < tree_.size(); i = FuncG(i)) {
      for (size_t j = y; j < tree_.size(); j = FuncG(j)) {
        for (size_t k = z; k < tree_.size(); k = FuncG(k)) {
          tree_[i][j][k] += val;
        }
      }
    }
  }

  int64_t GetSum(size_t x_1, size_t y_1, size_t z_1, size_t x_2, size_t y_2,
                 size_t z_2) {
    return PrefSum(x_2, y_2, z_2) - PrefSum(x_1 - 1, y_2, z_2) -
           PrefSum(x_2, y_1 - 1, z_2) - PrefSum(x_2, y_2, z_1 - 1) +
           PrefSum(x_1 - 1, y_1 - 1, z_2) + PrefSum(x_1 - 1, y_2, z_1 - 1) +
           PrefSum(x_2, y_1 - 1, z_1 - 1) - PrefSum(x_1 - 1, y_1 - 1, z_1 - 1);
  }

 private:
  VecVecVec tree_;

  static size_t FuncF(size_t idx) { return idx & (idx + 1); }
  static size_t FuncG(size_t idx) { return idx | (idx + 1); }

  int64_t PrefSum(size_t x, size_t y, size_t z) {
    int64_t answer = 0;
    for (int i = x; i >= 0; i = FuncF(i) - 1) {
      for (int j = y; j >= 0; j = FuncF(j) - 1) {
        for (int k = z; k >= 0; k = FuncF(k) - 1) {
          answer += tree_[i][j][k];
        }
      }
    }
    return answer;
  }
};

int main() {
  int num = 0;
  std::cin >> num;
  FenwickTree tree(num);
  size_t command = 0;
  size_t x1 = 0;
  size_t y1 = 0;
  size_t z1 = 0;
  size_t x2 = 0;
  size_t y2 = 0;
  size_t z2 = 0;
  int64_t number = 0;
  while (true) {
    std::cin >> command;
    if (command == 3) {
      break;
    }
    if (command == 1) {
      std::cin >> x1 >> y1 >> z1 >> number;
      tree.Update(x1, y1, z1, number);
    } else if (command == 2) {
      std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      std::cout << tree.GetSum(x1, y1, z1, x2, y2, z2) << '\n';
    }
  }
  return 0;
}
