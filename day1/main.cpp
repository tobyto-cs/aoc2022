#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

template <class T> struct max_three {
  typedef pair<int, T> toppair;
  toppair first;
  toppair second;
  toppair third;


  void add(T num, int index) {
    if (num > first.second) {
      third = second;
      second = first;
      first = toppair(index, num);
    } else if (num > second.second) {
      third = second;
      second = toppair(index, num);
    } else if (num > third.second) {
      third = toppair(index, num);
    }
  }
};

int main(int argc, const char* argv[]) {
  // get file to open from command line
  if (argc < 2) {
    cerr << "Please give an input file\n";
    exit(EXIT_FAILURE);
  }

  ifstream input;
  input.open(argv[1]);

  if (input) {
    string line;
    vector<int> elf_data = {0};
    max_three<int> leaderboard;
    while (getline(input, line)) {
      if (line.empty()) {
        leaderboard.add(elf_data[elf_data.size()-1], elf_data.size());
        elf_data.push_back(0);
      } else {
        elf_data[elf_data.size()-1] += stoi(line);
      }
    }
    cout << "\nElf Calorie Leaderboard\n";
    int top_total = 0;
    cout << "Elf #1 was elf " << leaderboard.first.first << " with " <<leaderboard.first.second << " calories\n";
    cout << "Elf #2 was elf " << leaderboard.second.first << " with " <<leaderboard.second.second << " calories\n";
    cout << "Elf #3 was elf " << leaderboard.third.first << " with " <<leaderboard.third.second << " calories\n";
    cout << "With a total of " << leaderboard.first.second + leaderboard.second.second + leaderboard.third.second << '\n';

  } else {
    // file wasn't opened
    cerr << "File " << argv[1] << " could not be opened\n";
    cerr << "Error code: " << strerror(errno);
  }



  return EXIT_SUCCESS;
}
