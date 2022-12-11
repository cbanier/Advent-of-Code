#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/* ***************************************************************** */
/* *                            PART 1                             * */
/* ***************************************************************** */
int score_common_letter(const string& left, const string& right,
                        const map<char, int>& priorities) {
  int score = 0;
  for (char letter : left) {
    if (right.find(letter) != string::npos) {
      score = priorities.at(letter);
      break;
    }
  }
  return score;
}

void rucksack_part1(const string& filename, const map<char, int>& priorities) {
  ifstream fileInput;
  fileInput.open(filename);

  int score = 0;
  if (fileInput.is_open()) {
    int half;
    string current_line;
    string left, right;

    while (getline(fileInput, current_line)) {
      half = current_line.length() / 2;
      left = current_line.substr(0, half);
      right = current_line.substr(half);

      score += score_common_letter(left, right, priorities);
    }
  }
  fileInput.close();
  cout << "\nPart 1\nRucksack score : " << score << endl;
}

/* ***************************************************************** */
/* *                            PART 2                             * */
/* ***************************************************************** */
int score_from_group_of_3string(vector<string>& vec,
                                const map<char, int>& priorities) {
  int score = 0;
  for (char letter_fword : vec.front()) {
    for (char letter_sword : vec.at(1)) {
      if (letter_fword == letter_sword &&
          vec.back().find(letter_fword) != string::npos) {
        score = priorities.at(letter_fword);
        break;
      }
    }
  }
  return score;
}

void rucksack_part2(const string& filename, const map<char, int>& priorities) {
  ifstream fileInput;
  fileInput.open(filename);

  int score = 0;
  if (fileInput.is_open()) {
    int index = 1;
    string current_line;
    string left, right;
    vector<string> group_of_3lines;

    while (getline(fileInput, current_line)) {
      group_of_3lines.push_back(current_line);
      if (index % 3 == 0) {
        score += score_from_group_of_3string(group_of_3lines, priorities);
        group_of_3lines.clear();
      }
      ++index;
    }
  }
  fileInput.close();
  cout << "\nPart 2\nRucksack score : " << score << endl;
}

int main() {
  const map<char, int> priorities = {
      {'a', 1},  {'b', 2},  {'c', 3},  {'d', 4},  {'e', 5},  {'f', 6},
      {'g', 7},  {'h', 8},  {'i', 9},  {'j', 10}, {'k', 11}, {'l', 12},
      {'m', 13}, {'n', 14}, {'o', 15}, {'p', 16}, {'q', 17}, {'r', 18},
      {'s', 19}, {'t', 20}, {'u', 21}, {'v', 22}, {'w', 23}, {'x', 24},
      {'y', 25}, {'z', 26}, {'A', 27}, {'B', 28}, {'C', 29}, {'D', 30},
      {'E', 31}, {'F', 32}, {'G', 33}, {'H', 34}, {'I', 35}, {'J', 36},
      {'K', 37}, {'L', 38}, {'M', 39}, {'N', 40}, {'O', 41}, {'P', 42},
      {'Q', 43}, {'R', 44}, {'S', 45}, {'T', 46}, {'U', 47}, {'V', 48},
      {'W', 49}, {'X', 50}, {'Y', 51}, {'Z', 52}};

  /* PART 1 */
  rucksack_part1("../../data/day3.txt", priorities);

  /* PART 2 */
  rucksack_part2("../../data/day3.txt", priorities);

  return EXIT_SUCCESS;
}