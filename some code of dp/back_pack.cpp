#include <iostream>
#include <vector>

std::vector<size_t> BackPack(const std::vector<size_t>& weight,
                             const std::vector<size_t>& prise,
                             const size_t kMaxW) {
  std::vector<std::vector<size_t>> dp_arr(weight.size() + 1,
                                          std::vector<size_t>(kMaxW + 1, 0));
  std::vector<std::vector<std::vector<size_t>>> ans_arr(
      weight.size() + 1, std::vector<std::vector<size_t>>(kMaxW + 1));
  for (auto& i : ans_arr) {
    for (auto& j : i) {
      j.push_back(0);
    }
  }
  for (size_t i = 0; i <= weight.size(); ++i) {
    for (size_t j = 0; j <= kMaxW; ++j) {
      if (i == 0 || j == 0) {
        dp_arr[i][j] = 0;
        continue;
      }
      if (j >= weight[i - 1]) {
        if (dp_arr[i - 1][j] >
            dp_arr[i - 1][j - weight[i - 1]] + prise[i - 1]) {
          dp_arr[i][j] = dp_arr[i - 1][j];
          ans_arr[i][j] = ans_arr[i - 1][j];
        } else {
          dp_arr[i][j] = dp_arr[i - 1][j - weight[i - 1]] + prise[i - 1];
          ans_arr[i][j] = ans_arr[i - 1][j - weight[i - 1]];
          ans_arr[i][j].push_back(i);
        }
      } else {
        dp_arr[i][j] = dp_arr[i - 1][j];
        ans_arr[i][j] = ans_arr[i - 1][j];
      }
    }
  }
  return ans_arr[weight.size()][kMaxW];
}

int main() {
  size_t size = 0;
  size_t backpack_weight = 0;
  std::cin >> size >> backpack_weight;
  std::vector<size_t> weight(size, 0);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> weight[i];
  }
  std::vector<size_t> price(size, 0);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> price[i];
  }
  std::vector<size_t> dp_ans = BackPack(weight, price, backpack_weight);
  for (size_t i = 1; i < dp_ans.size(); ++i) {
    std::cout << dp_ans[i] << '\n';
  }
  return 0;
}
