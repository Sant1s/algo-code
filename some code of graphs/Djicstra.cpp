// 83038298

#include <iostream>
#include <queue>
#include <set>
#include <vector>

template <typename Vertex = size_t, typename Weight = size_t>
struct Node {
  Vertex first;
  Vertex second;
  Weight weight;
  Node() = default;
  Node(Vertex vertex_1, Vertex vertex_2, Weight weight)
      : first(vertex_1), second(vertex_2), weight(weight) {}
};

template <typename Vertex = size_t, typename Edge = Node<Vertex>>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;
  AbstractGraph(size_t vertexes_number, size_t edges_number)
      : kVertexAmount(vertexes_number), kEdgesAmount(edges_number) {}
  size_t GetVertexesAmount() const { return kVertexAmount; }
  size_t GetEdgesAmount() const { return kEdgesAmount; }
  virtual std::vector<std::pair<Vertex, size_t>> GetNeighbour(
      Vertex vertex) = 0;
  virtual ~AbstractGraph() = default;

 private:
  const size_t kVertexAmount = 0;
  const size_t kEdgesAmount = 0;
};

template <typename Vertex = size_t, typename Weight = size_t,
          typename Edge = Node<Vertex, Weight>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertex_number, std::vector<Edge>& edeges)
      : AbstractGraph<Vertex, Edge>(vertex_number, edeges.size()) {
    adjacency_list_.resize(vertex_number);
    for (const auto& iter : edeges) {
      adjacency_list_[iter.first].emplace_back(iter.second, iter.weight);
      adjacency_list_[iter.second].emplace_back(iter.first, iter.weight);
    }
  }
  std::vector<std::pair<Vertex, Weight>> GetNeighbour(Vertex vertex) override {
    return adjacency_list_[vertex];
  }

  size_t GetVertexAmount() { return adjacency_list_.size(); }

 private:
  std::vector<std::vector<std::pair<Vertex, Weight>>> adjacency_list_;
};

template <typename Vertex = size_t, typename Weight = size_t,
          typename Edge = Node<Vertex, Weight>>
struct AbstractVisitor {
  virtual std::pair<Vertex, Weight>& GetVertexParent(Vertex vertex) = 0;
  virtual void AddParent(Vertex vertex, Vertex parent) = 0;
  virtual ~AbstractVisitor() = default;
};

template <typename Vertex = size_t, typename Weight = size_t,
          typename Edge = Node<Vertex, Weight>>
class DijkstraVisitor : public AbstractVisitor<Vertex, Weight, Edge> {
 public:
  DijkstraVisitor(size_t size) { visitor_.resize(size); }
  std::pair<Vertex, Weight>& GetVertexParent(Vertex vertex) final {
    return visitor_[vertex];
  }
  void AddParent(Vertex vertex, Vertex parent) final {
    visitor_[vertex].first = parent;
  }
  void AddPath(Vertex vertex, Weight weight) {
    visitor_[vertex].second = weight;
  }
  ~DijkstraVisitor() override = default;

 private:
  std::vector<std::pair<Vertex, Weight>> visitor_;
};

template <typename Vertex = size_t, typename Weight = size_t,
          typename Edge = Node<Vertex, Weight>,
          typename Graph = AdjacencyListGraph<Vertex, Weight, Edge>,
          typename Visitor = DijkstraVisitor<Vertex, Edge>>
std::vector<size_t> Dijkstra(Graph& graph, Visitor& visitor,
                             Vertex vertex_from) {
  const size_t kNumber = 2009000999;
  std::vector<size_t> dist(graph.GetVertexAmount(), kNumber);
  std::set<std::pair<size_t, Vertex>> queue;
  dist[vertex_from] = 0;
  queue.emplace(0, vertex_from);
  Vertex current;
  while (!queue.empty()) {
    current = queue.begin()->second;
    queue.erase(queue.begin());
    for (auto& iter : graph.GetNeighbour(current)) {
      if (dist[iter.first] > dist[current] + iter.second) {
        queue.erase({dist[iter.first], iter.first});
        dist[iter.first] = dist[current] + iter.second;
        visitor.AddParent(iter.first, current);
        visitor.AddPath(iter.first, dist[iter.first]);
        queue.emplace(dist[iter.first], iter.first);
      }
    }
  }
  return dist;
}

int main() {
  size_t cards_number = 0;
  std::cin >> cards_number;
  size_t vertex_1 = 0;
  size_t vertex_2 = 0;
  size_t weight = 0;
  size_t vertex_from = 0;
  size_t vertex_num = 0;
  size_t edges_num = 0;
  for (size_t i = 0; i < cards_number; ++i) {
    std::cin >> vertex_num >> edges_num;
    std::vector<Node<size_t>> edges;
    for (size_t j = 0; j < edges_num; ++j) {
      std::cin >> vertex_1 >> vertex_2 >> weight;
      edges.emplace_back(vertex_1, vertex_2, weight);
    }
    AdjacencyListGraph<size_t> graph(vertex_num, edges);
    std::cin >> vertex_from;
    DijkstraVisitor<size_t> visitor(graph.GetVertexesAmount());
    std::vector<size_t> answer = Dijkstra(graph, visitor, vertex_from);
    for (const auto& iter : answer) {
      std::cout << iter << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
