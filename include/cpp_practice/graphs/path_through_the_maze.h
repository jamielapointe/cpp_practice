/*

Find a valid path through a maze from start to finish.  The path just has to be
valid. It does not have to be the shortest path.  The maze is represented as a
2D array of 0s and 1s.  0s represent walls and 1s represent open spaces.  The
start and finish are represented as a 2D array of coordinates.  The start
coordinates are the first element and the finish coordinates are the second
element.  The path is represented as a container of characters.  'u' means up,
'd' means down, 'l' means left, and 'r' means right.  The path is valid if it
does not go through any walls and it ends at the finish coordinates.  If there
is no valid path, return an empty vector

You may assume that the borders of the maze are all walls (see examples).

Example 1:
  #######
  # F   #
  ###  ##
  #     #
  # #  ##
  # # S #
  #######

Input: maze = {
      // 0  1  2  3  4  5  6
      {0, 0, 0, 0, 0, 0, 0},  // 0
      {0, 1, 1, 1, 1, 1, 1},  // 1
      {0, 0, 0, 1, 1, 0, 0},  // 2
      {0, 1, 1, 1, 1, 1, 0},  // 3
      {0, 1, 0, 1, 1, 0, 0},  // 4
      {0, 1, 0, 1, 1, 1, 0},  // 5
      {0, 0, 0, 0, 0, 0, 0},  // 6
  };
start = [4,5], finish = [2,1] Output: {'u', 'u', 'u', 'u', 'l', 'l'};

Example 2:
 0 ##############
 1 #    #  ######
 2 # ##### ##   #
 3 #  #######   #
 4 ###  #     ###
 5 ####### ######
 6 # S       F ##
 7 ##############

Input: maze =
[
  [0,0,0,0,0,0,0,0,0,0,0,0,0,0], // 0
  [0,1,1,1,1,0,1,0,0,0,0,0,0,0], // 1
  [0,1,0,0,0,0,0,1,0,0,1,1,1,0], // 2
  [0,1,1,0,0,0,0,0,0,0,1,1,1,0], // 3
  [0,0,0,1,1,0,1,1,1,1,1,0,0,0], // 4
  [0,0,0,0,0,0,0,1,0,0,0,0,0,0], // 5
  [0,1,1,1,1,1,1,1,1,1,1,1,0,0], // 6
  [0,0,0,0,0,0,0,0,0,0,0,0,0,0], // 7
]
start = [6,2], finish=[6,10],
Output = {'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'};

*/

#include <array>
#include <cassert>
#include <cstdint>
#include <deque>
#include <stack>
#include <unordered_map>
#include <vector>

namespace cpp_practice::graphs::path_through_the_maze {

using std::size_t;

class Maze {
 public:
  struct Node {
    int row;
    int col;
    bool operator==(const Node& other) const {
      return row == other.row && col == other.col;
    }
  };
  struct NodeHash {
    size_t operator()(const Node& node) const {
      return std::hash<int>()(node.row) ^ std::hash<int>()(node.col);
    }
  };

  using Map = std::vector<std::vector<int>>;
  using Path = std::unordered_map<Node, Node, NodeHash>;
  using VisitedMap = std::vector<std::vector<int>>;

  Maze(const Map& maze, const Node& start, const Node& finish)
      : maze_(maze),
        width_{static_cast<int>(maze_[0].size())},
        height_{static_cast<int>(maze_.size())},
        start_(start),
        finish_(finish),
        visited_(static_cast<size_t>(height_),
                 std::vector<int>(static_cast<size_t>(width_), 0)) {}

  Path const& paths() const { return path_; }
  bool was_path_found() const { return was_path_found_; }

  void find_paths() {
    // Finds all of the paths from the start to the finish
    // Use BFS to find the shortest path
    // Use a queue to store the nodes to visit
    // Use a matrix (map) to store the visited nodes; the visited map also keeps
    // track of the number of steps to get to each node
    // Use a map to store the path from the tail node to the head node
    // this ends up being one of the shortest paths (if more than oen)
    // from the tail to the head.
    // You can then reverse this to get the path from the head to the tail
    std::deque<Node> node_queue;
    node_queue.emplace_back(start_);
    // mark the started node as visited
    visited_[static_cast<size_t>(start_.row)][static_cast<size_t>(start_.col)] =
        1;
    while (!node_queue.empty()) {
      auto current_node = node_queue.front();
      node_queue.pop_front();
      if (current_node == finish_) {
        was_path_found_ = true;
        return;
      }
      for (auto direction : directions_) {
        Node next_node = {current_node.row + direction.row,
                          current_node.col + direction.col};
        if (is_valid(next_node.row, next_node.col)) {
          mark_visited(next_node.row, next_node.col, current_node.row,
                       current_node.col);
          node_queue.emplace_back(next_node);
          // this is backwards on purpose
          path_.emplace(next_node, current_node);
        }
      }
    }
  }

 private:
  Map maze_;
  int width_{0};
  int height_{0};
  Node start_;
  Node finish_;
  Path path_;
  VisitedMap visited_;
  bool was_path_found_{false};
  static constexpr std::array<Node, 4> directions_ = {
      {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};

  bool is_valid(int row, int col) const {
    return row >= 0 && row < height_ && col >= 0 && col < width_ &&
           maze_[static_cast<size_t>(row)][static_cast<size_t>(col)] == 1 &&
           visited_[static_cast<size_t>(row)][static_cast<size_t>(col)] == 0;
  }

  void mark_visited(int row, int col, int prev_row, int prev_col) {
    visited_[static_cast<size_t>(row)][static_cast<size_t>(col)] =
        visited_[static_cast<size_t>(prev_row)][static_cast<size_t>(prev_col)] +
        1;
  }
};

uint8_t get_direction(int row_dir, int col_dir) {
  if (row_dir == 1) {
    return 'd';
  } else if (row_dir == -1) {
    return 'u';
  } else if (col_dir == 1) {
    return 'r';
  } else if (col_dir == -1) {
    return 'l';
  }
  assert(false);  // raise error
  return ' ';
}

std::vector<uint8_t> solution(const Maze::Map& map, const Maze::Node& start,
                              const Maze::Node& finish) {
  // Search the maze and find the paths
  Maze maze(map, start, finish);
  maze.find_paths();
  if (!maze.was_path_found()) {
    return {};
  }

  // Get the paths (note that this is backwards)
  auto paths = maze.paths();
  std::vector<uint8_t> result;

  // Get the path from the finish to the start and reverse it
  // by storing in a stack and then iterating over the stack to
  // get the proper order from start to finish
  std::stack<Maze::Node> path;
  auto current_node = finish;
  while (current_node != start) {
    path.emplace(current_node);
    current_node = paths[current_node];
  }
  auto previous_node = start;
  while (!path.empty()) {
    current_node = path.top();
    result.emplace_back(get_direction(current_node.row - previous_node.row,
                                      current_node.col - previous_node.col));
    previous_node = current_node;
    path.pop();
  }
  return result;
}

}  // namespace cpp_practice::graphs::path_through_the_maze
