#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

struct Hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

struct Edge {
  size_t vertex_from;
  size_t vertex_to;
  int64_t capacity;
  Edge(size_t v_from, size_t v_to, int64_t cap)
      : vertex_from(v_from), vertex_to(v_to), capacity(cap) {}
};

class Graph {
 public:
  Graph(size_t vertex_number, size_t edges_number) {
    adj_list_.resize(vertex_number);
    dist_.resize(vertex_number, INT64_MAX);
    ptr_.resize(vertex_number, 0);
    size_t vertex_fr = 0;
    size_t vertex_to = 0;
    int64_t capacity = 0;
    for (size_t i = 0; i < edges_number; ++i) {
      std::cin >> vertex_fr >> vertex_to >> capacity;
      edges_list_.emplace_back(vertex_fr - 1, vertex_to - 1, capacity);
      if (adj_list_[vertex_fr - 1].contains(vertex_to - 1)) {
        adj_list_[vertex_fr - 1].at(vertex_to - 1).second += capacity;
        continue;
      }
      adj_list_[vertex_fr - 1].insert(
          std::make_pair(vertex_to - 1, std::make_pair(0, capacity)));
      adj_list_[vertex_to - 1].insert(
          std::make_pair(vertex_fr - 1, std::make_pair(0, 0)));
    }
  }

  std::vector<std::unordered_map<size_t, std::pair<int64_t, int64_t>>>&
  GetAdjList() {
    return adj_list_;
  }

  std::vector<Edge>& GetEdgesList() { return edges_list_; }

  bool BFS(size_t vertex_from, size_t vertex_to) {
    dist_.assign(dist_.size(), INT64_MAX);
    dist_[vertex_from] = 0;
    std::queue<size_t> bfs_queue;
    bfs_queue.push(vertex_from);
    size_t current = 0;
    while (!bfs_queue.empty()) {
      current = bfs_queue.front();
      bfs_queue.pop();
      for (const auto& iter : adj_list_[current]) {
        if (iter.second.first < iter.second.second &&
            dist_[iter.first] == INT64_MAX) {
          dist_[iter.first] = dist_[current] + 1;
          bfs_queue.push(iter.first);
        }
      }
    }
    return dist_[vertex_to] != INT64_MAX;
  }

  int64_t DFS(size_t vertex_from, size_t vertex_to, int64_t min_cap) {
    if (vertex_to == vertex_from || min_cap == 0) {
      return min_cap;
    }
    for (size_t iter = ptr_[vertex_from]; iter < adj_list_.size(); ++iter) {
      int64_t delta = 0;
      if (dist_[iter] == dist_[vertex_from] + 1) {
        delta = DFS(iter, vertex_to,
                    std::min(min_cap, adj_list_[vertex_from][iter].second -
                                          adj_list_[vertex_from][iter].first));
        if (delta != 0) {
          adj_list_[vertex_from][iter].first += delta;
          adj_list_[iter][vertex_from].first -= delta;
          return delta;
        }
      }
      ++ptr_[vertex_from];
    }
    return 0;
  }

  int64_t Dinic(size_t vertex_from, size_t vertex_to) {
    int64_t max_flow = 0;
    int64_t current_flow = 0;
    while (BFS(vertex_from, vertex_to)) {
      ptr_.assign(adj_list_.size(), 0);
      current_flow = DFS(vertex_from, vertex_to, INT64_MAX);
      while (current_flow != 0) {
        max_flow += current_flow;
        current_flow = DFS(vertex_from, vertex_to, INT64_MAX);
      }
    }
    return max_flow;
  }

 private:
  std::vector<std::unordered_map<size_t, std::pair<int64_t, int64_t>>>
      adj_list_;
  std::vector<Edge> edges_list_;
  std::vector<int64_t> dist_;
  std::vector<size_t> ptr_;
};

struct Solution {
  static void Answer() {
    size_t vertex_amount = 0;
    size_t edges_amount = 0;
    std::cin >> vertex_amount >> edges_amount;
    Graph graph(vertex_amount, edges_amount);

    std::cout << graph.Dinic(0, vertex_amount - 1) << '\n';

    for (const auto& iter : graph.GetEdgesList()) {
      if (graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first < 0) {
        std::cout << 0 << '\n';
        continue;
      }
      if (graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first >
          iter.capacity) {
        std::cout << iter.capacity << '\n';
        graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first -=
            iter.capacity;
        continue;
      }
      if (graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first <=
          iter.capacity) {
        std::cout
            << graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first
            << '\n';
        graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first = 0;
        continue;
      }
      std::cout << graph.GetAdjList()[iter.vertex_from].at(iter.vertex_to).first
                << '\n';
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solution::Answer();
  return 0;
}
