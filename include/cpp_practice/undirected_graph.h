///\file undirected_graph.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Compute the BFS for an unordered graph
///\version 0.1
///\date 2023-06-25
///
///\copyright Copyright (c) 2023
///

#pragma once

#include <cstdint>
#include <functional>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <new>
#include <queue>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// #include "cpp_practice/macros.h"
#include "cpp_practice/expects.h"

namespace cpp_practice::algorithms::undirected_graph {

///\brief Represent the Node of a graph
///\tparam NodeValue The type of the Value - must support operator<<
template <typename NodeValue>
struct Node {
  ///\brief The type of the NodeIndex
  using NodeIndex = gsl::index;

  ///\brief \c true if this node has been visited by a search algorithm;
  /// otherwise
  /// \c false
  ///\todo redo this class to remove \c is_visited and use a separate hash set
  /// to keep track of visited nodes in search algorithms.
  bool is_visited{false};

  ///\brief The key id of the Node
  NodeIndex id{0};

  ///\brief The value of the Node
  NodeValue value{};

  ///\brief return the nodes Key which can be hashed
  ///\return NodeIndex
  [[gnu::nothrow]] NodeIndex key() const noexcept { return id; }

  ///\brief return the node as a string
  ///\param node a Node to convert to a string
  ///\return \c std::string
  static std::string to_string(Node const& node) {
    return fmt::format("Node ID: {} = {}", node.id, node.value);
  }

  ///\brief return the node as a string
  ///\return \c std::string
  std::string to_string() const { return Node::to_string(*this); }

  ///\brief output stream operator - puts a string representation of the node
  /// onto the \c std::ostream
  ///\param os an existing \c std::ostream
  ///\param node a node to "print" to the \c std::ostream
  ///\return \c std::ostream& a reference to the \c std::ostream
  friend std::ostream& operator<<(std::ostream& os, Node const& node) {
    os << to_string(node);
    return os;
  }

  ///\brief equality operator for two Node types
  ///
  ///\param rhs Node
  ///\param lhs Node
  ///\return true if the nodes are equal
  ///\return false if the nodes are not equal
  friend bool operator==(Node const& rhs, Node const& lhs) {
    return rhs.id == lhs.id;
  }

  ///\brief inequality operator for two Node types
  ///
  ///\param rhs Node
  ///\param lhs Node
  ///\return true if the nodes are not equal
  ///\return false if the nodes are equal
  friend bool operator!=(Node const& rhs, Node const& lhs) {
    return rhs.id != lhs.id;
  }
};

///\brief Representation of an edge of a graph
/// An Edge connects exactly two Node types of a graph.  The Edge object stores
/// a pointer to the node rather than the node itself so that we can easily
/// reference the original object when we need to set the is_visited flag on it.
///\tparam NodeValue_T The value type of a Node
///\tparam CostType_t The cost type for the edge cost - expected to be some kind
/// of numeric type
template <typename NodeValue_T, typename CostType_T>
struct Edge {
  ///\brief The type of the NodeValue
  using NodeValue = NodeValue_T;
  ///\brief The type of the cost of the edge
  using CostType = CostType_T;
  ///\brief The type of the Node
  using Node_T = Node<NodeValue>;
  ///\brief The type of the NodeIndex
  using NodeIndex = typename Node_T::NodeIndex;

  ///\brief The head Node index of the edge on one side of the edge
  NodeIndex head_node_index{0};

  ///\brief The pointer to the tail Node on the other side of the edge
  NodeIndex tail_node_index{0};

  ///\brief The cost of this edge
  CostType cost{0};
};

///\brief Represent distance from a Node to another Node
/// This implements a strongly ordered data structure for use in a priority
/// queue.  The distance is the cost of the edge from the Node to another Node.
///\tparam NodeValue_T Data structure representing the Node value
///\tparam CostType_T Data structure representing the cost type of the edge
template <typename NodeValue_T, typename CostType_T>
struct VertexDistance_T {
  ///\brief The type of the NodeValue
  using NodeValue = NodeValue_T;
  ///\brief The type of the cost of the edge
  using CostType = CostType_T;
  ///\brief The type of the Node
  using Edge_T = Edge<NodeValue, CostType>;
  ///\brief The type of the Node
  using NodeIndex = typename Edge_T::NodeIndex;

