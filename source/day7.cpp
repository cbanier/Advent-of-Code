#include "day7.hpp"

using namespace std;

void parser(const string& filename, vector<string>& data) {
  ifstream fileInput;
  fileInput.open(filename);

  string current_line;
  /* init data */
  if (fileInput.is_open()) {
    while (getline(fileInput, current_line)) {
      data.push_back(current_line);
    }
  }
  fileInput.close();
}

void create_architecture(const vector<string>& data, Directory& root) {
  root.dirname = "/";
  root.parent = nullptr;

  Directory* current_directory = &root;
  Directory* tmp_parent;

  uint32_t filesize;
  string dirname, filename;
  for (string line : data) {
    if (line.find("$ cd") != string::npos) {      // $ cd <dirname>
      line = line.substr(line.find("cd"));        // remove '$ '
      dirname = line.substr(line.find(" ") + 1);  // remove 'cd '

      if (dirname.find("/") != string::npos) {
        current_directory = &root;
      } else if (dirname.find("..") != string::npos) {
        current_directory = current_directory->parent;
      } else {
        tmp_parent = current_directory;
        current_directory->subdirectories.push_back(Directory(dirname));
        current_directory = &current_directory->subdirectories.back();
        current_directory->parent = tmp_parent;
      }
    } else if (line.find("$ ls") != string::npos ||
               line.find("dir") != string::npos) {  // $ ls <dirname> or
                                                    // dir <dirname>
      continue;                                     // nothing to do here
    } else {                                        // <size><space><filename>
      filesize = stoi(line.substr(0, line.find(" ")));
      filename = line.substr(line.find(" ") + 1);
      current_directory->files.push_back(File(filename, filesize));
    }
  }
}

uint32_t get_dir_size(const Directory& root) {
  uint32_t total_size = 0;
  for (const File& file : root.files) {
    total_size += file.size;
  }
  for (const Directory& subdir : root.subdirectories) {
    total_size += get_dir_size(subdir);
  }
  return total_size;
}

/* ***************************************************************** */
/* *                            PART 1                             * */
/* ***************************************************************** */
uint32_t explore_architecture_part1_rec(const Directory& root,
                                        uint32_t& sum_of_sizes) {
  uint32_t total_size = 0;
  for (const File& file : root.files) {
    total_size += file.size;
  }
  for (const Directory& subdir : root.subdirectories) {
    total_size += explore_architecture_part1_rec(subdir, sum_of_sizes);
  }
  if (total_size <= 100000) sum_of_sizes += total_size;

  return total_size;
}

void explore_architecture_part1(const Directory& root) {
  uint32_t sum_of_sizes = 0;
  explore_architecture_part1_rec(root, sum_of_sizes);
  cout << "\nPart 1 : " << sum_of_sizes << endl;
}

/* ***************************************************************** */
/* *                            PART 2                             * */
/* ***************************************************************** */
uint32_t explore_architecture_part2_rec(const Directory& root,
                                        vector<uint32_t>& all_sizes) {
  uint32_t total_size = 0;
  for (const File& file : root.files) {
    total_size += file.size;
  }
  for (const Directory& subdir : root.subdirectories) {
    total_size += explore_architecture_part2_rec(subdir, all_sizes);
  }
  all_sizes.push_back(total_size);

  return total_size;
}

void explore_architecture_part2(const Directory& root) {
  uint32_t available_space = (70000000 - get_dir_size(root));
  vector<uint32_t> size_of_each_dir({});
  explore_architecture_part2_rec(root, size_of_each_dir);

  sort(size_of_each_dir.begin(), size_of_each_dir.end());

  for (const uint32_t dir_size : size_of_each_dir) {
    if (available_space + dir_size >= 30000000) {
      cout << "\nPart 2 : " << dir_size << endl;
      break;
    }
  }
}

int main() {
  vector<string> data{};
  parser("../../data/day7.txt", data);

  Directory tree;
  create_architecture(data, tree);
  /* PART 1 */
  explore_architecture_part1(tree);

  /* PART 2 */
  explore_architecture_part2(tree);

  return EXIT_SUCCESS;
}