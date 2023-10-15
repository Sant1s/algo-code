#include <iostream>
#include <vector>

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class Graph {
 public:
  explicit Graph(const std::vector<std::vector<VType>>& graph_matrix)
      : graph_(graph_matrix) {}

  void TransitiveClosure(std::vector<std::vector<VType>>& answer, VType vertex,
                         VType parent) {
    for (size_t iter = 0; iter < graph_.size(); ++iter) {
      if (graph_[vertex][iter] == 0) {
        continue;
      }
      if (answer[parent][iter] == 0) {
        answer[parent][iter] = 1;
        TransitiveClosure(answer, iter, parent);
      }
    }
  }
  size_t GetSize() { return graph_.size(); }
  VType& Get(size_t index_1, size_t index_2) {
    return graph_[index_1][index_2];
  }
  ~Graph() = default;

 private:
  std::vector<std::vector<VType>> graph_;
};

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
struct Solution {
  Solution(Graph<VType>& graph) {
    std::vector<std::vector<VType>> answer(
        graph.GetSize(), std::vector<VType>(graph.GetSize(), 0));
    for (size_t i = 0; i < graph.GetSize(); ++i) {
      graph.Get(i, i) = 1;
      graph.TransitiveClosure(answer, i, i);
    }
    for (const auto& iter : answer) {
      for (const auto& jter : iter) {
        std::cout << jter << ' ';
      }
      std::cout << '\n';
    }
  }
  ~Solution() = default;
};

int main() {
  size_t vertex_amount = 0;
  std::cin >> vertex_amount;
  std::vector<std::vector<size_t>> adjacency_matrix(
      vertex_amount, std::vector<size_t>(vertex_amount, 0));
  for (auto& iter : adjacency_matrix) {
    for (auto& jter : iter) {
      std::cin >> jter;
    }
  }
  Graph<size_t> graph(adjacency_matrix);
  Solution<size_t> solution(graph);
  return 0;
}