  ///\brief The index of the Node
  NodeIndex node_index{0};
  ///\brief The distance from the Node to another Node
  CostType distance{0};

  ///\brief Compare two VertexDistance_T objects
  ///\details This is used by the priority queue to order the elements in the
  /// queue.  The priority queue will place the element with the greatest
  /// distance at the top of the queue.  If there is a tie in distance, then
  /// the element with the greatest node index will be placed at the top of the
  /// queue.
  ///\param other The other VertexDistance_T object to compare to
  ///\return 0 if the two objects are equal, -1 if this object is less than the,
  /// and 1 if this object is greater than the other object
  auto operator<=>(VertexDistance_T const& other) const {
    return (other.distance == distance && other.node_index == node_index)
               ? 0
               : (other.distance < distance
                      ? -1
                      : (distance < other.distance
                             ? 1
                             : (other.node_index < node_index ? -1 : 1)));
  }
  ///\brief Equality operator for two VertexDistance_T objects
  /// The equality operator is specified in conjunction with the spaceship
  /// operator as an optimization for the compiler
  ///\param other The other VertexDistance_T object to compare to
  ///\return true if the two objects are equal; otherwise false
  auto operator==(VertexDistance_T const& other) const {
    return other.distance == distance && other.node_index == node_index;
  }
};  // namespace cpp_practice::algorithms::undirected_graph

///\brief An undirected graph
/// In an undirected graph an edge does not have direction.  To compensate for
/// this, when we add an edge we add its mirror copy.  For example, if adding
/// and edge between two nodes A and B, then we have edge 1 from from A to B and
/// then its opposite copy, edge 2 going from B to A.
///\tparam NodeValue_T The value stored in a Node
///\tparam CostType_T The type of the cost of an Edge
template <typename NodeValue_T, typename CostType_T>
class UndirectedGraph {
 public:
  ///\brief The type of the NodeValue
  using NodeValue = NodeValue_T;
  ///\brief The type of the cost of the edge
  using CostType = CostType_T;
  ///\brief The type of the Node
  using Edge_T = Edge<NodeValue, CostType>;
  ///\brief The type of the Node
  using Node = typename Edge_T::Node_T;
  ///\brief The type of the NodeIndex
  using NodeIndex = typename Edge_T::NodeIndex;
  ///\brief The type of the EdgeList
  using EdgeList = std::vector<Edge_T>;
  ///\brief The type of the NodeAdjacencyMap
  using NodeAdjacencyMap = std::unordered_map<NodeIndex, EdgeList>;
  ///\brief The type of the NodeMap
  using NodeMap = std::unordered_map<NodeIndex, Node>;
  ///\brief The type of the EdgeListIterator
  using EdgeListIterator = typename EdgeList::iterator;
  ///\brief The type of the EdgeListConstIterator
  using NodeDistanceMap = std::unordered_map<NodeIndex, CostType>;
  ///\brief The type of the VertexDistance
  using VertexDistance = VertexDistance_T<NodeValue, CostType>;
  ///\brief The type of the VertexDistanceList
  using VertexDistanceList = std::vector<VertexDistance>;
  ///\brief The type of the NodePriorityQueue
  using NodePriorityQueue =
      std::priority_queue<VertexDistance, VertexDistanceList,
                          std::greater<VertexDistance>>;

  ///\brief Construct a new Undirected Graph object
  /// Sets the initial size for the number of nodes and number of edges.  For
  /// large graphs, setting the number of nodes and the number of edges first
  /// makes creating the graph much more efficient.
  ///\param num_nodes the initial number of nodes
  ///\param num_edges the initial number of edges
  UndirectedGraph(std::size_t num_nodes, std::size_t num_edges)
      : node_map_(num_nodes), adjacency_map_(num_edges) {}

  ///\brief Construct a new Undirected Graph object
  UndirectedGraph() = default;

