#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

const size_t kInf = 1000000;

struct Node {
  size_t vertex_to = 0;
  int flow = 0;
  int capacity = 0;
  Node(size_t vertex, int cap) : vertex_to(vertex), capacity(cap) {}
};

class Graph {
 public:
  Graph(size_t vertex_number,
        std::vector<std::pair<std::pair<size_t, size_t>, int>>& edges) {
    list_.resize(vertex_number);
    for (const auto& iter : edges) {
      if (list_[iter.first.first].contains(iter.first.second)) {
        list_[iter.first.first][iter.first.second].second += iter.second;
        continue;
      }
      list_[iter.first.first][iter.first.second] =
          std::make_pair(0, iter.second);
      list_[iter.first.second][iter.first.first] = std::make_pair(0, 0);
    }
  }
  std::vector<std::unordered_map<size_t, std::pair<int, int>>>& GetList() {
    return list_;
  }

 private:
  std::vector<std::unordered_map<size_t, std::pair<int, int>>> list_;
};

int64_t DFS(Graph& graph, std::vector<bool>& used, size_t vertex_from,
            size_t vertex_to, int min_cap) {
  if (vertex_from == vertex_to) {
    return min_cap;
  }
  if (used[vertex_from]) {
    return 0;
  }
  used[vertex_from] = true;
  for (auto& iter : graph.GetList()[vertex_from]) {
    int64_t delta = 0;
    if (iter.second.second > iter.second.first) {
      delta = DFS(graph, used, iter.first, vertex_to,
                  std::min(min_cap, iter.second.second - iter.second.first));
      if (delta > 0) {
        iter.second.first += delta;
        graph.GetList()[iter.first].at(vertex_from).first -= delta;
        return delta;
      }
    }
  }
  return 0;
}

int64_t FFAlgo(Graph& graph, size_t vertex_from, size_t vertex_to) {
  std::vector<bool> used(graph.GetList().size(), false);
  int64_t max_flow = 0;
  int64_t flow = 0;
  while (true) {
    used = std::vector<bool>(graph.GetList().size(), false);
    flow = DFS(graph, used, vertex_from, vertex_to, kInf);
    if (flow == 0) {
      return max_flow;
    }
    max_flow += flow;
  }
  return 0;
}

struct Solution {
  static void Olution() {
    size_t vertex_number = 0;
    size_t edges_number = 0;
    std::cin >> vertex_number >> edges_number;
    std::vector<std::pair<std::pair<size_t, size_t>, int>> edge(edges_number);
    size_t vertex_from = 0;
    size_t vertex_to = 0;
    int weight = 0;
    for (size_t i = 0; i < edges_number; ++i) {
      std::cin >> vertex_from >> vertex_to >> weight;
      edge[i].first.first = --vertex_from;
      edge[i].first.second = --vertex_to;
      edge[i].second = weight;
    }
    Graph graph(vertex_number, edge);
    int64_t answer = FFAlgo(graph, 0, vertex_number - 1);
    std::cout << answer;
  }
};

int main() {
  Solution::Olution();
  return 0;
}
