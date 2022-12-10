#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void max_calorie_counter(string filename) {
  ifstream fileInput;
  fileInput.open(filename);

  int max = 0;
  int counter = 0;
  string current_line;
  if (fileInput.is_open()) {
    while (getline(fileInput, current_line)) {
      if (!current_line.empty()) {
        counter += atoi(current_line.c_str());
      } else {
        if (counter > max) max = counter;

        counter = 0;
      }
    }
  }
  fileInput.close();
  cout << "\nMaximum of calories is : " << max << endl;
}

void max3_calorie_counter(string filename) {
  ifstream fileInput;
  fileInput.open(filename);

  int counter = 0;
  int min, index;
  int top[3] = {0, 0, 0};
  string current_line;

  if (fileInput.is_open()) {
    while (getline(fileInput, current_line)) {
      if (!current_line.empty()) {
        counter += atoi(current_line.c_str());
      } else {
        min = *min_element(top, top + 3);

        if (min < counter) {
          index = find(top, top + 3, min) - top;
          top[index] = counter;
        }
        counter = 0;
      }
    }
  }
  fileInput.close();

  int total = 0;
  cout << "\nTop 3 of calories are : ";
  for (int i = 0; i < 3; ++i) {
    if (i == 2)
      cout << top[i] << " with a total of ";
    else
      cout << top[i] << ", ";

    total += top[i];
  }

  cout << total << endl;
}

int main() {
  /* PART 1 */
  max_calorie_counter("../data/data_day1.txt");

  /* PART 2 */
  max3_calorie_counter("../data/data_day1.txt");

  return EXIT_SUCCESS;
}