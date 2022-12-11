#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool all_different(vector<char> &vec) {
  for (int i = 0; i < vec.size(); ++i)
    for (int j = i + 1; j < vec.size(); ++j)
      if (vec.at(i) == vec.at(j)) return false;

  return true;
}

void reorganize_vector(vector<char> &vec, const char &new_item) {
  for (int i = 1; i < vec.size(); ++i) {
    vec.at(i - 1) = vec.at(i);
  }
  vec.back() = new_item;
}

void marker_finder(const string &filename, const int &marker_size) {
  ifstream fileInput;
  fileInput.open(filename);

  string line;
  if (fileInput.is_open()) {
    getline(fileInput, line);
  }
  fileInput.close();

  vector<char> tmp(marker_size);

  /* init current tmp vector */
  for (int i = 0; i < marker_size; ++i) {
    tmp.at(i) = line.at(i);
  }

  int position_marker = marker_size - 1;
  while (position_marker < line.size()) {
    if (all_different(tmp)) {
      cout << "Marker position is " << position_marker << endl;
      break;
    } else {
      reorganize_vector(tmp, line[position_marker]);
      ++position_marker;
    }
  }
}

int main() {
  /* PART 1 */
  marker_finder("../../data/day6.txt", 4);

  /* PART 2 */
  marker_finder("../../data/day6.txt", 14);

  return EXIT_SUCCESS;
}