  ///\brief return the number of nodes in the graph
  ///\return auto the number of nodes in the graph
  auto number_of_nodes() noexcept { return node_map_.size(); }

  ///\brief return the number of edges in the graph
  ///\return auto the number of edges in the graph
  auto number_of_edges() noexcept { return adjacency_map_.size(); }

  ///\brief Readonly accessor for the adjacency map
  /// The adjacency map maps the key of a Node (NodeIndex) to its
  /// list of directly connected edges.  this is equivalent to an
  /// Adjacency List
  ///\return NodeAdjacencyMap const&
  NodeAdjacencyMap const& adjacency_map() const noexcept {
    return adjacency_map_;
  }

  ///\brief Accessor for the adjacency map
  /// The adjacency map maps the key of a Node (NodeIndex) to its
  /// list of directly connected edges.  this is equivalent to an
  /// Adjacency List
  ///\return NodeAdjacencyMap const&
  NodeAdjacencyMap& adjacency_map() noexcept { return adjacency_map_; }

  ///\brief Readonly accessor for the Node map
  /// The node_map maps the key of a Node (NodeIndex) to the Node it represents
  ///\return NodeMap const&
  NodeMap const& node_map() const noexcept { return node_map_; }

  ///\brief Accessor for the Node map
  /// The node_map maps the key of a Node (NodeIndex) to the Node it represents
  ///\return NodeMap const&
  NodeMap& node_map() noexcept { return node_map_; }

  ///\brief Return the list of Edge objects for a specific node
  /// This will return the list of Edge objects that are directly connected to
  /// the Node represented by the NodeIndex
  ///\param node_index The key of the Node whose Edge objects you want to return
  ///\return EdgeList&
  EdgeList& get_edges(NodeIndex node_index) {
    typename NodeAdjacencyMap::iterator edge_iterator =
        adjacency_map().find(node_index);
    [[likely]] if (edge_iterator != adjacency_map().end()) {
      return edge_iterator->second;
    }
    return empty_edge_list_;
  }

  ///\brief Return the Node from the node index
  ///\param node_index The node index
  ///\return Node const&
  Node& get_node(NodeIndex node_index) {
    auto node_iterator = node_map().find(node_index);
    [[likely]] if (node_iterator != node_map().end()) {
      return node_iterator->second;
    }
    return empty_node_;
  }

  ///\brief Add an Edge to the Graph
  /// Because this is an undirected graph, this will add two edges swapping the
  /// Node for the head_node and tail_node
  ///\param head_node A Node on one of the ends of an Edge
  ///\param tail_node A Node on one of the ends of an Edge
  ///\param edge_cost The optional cost of the Edge - default is 0 or no cost
  ///\note This induces two copies.  Which is fine for small Nodes.  We should
  ///      employ a mechanism to either move or construct in place... similar to
  ///      emplace_back for a std::vector.
  void add_edge(Node head_node, Node tail_node,
                CostType edge_cost = static_cast<CostType>(0)) {
    add_edge(head_node.id, head_node.value, tail_node.id, tail_node.value,
             edge_cost);
  }

  ///\brief Add an edge to the Graph
  /// Because this is an undirected graph, this will add two edges swapping the
  /// Node for the head_node and tail_node.  Head and Tail have no real meaning
  /// for an undirected graph and just mean two ends of an Edge.
  ///\param head_node_index Index of the head Node
  ///\param head_node_value Value of the head Node
  ///\param tail_node_index Index of the tail Node
  ///\param tail_node_value Value of the tail Node
  ///\param edge_cost Cost of the edge
  void add_edge(NodeIndex head_node_index, NodeValue head_node_value,
                NodeIndex tail_node_index, NodeValue tail_node_value,
                CostType edge_cost = static_cast<CostType>(0)) {
    node_map().emplace(head_node_index,
                       Node{false, head_node_index, head_node_value});
    node_map().emplace(tail_node_index,
                       Node{false, tail_node_index, tail_node_value});
    adjacency_map()[head_node_index].emplace_back(
        Edge_T{head_node_index, tail_node_index, edge_cost});
    adjacency_map()[tail_node_index].emplace_back(
        Edge_T{tail_node_index, head_node_index, edge_cost});
  }

