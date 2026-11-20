#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string insert_copy(string s, int i) {
  string first, last;
  first = s.substr(0, i+1);
  // ensure last is in bounds
  if (i < s.size()) {
    last = s.substr(i + 1);
  } else {
    last = "";
  }

  return first + s + last;
}

vector<string> parse_file(string path) {
  ifstream file(path);
  if (!file.is_open()) {
    cerr << "Error: file " << path << " not opened. Maybe path is wrong?"
         << endl;
    return vector<string>{};
  }

  string s1, s2, r;
  while (getline(file, r)) {
    // init s1
    if (s1.empty()) {
      s1 = r;
    }
    // copy for s1
    else if (s2.empty() && '0' <= r[0] && r[0] <= '9') {
      int i = stoi(r);
      s1 = insert_copy(s1, i);
    }
    // init s2
    else if (s2.empty()) {
      s2 = r;
    } else {
      int i = stoi(r);
      s2 = insert_copy(s2, i);
    }
  }
  file.close();

  return vector<string>{s1, s2};
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "usage: input_generator path/to/input_file" << endl;
    return -1;
  }
  vector<string> ans = parse_file(argv[1]);
  if (ans.empty()) {
    return -1;
  }
  cout << "String 1:" << endl;
  cout << ans[0] << endl;
  cout << "String 2:" << endl;
  cout << ans[1] << endl;
}
