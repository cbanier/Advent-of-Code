#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct File {
  std::string filename;
  uint32_t size;

  inline File(const std::string &name, const uint32_t size)
      : filename(name), size(size) {}
};

struct Directory {
  std::string dirname;
  std::vector<File> files;
  std::vector<Directory> subdirectories;
  Directory *parent;

  Directory() = default;
  Directory(const std::string &name) : dirname(name) {}
};

void create_architecture(const std::vector<std::string> &, Directory &);
uint32_t get_dir_size(const Directory &);

/* PART 1 */
uint32_t explore_architecture_part1_rec(const Directory &, uint32_t &);
void explore_architecture_part1(const Directory &);

/* PART 2 */
uint32_t explore_architecture_part2_rec(const Directory &,
                                        std::vector<uint32_t> &);
void explore_architecture_part2(const Directory &);