  ///\brief Perform the BFS (breadth first search) algorithm on the graph
  ///
  /// In general, this algorithm will terminate when all reachable nodes from
  /// the start_node have been exhausted.  However, a user may pass an optional
  /// callback function that returns a bool.  If this optional callback return
  /// true, then this algorithm will terminate early.  This is useful if you
  /// are searching for a specific Node.  You would naturally want to
  /// terminate the search when the Node has been located.
  ///
  /// This algorithm uses a queue to process the nodes as is an iterative
  /// algorithm.  The algorithm starts with the user provided start node index.
  ///
  ///\param start_node_index the index of the Node to start the BFS algorithm at
  ///\param callback the optional function to call to process each new node
  ///                found in the search.  This function will return a bool
  ///                type.  If the function returns true, then this algorithm is
  ///                terminated early.
  ///
  /// \note The time complexity is O(V + E) where V is the number of vertices
  ///       and E is the number of edges
  /// \note the space complexity is O(V) where V is the number of vertices
  ///
  /// \todo ideally this would be a constant function and not change the state
  /// of the object
  void breadth_first_search(
      NodeIndex start_node_index,
      std::function<bool(Node const&)> callback = nullptr) {
    // "Visit" the start_node and add it to the queue and call the callback if
    // it exists
    auto& start_node = get_node(start_node_index);
    // cannot easily preallocate a queue with a specific size.
    std::queue<NodeIndex> node_queue{};
    start_node.is_visited = true;
    if (callback != nullptr && callback(start_node)) {
      return;
    }
    node_queue.push(start_node.id);
    // process reachable nodes added to the node queue.  We are finished when
    // the node queue is empty
    while (!node_queue.empty()) {
      auto node_index = node_queue.front();
      auto& node_edges = get_edges(node_index);
      node_queue.pop();
      // process unvisited nodes directly reachable (i.e., an edge exists from
      // the current "head node" to the "tail node") from "node".  Process means
      // to call the callback function and add the tail node to the node_queue
      for (auto& node_edge : node_edges) {
        auto& tail_node = get_node(node_edge.tail_node_index);
        if (!tail_node.is_visited) {
          tail_node.is_visited = true;
          if (callback != nullptr && callback(tail_node)) {
            return;
          }
          node_queue.push(tail_node.id);
        }
      }
    }
  }

  ///\brief Perform the DFS (depth first search) algorithm on the graph
  ///
  /// In general, this algorithm will terminate when all reachable nodes from
  /// the start nodes have been exhausted.  However, a user may pass an optional
  /// callback function that returns a bool.  If this optional callback returns
  /// \b true, then this algorithm with terminate early.  This is useful if you
  /// are searching for a specific Node.  You would naturally want to terminate
  /// the search when the Node has been located.
  ///
  /// This algorithms explicitly uses a stack and is an iterative algorithm.  It
  /// stores the edge iterator in the stack and has the same order as the
  /// recursive version of this algorithm.  We use an iterative as opposed to a
  /// recursive algorithm to support very large and deep graphs without worrying
  /// about a stack overflow.  The stack data structure is allocated on the free
  /// store (aka heap or dynamic memory). The algorithm starts with the user
  /// provided start node index.
  ///
  ///\param start_node_index The index of the node to start the DFS algorithm at
  ///\param callback the optional function to call to process each new node
  ///                found in the search.  This function will return a bool
  ///                type.  If the function returns true, then this algorithm is
  ///                terminated early.
  ///
  /// \note The time complexity is O(V + E) where V is the number of vertices
  ///       and E is the number of edges
  /// \note the space complexity is O(E) where E is the number of edges
  ///
  /// \todo ideally this would be a constant function and not change the state
  /// of the object
  void depth_first_search(NodeIndex start_node_index,
                          std::function<bool(Node const&)> callback = nullptr) {
    auto& start_node = get_node(start_node_index);
    start_node.is_visited = true;
    if (callback != nullptr && callback(start_node)) {
      return;
    }
    std::stack<EdgeListIterator> node_stack(
        static_cast<std::size_t>(number_of_edges()));
    node_stack.push(adjacency_map().find(start_node_index));
    // process unvisited nodes directly reachable (i.e., an edge exists from the
    // current "head node" to the "tail node") from "node".  Process means to
    // call the callback function and add the tail node to the node_queue
    while (!node_stack.empty()) {
      auto& current_edge_iterator = node_stack.top();
      if (current_edge_iterator != adjacency_map().end()) {
        auto& current_edge_list = current_edge_iterator->second;
        auto& current_edge = *current_edge_list;
        auto& tail_node = get_node(current_edge.tail_node_index);
        if (tail_node.is_visited) {
          continue;
        }
        tail_node.is_visited = true;
        if (callback != nullptr && callback(tail_node)) {
          return;
        }
        node_stack.push(adjacency_map().find(tail_node.id));
        ++current_edge_iterator;
      } else {
        node_stack.pop();
      }
    }
  }

