#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <limits.h>

using namespace std;

vector<string> split_compartment(const string& str) {
  vector<string> split;
  size_t comp_sz = str.length()/2;
  split.push_back(str.substr(0,comp_sz));
  split.push_back(str.substr(comp_sz));
  return split;
}

char get_common_char(const string& line) {
  vector<string> split = split_compartment(line);
  for (size_t i=0; i<split[0].size(); i++) {
    if (split[1].find(split[0][i]) != string::npos) return split[0][i];
  }
  return '\0';
}

int char_to_priority(const char& c) {
  int ch = (int)c;
  if (ch >= 97) return ch-96;
  else return ch-38;
}

int charindex(const char& c) {
  return char_to_priority(c)-1;
}

char priority_to_char(const int& prio) {
  if (prio < 27) return (char)(prio+96);
  else return (char)(prio+38);
}

template<class T>
void print_vector(vector<T> vec) {
  cout << "[";
  for (auto ele : vec) {
    cout << ele << ", ";
  }
  cout << "]\n";
}

char get_common_char(const vector<string>& lines) {
  vector<int> hash1(52,0);
  vector<int> hash2(52,0);

  for (auto ch : lines[0]) {
    hash1[charindex(ch)]++;
  }

  for (int i=1; i<lines.size(); i++) {
    for (auto ch : lines[i]) {
      hash2[charindex(ch)]++;
    }
    for (int i=0; i<52; i++) {
      hash1[i] = (hash1[i] < hash2[i]) ? hash1[i] : hash2[i];
      hash2[i] = 0;
    }
  }

  for (int i=0; i<52; i++) {
    if (hash1[i] > 0) return priority_to_char(i+1);
  }
  return '\0';
}


int line_to_priority(const string& str) {
  return char_to_priority(get_common_char(str));
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
    int num=1, priority=0, total_priority=0;
    int group_counter=1, total_group_counter=1, b_priority=0, total_b_priority=0;
    vector<string> lines;
    char common, group_common;
    while (getline(input, line)) {
      if (group_counter > 3) {
        group_counter = 1;
        group_common = get_common_char(lines);
        b_priority = char_to_priority(group_common);
        cout << "Group #"<<total_group_counter++<<": " << group_common<<"("<<b_priority<<")\n";
        total_b_priority += b_priority;
        lines.clear();
      }
      lines.push_back(line);
      group_counter++;
      common = get_common_char(line);
      priority = char_to_priority(common);
      cout << "Rucksack #"<<num++<<": " << common <<"("<<priority<<")\n";
      total_priority+=priority;
    }
    if (group_counter > 3) {
      group_counter = 1;
      group_common = get_common_char(lines);
      b_priority = char_to_priority(group_common);
      cout << "Group #"<<total_group_counter++<<": " << group_common<<"("<<b_priority<<")\n";
      total_b_priority += b_priority;
      lines.clear();
    }
    cout << "Sum of priorities: " << total_priority << '\n';
    cout << "Sum of group priorities: " << total_b_priority << '\n';
  } else {
    // file wasn't opened
    cerr << "File " << argv[1] << " could not be opened\n";
    cerr << "Error code: " << strerror(errno);
  }
}
