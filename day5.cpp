#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void display_answer(map<int, stack<char>> *stacks) {
  string answer;
  for (int i = 0; i < stacks->size(); ++i) {
    answer += (stacks->at(i).top());
  }
  cout << answer << endl;
}

void create_stacks_from_input(vector<string> *stack_elements,
                              map<int, stack<char>> *stacks) {
  int nb_stack = stack_elements->size();

  int index = 0;
  stack<char> tmp_stack;

  /* init stacks */
  for (int s = 1; s < 4 * nb_stack; s = s + 4) {
    // there is 4 space between the letters
    for (int i = nb_stack - 2; i >= 0;
         --i) {  // nb_stack - 2 because there is a number at the end

      if (stack_elements->at(i)[s] != ' ')
        tmp_stack.push(stack_elements->at(i)[s]);
    }
    stacks->insert(make_pair(index, tmp_stack));

    /* clear the temporary stack */
    while (!tmp_stack.empty()) tmp_stack.pop();

    ++index;
  }
}

/* ***************************************************************** */
/* *                            PART 1                             * */
/* ***************************************************************** */
void cratemover(vector<string> *moves, map<int, stack<char>> *stacks) {
  int nb_to_move, stack_from, stack_to;
  for (string current_move : *moves) {
    current_move = current_move.substr(
        current_move.find("move") + string("move ").size());  // remove 'move '

    nb_to_move = stoi(current_move.substr(0, current_move.find("from")));

    current_move =
        current_move.substr(current_move.find("from") + string("from ").size());

    stack_from = stoi(current_move.substr(0, current_move.find("to"))) - 1;
    stack_to = stoi(current_move.substr(current_move.find("to") +
                                        string("to ").size())) -
               1;

    for (int i = 0; i < nb_to_move; ++i) {
      if (!stacks->at(stack_from).empty()) {
        stacks->at(stack_to).push(stacks->at(stack_from).top());
        stacks->at(stack_from).pop();
      }
    }
  }
}

/* ***************************************************************** */
/* *                            PART 2                             * */
/* ***************************************************************** */
void cratemover9001(vector<string> *moves, map<int, stack<char>> *stacks) {
  int nb_to_move, stack_from, stack_to;
  for (string current_move : *moves) {
    current_move = current_move.substr(
        current_move.find("move") + string("move ").size());  // remove 'move '

    nb_to_move = stoi(current_move.substr(0, current_move.find("from")));

    current_move =
        current_move.substr(current_move.find("from") + string("from ").size());

    stack_from = stoi(current_move.substr(0, current_move.find("to"))) - 1;
    stack_to = stoi(current_move.substr(current_move.find("to") +
                                        string("to ").size())) -
               1;

    if (nb_to_move == 1) {
      if (!stacks->at(stack_from).empty()) {
        stacks->at(stack_to).push(stacks->at(stack_from).top());
        stacks->at(stack_from).pop();
      }

    } else {
      stack<char> tmp_stack;
      for (int i = 0; i < nb_to_move; ++i) {
        if (!stacks->at(stack_from).empty()) {
          tmp_stack.push(stacks->at(stack_from).top());
          stacks->at(stack_from).pop();
        }
      }

      for (int j = 0; j < nb_to_move; ++j) {
        stacks->at(stack_to).push(tmp_stack.top());
        tmp_stack.pop();
      }
    }
  }
}

void supply_stack(string filename,
                  void (*crate_func)(vector<string> *,
                                     map<int, stack<char>> *)) {
  ifstream fileInput;
  fileInput.open(filename);

  vector<string> stack_elements;
  vector<string> moves;
  if (fileInput.is_open()) {
    string current_line;

    while (getline(fileInput, current_line)) {
      if (current_line[0] == 'm')
        moves.push_back(current_line);
      else if (!current_line.empty())
        stack_elements.push_back(current_line);
    }
  }
  fileInput.close();

  map<int, stack<char>> stacks;
  create_stacks_from_input(&stack_elements, &stacks);
  crate_func(&moves, &stacks);
  display_answer(&stacks);
}

int main() {
  /* PART 1 */
  cout << "Part 1 : ";
  supply_stack("../data/data_day5.txt", cratemover);

  /* PART 2 */
  cout << "Part 2 : ";
  supply_stack("../data/data_day5.txt", cratemover9001);

  return EXIT_SUCCESS;
}