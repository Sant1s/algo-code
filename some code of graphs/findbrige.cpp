// 82486444

#include <algorithm>
#include <iostream>
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

  virtual std::vector<std::pair<VertexType, size_t>> GetNeighbour(
      size_t vertex) = 0;

 private:
  size_t number_of_vertex_ = 0;
  size_t number_of_edges_ = 0;
};

template <typename VertexType = size_t,
          typename EdgeType =
              std::pair<VertexType, std::pair<VertexType, size_t>>>
class AdjacencyListGraph : public AbstractGraph<VertexType, EdgeType> {
 public:
  AdjacencyListGraph(size_t vertex_num, std::vector<EdgeType>& edges)
      : AbstractGraph<VertexType, EdgeType>(vertex_num, edges.size()) {
    graph_.resize(vertex_num);
    for (size_t i = 0; i < edges.size(); ++i) {
      graph_[edges[i].first].push_back(edges[i].second);
      graph_[edges[i].second.first].push_back(
          {edges[i].first, edges[i].second.second});
    }
  }

  std::vector<std::pair<VertexType, size_t>> GetNeighbour(
      VertexType vertex) override {
    return graph_[vertex];
  }

 private:
  std::vector<std::vector<std::pair<VertexType, size_t>>> graph_;
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
    return graph_[vertex];
  }

 private:
  std::vector<std::vector<VertexType>> graph_;
};

template <typename VertexType = size_t,
          typename EdgeType =
              std::pair<VertexType, std::pair<VertexType, size_t>>>
class AbstractVisitors {
 public:
  virtual void BridgeFinder(
      VertexType vertex_1, VertexType vertex_2,
      AdjacencyListGraph<VertexType, EdgeType>& graph) = 0;

  virtual ~AbstractVisitors() = default;
};

template <typename VertexType = size_t,
          typename EdgeType =
              std::pair<VertexType, std::pair<VertexType, size_t>>>
class DFSVisitor : public AbstractVisitors<VertexType, EdgeType> {
 public:
  void BridgeFinder(VertexType vertex_1, VertexType vertex_2,
                    AdjacencyListGraph<VertexType, EdgeType>& graph) final {
    for (const auto& iter : graph.GetNeighbour(vertex_1)) {
      if (iter.first == vertex_2) {
        bridges_.push_back(iter.second);
        break;
      }
    }
  }

  std::vector<size_t> GetBridges() { return bridges_; }

 private:
  std::vector<size_t> bridges_;
};

template <
    typename VertexType = size_t,
    typename EdgeType = std::pair<VertexType, std::pair<VertexType, size_t>>>
bool IsMultipleEdge(AdjacencyListGraph<VertexType, EdgeType>& graph,
                    size_t vertex_1, size_t vertex_2);

template <typename VertexType = size_t,
          typename EdgeType =
              std::pair<VertexType, std::pair<VertexType, size_t>>,
          class Visitor = DFSVisitor<VertexType, EdgeType>>
class DFS {
 public:
  DFS(size_t size_of_graph)
      : used_(std::vector<bool>(size_of_graph, false)),
        t_in_(std::vector<size_t>(size_of_graph)),
        t_up_(std::vector<size_t>(size_of_graph)),
        parents_(std::vector<int>(size_of_graph)) {}

  void Dfs(Visitor& visitor, AdjacencyListGraph<VertexType, EdgeType>& graph,
           VertexType vertex, int parent = -1) {
    used_[vertex] = true;
    t_in_[vertex] = t_up_[vertex] = timer_++;
    parents_[vertex] = parent;
    for (const auto& iter : graph.GetNeighbour(vertex)) {
      if ((int)iter.first != parent) {
        if (used_[iter.first]) {
          t_up_[vertex] = std::min(t_up_[vertex], t_in_[iter.first]);
        } else {
          Dfs(visitor, graph, iter.first, vertex);
          t_up_[vertex] = std::min(t_up_[vertex], t_up_[iter.first]);
          if (t_up_[iter.first] > t_in_[vertex]) {
            if (!IsMultipleEdge(graph, vertex, iter.first)) {
              visitor.BridgeFinder(vertex, iter.first, graph);
            }
          }
        }
      }
    }
  }

 private:
  std::vector<bool> used_;
  std::vector<size_t> t_in_;
  std::vector<size_t> t_up_;
  std::vector<int> parents_;
  size_t timer_ = 0;
};

template <typename VertexType = size_t,
          typename EdgeType =
              std::pair<VertexType, std::pair<VertexType, size_t>>,
          class Visitor = DFSVisitor<VertexType, EdgeType>>
class Solution {
 public:
  void Answer(AdjacencyListGraph<VertexType, EdgeType>& graph,
              Visitor& visitor) {
    DFS<VertexType, EdgeType> dfs(graph.VertexesAmount());
    for (size_t i = 0; i < graph.VertexesAmount(); ++i) {
      dfs.Dfs(visitor, graph, i);
    }
    ans_ = visitor.GetBridges();
  }
  ~Solution() = default;
  std::vector<size_t>& GetAns() { return ans_; }

 private:
  std::vector<size_t> ans_;
};

template <typename VertexType, typename EdgeType>
bool IsMultipleEdge(AdjacencyListGraph<VertexType, EdgeType>& graph,
                    size_t vertex_1, size_t vertex_2) {
  int counter = -1;
  for (auto iter : graph.GetNeighbour(vertex_1)) {
    if (iter.first == vertex_2) {
      ++counter;
    }
  }
  return (counter > 0);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t number_of_vertex = 0;
  size_t number_of_edges = 0;
  std::cin >> number_of_vertex >> number_of_edges;
  std::vector<std::pair<size_t, std::pair<size_t, size_t>>> edges;
  size_t vertex_1 = 0;
  size_t vertex_2 = 0;
  for (size_t i = 0; i < number_of_edges; ++i) {
    std::cin >> vertex_1 >> vertex_2;
    edges.push_back({vertex_1 - 1, {vertex_2 - 1, i + 1}});
  }
  AdjacencyListGraph graph(number_of_vertex, edges);
  DFSVisitor<size_t> visitor;
  Solution<size_t> solution;
  solution.Answer(graph, visitor);
  std::cout << solution.GetAns().size() << '\n';
  std::sort(solution.GetAns().begin(), solution.GetAns().end());
  for (const auto& iter : solution.GetAns()) {
    std::cout << iter << '\n';
  }
  return 0;
}
