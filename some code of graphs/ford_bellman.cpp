#include <iostream>
#include <vector>

class Graph {
 public:
  struct Edge {
    size_t vertex_1;
    size_t vertex_2;
    int64_t weight;
    Edge(size_t one, size_t two, int64_t weight)
        : vertex_1(one), vertex_2(two), weight(weight) {}
  };

  Graph() {
    size_t edges_amount = 0;
    std::cin >> vertex_amount_ >> edges_amount;
    size_t vertex_1 = 0;
    size_t vertex_2 = 0;
    int64_t weight = 0;
    for (size_t i = 0; i < edges_amount; ++i) {
      std::cin >> vertex_1 >> vertex_2 >> weight;
      edges_.emplace_back(vertex_1 - 1, vertex_2 - 1, weight);
    }
  }
  std::vector<int64_t> FordBellman(size_t vertex, size_t vertex_amount) {
    std::vector<int64_t> dp_arr(vertex_amount, kInf);
    dp_arr[vertex] = 0;
    for (size_t i = 0; i < vertex_amount - 1; ++i) {
      for (const auto& edge : edges_) {
        if (dp_arr[edge.vertex_1] < kInf) {
          dp_arr[edge.vertex_2] = std::min(dp_arr[edge.vertex_2],
                                           dp_arr[edge.vertex_1] + edge.weight);
        }
      }
    }
    return dp_arr;
  }
  size_t GetVertexAmount() { return vertex_amount_; }
  ~Graph() = default;

 private:
  std::vector<Edge> edges_;
  const int64_t kInf = INT64_MAX;
  size_t vertex_amount_ = 0;
};

struct Solution {
  Solution() {
    Graph graph;
    std::vector<int64_t> answer = graph.FordBellman(0, graph.GetVertexAmount());
    for (const auto& iter : answer) {
      (iter == INT64_MAX) ? std::cout << 30000 << ' '
                          : std::cout << iter << ' ';
    }
  }
  ~Solution() = default;
};

int main() {
  Solution solution;
  return 0;
}
