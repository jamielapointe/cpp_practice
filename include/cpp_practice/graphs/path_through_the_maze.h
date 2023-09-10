/*

Find a valid path through a maze from start to finish.  The path just has to be
valid. It does not have to be the shortest path.  The maze is represented as a
2D array of 0s and 1s.  0s represent walls and 1s represent open spaces.  The
start and finish are represented as a 2D array of coordinates.  The start
coordinates are the first element and the finish coordinates are the second
element.  The path is represented as a string of characters.  'u' means up, 'd'
means down, 'l' means left, and 'r' means right.  The path is valid if it does
not go through any walls and it ends at the finish coordinates.  If there is no
valid path, return "impossible".

You may assume that the borders of the maze are all walls (see examples).

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