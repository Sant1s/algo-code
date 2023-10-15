#include <iostream>
#include <unordered_map>
#include <vector>

struct Hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& pair) const {
    return std::hash<T1>()(pair.first) << std::hash<T2>()(pair.second);
  }
};

class Graph {
 public:
  Graph(const size_t kVertexNum, const size_t kEdgesNumber)
      : kVertexAmount(kVertexNum) {
    size_t vrx_from = 0;
    size_t vrx_to = 0;
    int64_t wht = 0;
    for (size_t i = 0; i < kEdgesNumber; ++i) {
      std::cin >> vrx_from >> vrx_to >> wht;
      list_of_edges_.insert({{vrx_from, vrx_to}, {wht, i}});
    }
    parents_.resize(kVertexAmount, std::vector<int64_t>(kVertexAmount));
  }
  std::vector<std::vector<int64_t>> FloydWarshall() {
    std::vector<std::vector<int64_t>> dp_arr(
        kVertexAmount, std::vector<int64_t>(kVertexAmount, 2 * 1e5));
    for (size_t i = 0; i < kVertexAmount; ++i) {
      for (size_t j = 0; j < kVertexAmount; ++j) {
        dp_arr[i][i] = 0;
      }
    }
    for (const auto& iter : list_of_edges_) {
      parents_[iter.first.first - 1][iter.first.second - 1] =
          iter.first.second - 1;
    }
    for (const auto& edge : list_of_edges_) {
      dp_arr[edge.first.first - 1][edge.first.second - 1] =
          -1 * edge.second.first;
    }
    for (size_t k = 0; k < kVertexAmount; ++k) {
      for (size_t u = 0; u < kVertexAmount; ++u) {
        for (size_t v = 0; v < kVertexAmount; ++v) {
          if (dp_arr[u][k] < 2 * 1e5 && dp_arr[k][v] < 2 * 1e5 &&
              dp_arr[k][v] + dp_arr[u][k] < dp_arr[u][v]) {
            dp_arr[u][v] = dp_arr[k][v] + dp_arr[u][k];
            parents_[u][v] = parents_[u][k];
          }
        }
      }
    }
    return dp_arr;
  }

  const std::vector<std::vector<int64_t>>& GetParents() const {
    return parents_;
  }

  const std::unordered_map<std::pair<size_t, size_t>,
                           std::pair<int64_t, size_t>, Hash>&
  GetListOfEdges() const {
    return list_of_edges_;
  }

 private:
  std::unordered_map<std::pair<size_t, size_t>, std::pair<int64_t, size_t>,
                     Hash>
      list_of_edges_;
  std::vector<std::vector<int64_t>> parents_;
  const size_t kVertexAmount;
};

struct Solution {
  Solution() {
    size_t vertex_number = 0;
    size_t edges_number = 0;
    size_t cities_number = 0;
    std::cin >> vertex_number >> edges_number >> cities_number;
    Graph graph(vertex_number, edges_number);
    std::vector<size_t> cities_order(cities_number);
    for (auto& iter : cities_order) {
      std::cin >> iter;
    }
    std::vector<std::vector<int64_t>> dp_floyd = graph.FloydWarshall();
    std::vector<std::vector<int64_t>> next = graph.GetParents();
    size_t curr;
    std::vector<size_t> order_by_vertex;
    for (size_t i = 0; i < cities_number - 1; ++i) {
      for (size_t j = 0; j < vertex_number; ++j) {
        if (dp_floyd[j][j] < 0) {
          if (dp_floyd[cities_order[i] - 1][j] < 2 * 1e5 &&
              dp_floyd[j][cities_order[i + 1] - 1] < 2 * 1e5) {
            std::cout << "infinitely kind" << std::endl;
            return;
          }
        }
      }
      curr = cities_order[i] - 1;
      while (curr != cities_order[i + 1] - 1) {
        order_by_vertex.push_back(curr);
        curr = next[curr][cities_order[i + 1] - 1];
      }
    }
    order_by_vertex.push_back(cities_order.back() - 1);
    std::vector<size_t> answer;
    for (size_t j = 1; j < order_by_vertex.size(); ++j) {
      answer.push_back(
          graph.GetListOfEdges()
              .find({order_by_vertex[j - 1] + 1, order_by_vertex[j] + 1})
              ->second.second +
          1);
    }
    std::cout << answer.size() << '\n';
    for (const auto& iter : answer) {
      std::cout << iter << ' ';
    }
  }
};

int main() {
  Solution solution;
  return 0;
}
