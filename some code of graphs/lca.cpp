#include <iostream>
#include <vector>


class Graph {
public:
  Graph() {
    int vertex_number;
    std::cin >> vertex_number;
    list.resize(vertex_number + 1);
    t_in.resize(vertex_number + 1);
    t_out.resize(vertex_number + 1);
    dp_arr.resize(vertex_number + 1, std::vector<int>(20));
    depth.resize(vertex_number + 1);
    int vertex1;
    int vertex2;
    for (int i = 0; i < vertex_number - 1; ++i) {
      std::cin >> vertex1 >> vertex2;
      list[vertex1].push_back(vertex2);
      list[vertex2].push_back(vertex1);
    }
  }
  void DFS(int vertex, int parent = 1, int dept = 0) {
    t_in[vertex] = ++timer;
    depth[vertex] = dept;
    dp_arr[vertex][0] = parent;
    DoubleUp(vertex);
    for (const auto& iter : list[vertex])
      if (parent != iter)
        DFS(iter, vertex, dept + 1);
    t_out[vertex] = ++timer;
  }

  int LCA(int vertex1, int vertex2) {
    if (AreAncestor(vertex2, vertex1)) return vertex2;
    if (AreAncestor(vertex1, vertex2)) return vertex1;
    for (int i = 19; i >= 0; --i)
      if (!AreAncestor(dp_arr[vertex1][i], vertex2))
        vertex1 = dp_arr[vertex1][i];
    return dp_arr[vertex1][0];
  }

  const std::vector<int>& GetDepth() const {
    return depth;
  }

private:
  void DoubleUp(int vertex) {
    for (int i = 0; i < 20; ++i)
      dp_arr[vertex][i + 1] = dp_arr[dp_arr[vertex][i]][i];
  }
  bool AreAncestor(int vertex1, int vertex2) {
    return t_in[vertex1] <= t_in[vertex2] && t_out[vertex1] >= t_out[vertex2];
  }
  std::vector<std::vector<int>> list;
  std::vector<int> depth;
  std::vector<std::vector<int>> dp_arr;
  std::vector<int> t_in;
  std::vector<int> t_out;
  size_t timer = 0;
};

struct Solution {
  Solution() {
    Graph graph;
    graph.DFS(1);
    int question_number;
    std::cin >> question_number;
    int ancestor;
    int answer;
    int vertex1;
    int vertex2;
    for (size_t i = 0; i < question_number; ++i) {
      std::cin >> vertex1 >> vertex2;
      ancestor = graph.LCA(vertex1, vertex2);
      answer = graph.GetDepth()[vertex1] + graph.GetDepth()[vertex2] - 2 * graph.GetDepth()[ancestor];
      std::cout << answer << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solution solution;
  return 0;
}
