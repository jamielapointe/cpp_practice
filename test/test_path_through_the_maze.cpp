
#include <gtest/gtest.h>

#include "cpp_practice/graphs/path_through_the_maze.h"

using cpp_practice::graphs::path_through_the_maze;

// NOLINTBEGIN(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)

/*
Example 1:
  #######
  # F   #
  ###  ##
  #     #
  # #  ##
  # # S #
  #######

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]],
start = [4,3], finish = [0,1] Output: "lul"
*/

TEST(PathThroughTheMazeTest, Test00) {
  std::vector<std::vector<int>> maze = {
      {0, 0, 0, 0, 0}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0},
      {0, 1, 0, 0, 1}, {0, 1, 0, 0, 0},
  };
  std::vector<int> start = {4, 3};
  std::vector<int> finish = {0, 1};
  std::string expected = "lul";
  std::string result = path_through_the_maze(maze, start, finish);
  EXPECT_EQ(result, expected);
}

/*
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
Output = "rrrrrrrr"
*/
TEST(PathThroughTheMazeTest, Test01) {
  std::vector<std::vector<int>> maze = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 0
      {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},  // 1
      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0},  // 2
      {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},  // 3
      {0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0},  // 4
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},  // 5
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},  // 6
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 7
  };
  std::vector<int> start = {6, 2};
  std::vector<int> finish = {6, 10};
  std::string expected = "rrrrrrrr";
  std::string result = path_through_the_maze(maze, start, finish);
  EXPECT_EQ(result, expected);
}

// NOLINTEND(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)
