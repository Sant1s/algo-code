//  82529171

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>>
class AbstractGraph {
 public:
  using Vertex = VertexType;
  using Edge = EdgeType;

  AbstractGraph(size_t vertex_num, size_t edge_num)
      : number_of_vertex_(vertex_num), number_of_edges_(edge_num) {}

  size_t VertexesAmount() { return number_of_vertex_; }

  size_t EdgesAmount() { return number_of_edges_; }

  virtual std::vector<VertexType> GetNeighbour(VertexType vertex) = 0;

 private:
  size_t number_of_vertex_ = 0;
  size_t number_of_edges_ = 0;
};

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>>
class AdjacencyListGraph : public AbstractGraph<VertexType, EdgeType> {
 public:
  AdjacencyListGraph(size_t vertex_num, std::vector<EdgeType>& edges)
      : AbstractGraph<VertexType, EdgeType>(vertex_num, edges.size()) {
    graph_.resize(vertex_num);
    for (size_t i = 0; i < edges.size(); ++i) {
      graph_[edges[i].first].push_back(edges[i].second);
      graph_[edges[i].second].push_back(edges[i].first);
    }
  }

  std::vector<VertexType> GetNeighbour(VertexType vertex) override {
    return graph_[vertex];
  }

 private:
  std::vector<std::vector<VertexType>> graph_;
};

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>>
class AdjacencyMatrixGraph : public AbstractGraph<VertexType, EdgeType> {
 public:
  AdjacencyMatrixGraph(size_t vertex_number, std::vector<EdgeType>& edges) {
    graph_.resize(vertex_number, std::vector<VertexType>(vertex_number, 0));
    for (const auto& iter : edges) {
      graph_[iter.first][iter.second] = 1;
    }
  }
  std::vector<VertexType> GetNeighbour(VertexType vertex) final {
    std::vector<VertexType> ret_value;
    for (size_t i = 0; i < graph_[vertex].size(); ++i) {
      if (graph_[vertex][i] == 1) {
        ret_value.push_back(i);
      }
    }
    return ret_value;
  }

 private:
  std::vector<std::vector<VertexType>> graph_;
};

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>>
class AbstractVisitor {
 public:
  virtual VertexType& GetVertexParent(VertexType vertex) = 0;
  virtual void AddParent(VertexType vertex, VertexType parent) = 0;
  virtual ~AbstractVisitor() = default;
};

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>>
class BFSVisitor : public AbstractVisitor<VertexType, EdgeType> {
 public:
  BFSVisitor(size_t size) { visitor_.resize(size); }
  VertexType& GetVertexParent(VertexType vertex) final {
    return visitor_[vertex];
  }

  void AddParent(VertexType vertex, VertexType parent) final {
    visitor_[vertex] = parent;
  }

 private:
  std::vector<VertexType> visitor_;
};

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>,
          class Visitor = BFSVisitor<VertexType, EdgeType>>
std::vector<int64_t> BFS(AdjacencyListGraph<VertexType, EdgeType>& graph,
                         Visitor& visitor, VertexType vertex_from) {
  std::queue<VertexType> bfs_queue;
  std::vector<int64_t> dist(graph.VertexesAmount(), -1);
  bfs_queue.push(vertex_from);
  dist[vertex_from] = 0;
  VertexType current;
  while (!bfs_queue.empty()) {
    current = bfs_queue.front();
    bfs_queue.pop();
    for (const auto& iter : graph.GetNeighbour(current)) {
      if (dist[iter] == -1) {
        visitor.AddParent(iter, current);
        bfs_queue.push(iter);
        dist[iter] = dist[current] + 1;
      }
    }
  }
  return dist;
}

template <typename VertexType = size_t,
          typename EdgeType = std::pair<VertexType, VertexType>,
          class Visitor = BFSVisitor<VertexType, EdgeType>>
void Solution(AdjacencyListGraph<VertexType, EdgeType>& graph, Visitor& visitor,
              VertexType vertex_from, VertexType vertex_to) {
  if (vertex_to == vertex_from) {
    std::cout << 0 << '\n' << vertex_from + 1;
  } else {
    std::vector<int64_t> distance = BFS(graph, visitor, vertex_from);
    if (distance[vertex_to] == -1) {
      std::cout << distance[vertex_to];
    } else {
      std::cout << distance[vertex_to] << '\n';
      std::vector<VertexType> answer;
      answer.push_back(vertex_to);
      VertexType tmp = visitor.GetVertexParent(vertex_to);
      while (tmp != vertex_from) {
        answer.push_back(tmp);
        tmp = visitor.GetVertexParent(tmp);
      }
      answer.push_back(vertex_from);
      std::reverse(answer.begin(), answer.end());
      for (const auto& iter : answer) {
        std::cout << iter + 1 << ' ';
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_of_vertex = 0;
  size_t number_of_edges = 0;
  int64_t vertex_from = 0;
  int64_t vertex_to = 0;
  std::cin >> number_of_vertex >> number_of_edges;
  std::cin >> vertex_from >> vertex_to;
  std::vector<std::pair<int64_t, int64_t>> edges;
  size_t vertex_1 = 0;
  size_t vertex_2 = 0;
  for (size_t i = 0; i < number_of_edges; ++i) {
    std::cin >> vertex_1 >> vertex_2;
    edges.emplace_back(vertex_1 - 1, vertex_2 - 1);
  }
  AdjacencyListGraph<int64_t, std::pair<int64_t, int64_t>> graph(
      number_of_vertex, edges);
  BFSVisitor<int64_t> visitor(number_of_vertex);
  Solution<int64_t>(graph, visitor, vertex_from - 1, vertex_to - 1);
  return 0;
}
