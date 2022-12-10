#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int contains_rule_part1(int min1, int max1, int min2, int max2) {
  if ((min1 <= min2 && max1 >= max2) || (min1 >= min2 && max1 <= max2))
    return 1;
  return 0;
}

int contains_rule_part2(int min1, int max1, int min2, int max2) {
  if (min1 <= max2 && min2 <= max1) return 1;
  return 0;
}

void camp_cleanup(string filename, int (*func)(int, int, int, int)) {
  ifstream fileInput;
  fileInput.open(filename);

  int score = 0;
  if (fileInput.is_open()) {
    string current_line;
    string first_pair, second_pair;
    int pair00, pair01, pair10, pair11;

    while (getline(fileInput, current_line)) {
      first_pair = current_line.substr(0, current_line.find(','));
      second_pair =
          current_line.substr(current_line.find(',') + 1);  // to remove ','

      pair00 = stoi(first_pair.substr(0, first_pair.find('-')));
      pair01 = stoi(first_pair.substr(first_pair.find('-') + 1));

      pair10 = stoi(second_pair.substr(0, second_pair.find('-')));
      pair11 = stoi(second_pair.substr(second_pair.find('-') + 1));

      score += func(pair00, pair01, pair10, pair11);
    }
  }
  fileInput.close();
  cout << "Camp cleanup score : " << score << endl;
}

int main() {
  /* PART 1 */
  cout << "\nPart 1" << endl;
  camp_cleanup("../data/data_day4.txt", contains_rule_part1);

  /* PART 2 */
  cout << "\nPart 2" << endl;
  camp_cleanup("../data/data_day4.txt", contains_rule_part2);

  return EXIT_SUCCESS;
}