  /// \brief Perform the Dijkstra's shortest path algorithm on the graph
  ///
  /// This algorithm will compute the shortest path from the start_node to all
  /// other reachable nodes and return the map of node indices and distances
  /// between that node and the start node.  In general, this algorithm will
  /// terminate when all reachable nodes from the start node have been
  /// exhausted. If the optional \c callback returns \c true, then this
  /// algorithm with terminate early.  This is useful if you are searching for a
  /// specific \c Node.  You would naturally want to terminate the search when
  /// that \c Node has been located.
  ///
  /// This implementation of the Dijkstra's shortest path algorithm uses a heap
  /// (priority queue) that places nodes with a greater distance from the start
  /// node at the top of the heap.  This allows us to process the nodes with the
  /// shortest distance from the start node first.  For ties in distance, the
  /// heap will place nodes with a greater index at the top of heap allowing us
  /// to process lower indexed nodes first.
  ///
  /// \param start_node_index the index of the Node to start the Dijkstra's
  ///                         shortest path algorithm at
  /// \param callback the optional function to call to process each new node
  ///                 found in the search.  This function will return a bool
  ///                 type.  If the function returns true, then this algorithm
  ///                 is terminated early.
  ///
  /// \return NodeDistanceMap a map of the distance from the start_node to each
  ///         node index
  ///
  /// \note The time complexity is O(E log V) where V is the number of vertices
  ///       and E is the number of edges
  /// \note The space complexity is O(V) where V is the number of vertices
  ///
  /// \todo ideally this would be a constant function and not change the state
  /// of the object
  NodeDistanceMap dijkstra_shortest_path(
      NodeIndex start_node_index,
      std::function<bool(Node const&)> callback = nullptr) {
    NodeDistanceMap node_distance_map(
        static_cast<std::size_t>(number_of_nodes()),
        std::numeric_limits<CostType>::max());
    auto& start_node = get_node(start_node_index);
    start_node.is_visited = true;
    node_distance_map[start_node.id] = 0;
    if (callback && callback(start_node)) {
      return node_distance_map;
    }
    NodePriorityQueue heap(static_cast<std::size_t>(number_of_nodes()));
    heap.push({.node_index = start_node.id, .distance = 0});
    while (!heap.empty()) {
      auto node_index = heap.top();
      heap.pop();
      for (auto& node_edge : get_edges(node_index)) {
        auto& tail_node = get_node(node_edge.tail_node_index);
        if (!tail_node.is_visited) {
          tail_node.is_visited = true;
          node_distance_map[tail_node.id] =
              node_distance_map[node_index] + node_edge.cost;
          if (callback && callback(tail_node)) {
            return node_distance_map;
          }
          heap.push({.node_index = tail_node.id,
                     .distance = node_distance_map[tail_node.id]});
        }
      }
    }
    return node_distance_map;
  }

 private:
  NodeMap node_map_{};
  NodeAdjacencyMap adjacency_map_{};

  // represent empty objects for the Node and EdgeList
  Node empty_node_{};
  EdgeList empty_edge_list_{};
};

}  // namespace cpp_practice::algorithms::undirected_graph
