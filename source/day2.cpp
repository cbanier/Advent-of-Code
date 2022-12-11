#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int letter_value(const char& letter) {
  int value;
  switch (letter) {
    case 'X':
      value = 1;
      break;
    case 'Y':
      value = 2;
      break;
    default:  // Z
      value = 3;
      break;
  }
  return value;
}

/* Associate A,B,C to X,Y,Z */
void reformat_letter(char& letter) {
  char cp_letter = letter;
  switch (cp_letter) {
    case 'A':
      letter = 'X';
      break;
    case 'B':
      letter = 'Y';
      break;
    default:
      letter = 'Z';
      break;
  }
}

/* ***************************************************************** */
/* *                            PART 1                             * */
/* ***************************************************************** */
int rules_part1(char& elf, const char& me) {
  reformat_letter(elf);

  // same value
  if (elf == me) return 3 + letter_value(me);

  // wining move
  else if ((me == 'X' && elf == 'Z') || (me == 'Y' && elf == 'X') ||
           (me == 'Z' && elf == 'Y'))
    return 6 + letter_value(me);

  // losing move
  return letter_value(me);
}

void rock_paper_scissors_part1(const string& filename) {
  ifstream fileInput;
  fileInput.open(filename);

  int score = 0;
  if (fileInput.is_open()) {
    string current_line;

    while (getline(fileInput, current_line)) {
      char& elf = current_line[0];
      char& me = current_line[2];

      score += rules_part1(elf, me);
    }
  }
  fileInput.close();
  cout << "\nPart 1\nRock Paper Scissors score : " << score << endl;
}

/* ***************************************************************** */
/* *                            PART 2                             * */
/* ***************************************************************** */
int rules_part2(char& elf, const char& which_end) {
  reformat_letter(elf);

  int score;
  char strategy;
  switch (which_end) {
    case 'Y':  // draw
      strategy = elf;
      score = 3;
      break;

    case 'X':  // lose
      if (elf == 'X')
        strategy = 'Z';
      else if (elf == 'Y')
        strategy = 'X';
      else
        strategy = 'Y';

      score = 0;
      break;

    default:  // win
      if (elf == 'X')
        strategy = 'Y';
      else if (elf == 'Y')
        strategy = 'Z';
      else
        strategy = 'X';

      score = 6;
      break;
  }

  return letter_value(strategy) + score;
}

void rock_paper_scissors_part2(const string& filename) {
  ifstream fileInput;
  fileInput.open(filename);

  int score = 0;
  if (fileInput.is_open()) {
    string current_line;

    while (getline(fileInput, current_line)) {
      char& elf = current_line[0];
      char& which_end = current_line[2];

      score += rules_part2(elf, which_end);
    }
  }
  fileInput.close();
  cout << "\nPart 2\nRock Paper Scissors score : " << score << endl;
}

int main() {
  /* PART 1 */
  rock_paper_scissors_part1("../../data/day2.txt");

  /* PART 2 */
  rock_paper_scissors_part2("../../data/day2.txt");

  return EXIT_SUCCESS;
}