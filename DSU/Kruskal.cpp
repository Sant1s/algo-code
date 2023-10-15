// 84220092

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

template <typename VertexType, typename WeightType>
struct Edge {
  VertexType vertex_from = 0;
  VertexType vertex_to = 0;
  WeightType weight = 0;
  Edge() = default;
  Edge(VertexType ver_from, VertexType ver_to, WeightType edge_w)
      : vertex_from(ver_from), vertex_to(ver_to), weight(edge_w) {}
};

template <typename VertexType, typename WeightType>
class AbstractGraph {
 public:
  AbstractGraph(size_t vertex_num, size_t edge_num)
      : vertex_number_(vertex_num), edge_number_(edge_num) {}
  size_t GetVertexNumber() const { return vertex_number_; }
  size_t GetEdgeNumber() const { return edge_number_; }

 private:
  size_t vertex_number_ = 0;
  size_t edge_number_ = 0;
};

template <typename VertexType, typename WeightType>
class AdjListGraph : public AbstractGraph<VertexType, WeightType> {
 public:
  AdjListGraph(size_t vertex_number,
               std::vector<Edge<VertexType, WeightType>>& edges)
      : AbstractGraph<VertexType, WeightType>(vertex_number, edges.size()),
        adj_list_(edges) {
    graph_.resize(vertex_number);
    for (const auto& iter : edges) {
      graph_[iter.vertex_from].emplace_back(iter.vertex_to, iter.weight);
    }
  }
  std::vector<std::pair<VertexType, WeightType>> GetNeighbours(
      VertexType vertex) const {
    return graph_[vertex];
  }
  const std::vector<Edge<VertexType, WeightType>>& GetAdjList() const {
    return adj_list_;
  }

 private:
  std::vector<Edge<VertexType, WeightType>> adj_list_;
  std::vector<std::vector<std::pair<VertexType, WeightType>>> graph_;
};

template <typename VertexType, typename WeightType>
class DSU {
 public:
  void Unite(Edge<VertexType, WeightType> iter) {
    iter.vertex_from = FindLeader(iter.vertex_from);
    iter.vertex_to = FindLeader(iter.vertex_to);
    if (iter.vertex_from == iter.vertex_to) {
      return;
    }
    if (ranks_[iter.vertex_to] > ranks_[iter.vertex_from]) {
      std::swap(iter.vertex_from, iter.vertex_to);
    }
    ranks_[iter.vertex_to] += ranks_[iter.vertex_from];
    parents_[iter.vertex_from] = iter.vertex_to;
    weight_ += iter.weight;
  }

  DSU(VertexType elem) {
    parents_.resize(elem);
    ranks_.resize(elem);
    for (size_t i = 0; i < elem; ++i) {
      parents_[i] = i;
      ranks_[i] = 1;
    }
  }
  int FindLeader(VertexType elem) {
    if (parents_[elem] == elem) {
      return elem;
    }
    return FindLeader(parents_[elem]);
  }
  WeightType GetWeight() { return weight_; }

 private:
  std::vector<VertexType> parents_;
  std::vector<VertexType> ranks_;
  WeightType weight_ = 0;
};

template <typename VertexType, typename WeightType>
void KruskalAlgorithm(AdjListGraph<VertexType, WeightType>& edges,
                      DSU<VertexType, WeightType>& dsu) {
  std::vector<Edge<VertexType, WeightType>> curr = edges.GetAdjList();
  sort(curr.begin(), curr.end(),
       [](Edge<VertexType, WeightType> first,
          Edge<VertexType, WeightType> second) {
         return first.weight < second.weight;
       });
  for (const auto& iter : curr) {
    if (dsu.FindLeader(iter.vertex_from) != dsu.FindLeader(iter.vertex_to)) {
      dsu.Unite(iter);
    }
  }
}

template <typename VertexType, typename WeightType>
WeightType PrimoAlgorithm(AdjListGraph<VertexType, WeightType>& graph) {
  std::set<std::pair<WeightType, VertexType>> cur_set;
  std::vector<WeightType> distance;
  VertexType vertex = 0;
  VertexType vertex_curr;
  WeightType weight;
  while (!cur_set.empty()) {
    vertex = cur_set.begin()->second;
    cur_set.erase(cur_set.begin());
    for (const auto& edge : graph.GetNeighbours(vertex)) {
      if (edge.second < distance[edge.first]) {
        cur_set.erase({distance[edge.first], edge.first});
        distance[edge.first] = edge.second;
        cur_set.insert({distance[edge.first], edge.first});
      }
    }
  }
  WeightType answer = 0;
  for (const auto& iter : distance) {
    answer += iter;
  }
  return answer;
}

int main() {
  size_t vertex_num = 0;
  size_t edge_num = 0;
  std::cin >> vertex_num >> edge_num;
  std::vector<Edge<size_t, size_t>> edges;
  size_t ver1 = 0;
  size_t ver2 = 0;
  size_t weight = 0;
  for (size_t i = 0; i < edge_num; ++i) {
    std::cin >> ver1 >> ver2 >> weight;
    edges.emplace_back(ver1 - 1, ver2 - 1, weight);
    edges.emplace_back(ver2 - 1, ver1 - 1, weight);
  }
  AdjListGraph<size_t, size_t> graph(vertex_num, edges);
  DSU<size_t, size_t> dsu(vertex_num);
  KruskalAlgorithm(graph, dsu);
  std::cout << dsu.GetWeight() << '\n';
  return 0;
}
