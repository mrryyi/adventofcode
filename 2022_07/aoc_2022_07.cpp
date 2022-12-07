#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

struct file {
  std::string name;
  std::size_t size;
};

struct directory {
  std::string name;
  directory* parent;
  std::vector<directory> subdirectories;
  std::vector<file> files;
};

// For debugging purposes
auto print_directories_recursive_prettyish(const directory& dir, int depth = 0) -> void {
  
  for (int i = 0; i < depth; ++i)
      std::cout << "   ";

  std::cout << dir.name << std::endl;
  
  for (const auto& file : dir.files) {
    for (int i = 0; i < depth; ++i)
      std::cout << "   ";

    std::cout << " - " << file.name << " (file, size=" << file.size << ")" << std::endl;
  }

  depth += 1;
  for (const auto& subdirectory : dir.subdirectories) {
    print_directories_recursive_prettyish(subdirectory, depth);
  }
}

// The total size of those directories are the second parameter as a reference.
// The return value is just for this function to help itself count.
auto add_sizes_of_directories_with_less_than_100000_size(const directory& dir, std::size_t& total_size) -> std::size_t {
  std::size_t size_of_this_directory = 0;

  for (const auto& file : dir.files)
    size_of_this_directory += file.size;
  for (const auto& subdirectory : dir.subdirectories)
    size_of_this_directory += add_sizes_of_directories_with_less_than_100000_size(subdirectory, total_size);
  
  if (size_of_this_directory < 100000)
    total_size += size_of_this_directory;
  return size_of_this_directory;
}

auto string_to_size_t(const std::string& str) -> std::size_t {
  std::size_t size = 0;
  for (const auto& c : str) {
    if (!std::isdigit(c)) {
      std::cout << "Error: " << str << " is not a number" << std::endl;
      return 0;
    }
    size *= 10;
    size += c - '0';
  }
  return size;
}

auto parse(const std::vector<std::string>& lines) -> directory {
  directory root{"/", nullptr, {}, {}};
  root.parent = &root;
  directory* current_directory = &root;
  
  for (const auto& line : lines) {
    std::string buffer;
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    while (std::getline(ss, buffer, ' '))
      tokens.push_back(buffer);
    
    // Ugly nested shit but pulling it out would make it less readable because of pointer stuff.
    if (tokens.at(0) == "$") {
      if (tokens.at(1) == "cd") {
        if(tokens.at(2) == "..")
          current_directory = current_directory->parent;
        else if (tokens.at(2) == "/")
          current_directory = &root;
        else {
          for (auto& subdirectory : current_directory->subdirectories) {
            if (subdirectory.name == tokens.at(2)) {
              current_directory = &subdirectory;
              break;
            }
          }
        }
      }
    }

    else if (tokens.at(0) == "dir") {
      // Directory. Doesn't handle that there can be multiple directories with the same name.
      directory new_directory{ tokens.at(1), current_directory, {}, {} };
      current_directory->subdirectories.push_back(new_directory);
    }
    else {
      // File. Lioesn't handle that there can be multiple files with the same name.
      std::size_t file_size = string_to_size_t(tokens.at(0));
      file new_file{ tokens.at(1), file_size };
      current_directory->files.push_back(new_file);
    }
  }

  return root;
}

auto part_one(const std::vector<std::string>& lines) -> void {
  auto root = parse(lines);
  
  std::size_t total_size = 0;
  add_sizes_of_directories_with_less_than_100000_size(root, total_size);
  std::cout << "Part one: Total size of directories with less than 100000 size: " << total_size << std::endl;
}

auto get_directories (const directory& dir, std::vector<directory>& directories) -> void {
  directories.push_back(dir);
  for (const auto& subdirectory : dir.subdirectories)
    get_directories(subdirectory, directories);
}

auto get_size_of_directory(const directory& dir) -> std::size_t {
  std::size_t size = 0;
  for (const auto& file : dir.files)
    size += file.size;
  for (const auto& subdirectory : dir.subdirectories)
    size += get_size_of_directory(subdirectory);
  return size;
}

auto part_two(const std::vector<std::string>& lines) -> void {
  auto root = parse(lines);

  const std::size_t used_space = get_size_of_directory(root);
  const std::size_t max_space = 70000000;
  const std::size_t required_unused_space = 30000000;
  const std::size_t unused_space = max_space - used_space;
  const std::size_t size_to_free = required_unused_space - unused_space;

  std::vector<directory> directories;
  get_directories(root, directories);

  std::size_t min = used_space;
  std::string name = "";
  for (const auto& directory : directories) {
    std::size_t size = get_size_of_directory(directory);
    if (size < min && size >= size_to_free) {
      name = directory.name;
      min = size;
    }
  }

  std::cout << "Part two: Delete directory: " << name << " with size: " << min << std::endl;
}

auto main() -> main {
  auto lines = get_lines();
  part_one(lines);
  part_two(lines);
  return 0;
}
