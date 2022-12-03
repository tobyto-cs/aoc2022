#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;
enum RPS { INVALID, ROCK, PAPER, SCISSORS };

int calc_score(const RPS opp, const RPS you) {
  if (opp == ROCK) {
    if (you == ROCK) return 1+3;
    else if (you == PAPER) return 2+6;
    else return 3+0;
  } else if (opp == PAPER) {
    if (you == ROCK) return 1+0;
    else if (you == PAPER) return 2+3;
    else return 3+6;
  } else {
    if (you == ROCK) return 1+6;
    else if (you == PAPER) return 2+0;
    else return 3+3;
  }
}

int calc_true_score(const char& opp, const char& you) {
  if (you == 'X') {
    if (opp == 'A') return 3;
    else if (opp == 'B') return 1;
    else return 2;
  } if (you == 'Y') {
    if (opp == 'A') return 3+1;
    else if (opp == 'B') return 3+2;
    else return 3+3;
  } else {
    if (opp == 'A') return 6+2;
    else if (opp == 'B') return 6+3;
    else return 6+1;
  }

}

RPS char_to_rps(const char& c) {
  if (c == 'A' || c == 'X') return ROCK;
  else if (c == 'B' || c == 'Y') return PAPER;
  else if (c == 'C' || c == 'Z') return SCISSORS;
  else return INVALID;
}


int main(int argc, const char* argv[]) {
  if (argc < 2) {
    cerr << "Please give an input file\n";
    exit(EXIT_FAILURE);
  }

  ifstream input;
  input.open(argv[1]);


  if (input) {
    string line;
    int round=1, score=0, total_score=0;
    int true_score=0, total_true_score=0;
    while (getline(input, line)) {
      // Part 1
      // Each line has two values, first is what opponent will chose
      // second is what you  should play
      assert(line.length() == 3);
      score = calc_score(char_to_rps(line[0]), char_to_rps(line[2]));
      true_score = calc_true_score(line[0], line[2]);
      cout << "Round " << round++ << " score: " << score << ", True score: " << true_score << '\n';
      total_score += score;
      total_true_score += true_score;
      // Part 2
    }
    cout << "Total Score: " << total_score << '\n';
    cout << "Total True Score: " << total_true_score << '\n';
  } else {
    // file wasn't opened
    cerr << "File " << argv[1] << " could not be opened\n";
    cerr << "Error code: " << strerror(errno);
  }
}
