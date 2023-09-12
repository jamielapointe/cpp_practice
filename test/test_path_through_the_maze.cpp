
#include <gtest/gtest.h>

#include "cpp_practice/graphs/path_through_the_maze.h"

using cpp_practice::graphs::path_through_the_maze::Maze;
using cpp_practice::graphs::path_through_the_maze::solution;

// NOLINTBEGIN(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)

/*
Example 1:
    0123456
  0 #######
  1 # F   #
  2 ###  ##
  3 #     #
  4 # #  ##
  5 # # S #
  6 #######
*/

TEST(PathThroughTheMazeTest, Test00) {
  Maze::Map maze = {
      // 0  1  2  3  4  5  6
      {0, 0, 0, 0, 0, 0, 0},  // 0
      {0, 1, 1, 1, 1, 1, 1},  // 1
      {0, 0, 0, 1, 1, 0, 0},  // 2
      {0, 1, 1, 1, 1, 1, 0},  // 3
      {0, 1, 0, 1, 1, 0, 0},  // 4
      {0, 1, 0, 1, 1, 1, 0},  // 5
      {0, 0, 0, 0, 0, 0, 0},  // 6
  };
  Maze::Node start = {5, 4};
  Maze::Node finish = {1, 2};
  std::vector<uint8_t> expected = {'l', 'u', 'u', 'u', 'u', 'l'};
  std::vector<uint8_t> result = solution(maze, start, finish);
  EXPECT_EQ(result, expected);
}

/*
Example 2:
 0 ############## 0
 1 #    #  ###### 1
 2 # ##### ##   # 2
 3 #  #######   # 3
 4 ###  #     ### 4
 5 ####### ###### 5
 6 # S       F ## 6
 7 ############## 7
*/
TEST(PathThroughTheMazeTest, Test01) {
  Maze::Map maze = {
      // 0  1  2  3  4  5  6  7  8  9 10 11 12 13
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 0
      {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},  // 1
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0},  // 2
      {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},  // 3
      {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0},  // 4
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},  // 5
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},  // 6
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 7
  };
  Maze::Node start = {6, 2};
  Maze::Node finish = {6, 10};
  std::vector<uint8_t> expected = {'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'};
  std::vector<uint8_t> result = solution(maze, start, finish);
  EXPECT_EQ(result, expected);
}

/*
Example 3:
#########
##S###F##
#########
*/
TEST(PathThroughTheMazeTest, Test02) {
  Maze::Map maze = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  Maze::Node start = {1, 2};
  Maze::Node finish = {1, 6};
  std::vector<uint8_t> expected{};
  std::vector<uint8_t> result = solution(maze, start, finish);
  EXPECT_EQ(result, expected);
}

// NOLINTEND(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)
