#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

auto get_lines() -> std::vector<std::string> {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open())
    std::cout << "Error opening file" << std::endl;

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_file, line))
    lines.push_back(line);

  input_file.close();
  return lines;
}

class Timer {
public:
  Timer(){};
  auto start() -> void { m_start = std::chrono::high_resolution_clock::now(); }
  auto stop() -> void { m_end = std::chrono::high_resolution_clock::now(); }

  auto print_all() -> void {
    print_milliseconds();
    print_microseconds();
    print_nanoseconds();
  }

  auto print_milliseconds() -> void {
    print<std::chrono::milliseconds>();
    std::cout << "ms\n";
  }

  auto print_microseconds() -> void {
    print<std::chrono::microseconds>();
    std::cout << "us\n";
  }

  auto print_nanoseconds() -> void {
    print<std::chrono::nanoseconds>();
    std::cout << "ns\n";
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_end;

  template <typename T>
  auto print() -> void {
    auto duration = std::chrono::duration_cast<T>(m_end - m_start);
    std::cout << "Time taken: " << duration.count();
  }

};

struct Tree {
  int height;
  bool visible = false;
};

void print_tree_grid(const std::vector<std::vector<Tree>>& TreeGrid) {
  for (const auto& row : TreeGrid) {
    for (const auto& tree : row) {
      // Change color of visible trees to green, otherwise red.
      if (tree.visible)
        std::cout << "\033[32m";
      else
        std::cout << "\033[31m";
      std::cout << tree.height;
    }
    std::cout << std::endl;
  }
  std::cout << "\033[0m";
}

using TreeRow = std::vector<Tree>;
using TreeGrid = std::vector<TreeRow>;

auto generate_tree_grid(const std::vector<std::string>& lines) -> TreeGrid {
  TreeGrid tree_grid;
  for (const auto& line : lines) {
    TreeRow row;

    for (const auto& c : line)
      row.push_back({ c - '0', false });

    tree_grid.push_back(row);
  }

  return tree_grid;
}

auto count_visible_trees(const TreeGrid& tree_grid) -> std::size_t {
  std::size_t count = 0;
  
  for (const auto& row : tree_grid)
    for (const auto& tree : row)
      if (tree.visible)
        ++count;
  
  return count;
}

auto part_one(const std::vector<std::string>& lines) -> std::size_t {
  TreeGrid tree_grid = generate_tree_grid(lines);

  // Rows
  for (auto& tree_row : tree_grid) {
    // Check from the left to right
    int max_height_this_row = -1;
    for (auto& tree : tree_row) {
      if (tree.height > max_height_this_row) {
        max_height_this_row = tree.height;
        tree.visible = true;
      }
    }

    // Check from the right to left
    max_height_this_row = -1;
    for (int index = tree_row.size() - 1; index >= 0; --index) {
      auto &tree = tree_row[index];
      if (tree.height > max_height_this_row) {
        max_height_this_row = tree.height;
        tree.visible = true;
      }
    }
  }

  // Columns
  for (int index = 0; index < tree_grid[0].size(); ++index) {
    // Check from the top to bottom, vertically
    int max_height_this_column = -1;
    for (auto& tree_row : tree_grid) {
      auto& tree = tree_row[index];
      if (tree.height > max_height_this_column) {
        max_height_this_column = tree.height;
        tree.visible = true;
      }
    }

    // Check from the bottom to top, vertically
    max_height_this_column = -1;
    for (int row_index = tree_grid.size() - 1; row_index >= 0; --row_index) {
      auto& tree_row = tree_grid[row_index];
      auto& tree = tree_row[index];
      if (tree.height > max_height_this_column) {
        max_height_this_column = tree.height;
        tree.visible = true;
      }
    }
  }

  // This is kinda cool: print_treegrid(tree_grid);

  return count_visible_trees(tree_grid);
}

auto part_two(const std::vector<std::string>& lines) -> std::size_t {
  TreeGrid tree_grid = generate_tree_grid(lines);
  // For every tree in the grid, check how many trees are visible from that tree.
  // The tree with the most visible trees is the best view of any tree.
  int best_visible_tree_score = 0;

  for (int tree_row_index = 0; tree_row_index < tree_grid.size(); ++tree_row_index) {
    auto& tree_row = tree_grid[tree_row_index];
    for (int tree_index = 0; tree_index < tree_row.size(); ++tree_index) {

      const auto& tree_with_view = tree_row[tree_index];

      int visible_trees_up = 0;
      int visible_trees_down = 0;
      int visible_trees_left = 0;
      int visible_trees_right = 0;

      // We count how many trees are visible from this tree.
      // Visible trees are trees that are lower than this tree
      // We count visible trees from right, left, up, down,  for trees that are lower than this tree.
      // We stop counting after we find a tree that is higher than this tree.
      
      // Check right
      for (int index = tree_index + 1; index < tree_row.size(); ++index) {
        
        // We increment this no matter what.
        // because even if we get blocked, we can still see the tree that blocks us.
        ++visible_trees_right;

        if (tree_row[index].height >= tree_with_view.height)
          break;
      }

      // Check left
      for (int index = tree_index - 1; index >= 0; --index) {
        ++visible_trees_left;

        if (tree_row[index].height >= tree_with_view.height)
          break;
      }

      // Check up
      for (int which_row_i = tree_row_index - 1; which_row_i >= 0; --which_row_i) {
        ++visible_trees_up;

        if (tree_grid[which_row_i][tree_index].height >= tree_with_view.height)
          break;
      }
      
      // Check down
      for (int which_row_i = tree_row_index + 1; which_row_i < tree_grid.size(); ++which_row_i) {
        ++visible_trees_down;
        
        if (tree_grid[which_row_i][tree_index].height >= tree_with_view.height)
          break;
      }

      int visible_tree_score = visible_trees_up * visible_trees_down * visible_trees_left * visible_trees_right;
      best_visible_tree_score = std::max(best_visible_tree_score, visible_tree_score);

    }
  }

  return best_visible_tree_score;
}

int main() {
  auto lines = get_lines();
  
  Timer part_one_timer;
  part_one_timer.start();
  auto part_one_count = part_one(lines);
  part_one_timer.stop();

  Timer part_two_timer;
  part_two_timer.start();
  auto part_two_bestviewofanytree = part_two(lines);
  part_two_timer.stop();

  std::cout << "Part one: visible trees: " << part_one_count << "\n";
  std::cout << "Part two: best view of any tree: " << part_two_bestviewofanytree << "\n";

  std::cout << "\nPart one time: \n";
  part_one_timer.print_all();

  std::cout << "\nPart two time: \n";
  part_two_timer.print_all();
  return 0;
}