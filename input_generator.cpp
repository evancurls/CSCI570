#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * parse_file(string path) -> vector<string>
 * Args:
 *   path: path to the file to read the input string
 *
 * Returns:
 *   vector<string> of length 2
 *     ans[0] is string a, ans[1] is string b
 *
 * Error:
 *   empty vector<string>
 */

string iter_insert_copy(string s, int i) {
  // there is a way to not do this with iterations
  string ret = "";
  for (int j = 0; j <= i; ++j) {
    ret += s[j];
  }
  ret += s;
  for (int j = i + 1; j < s.size(); ++j) {
    ret += s[j];
  }
  return ret;
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
    // register nurse. fuck you microsoft
    if (!r.empty() && r.back() == '\r') {
      r.pop_back();
    }

    // init s1
    if (s1.empty() && r[0] >= '9') {
      s1 = r;
    }
    // copy for s1
    else if (s2.empty() && '0' <= r[0] && r[0] <= '9') {
      int i = stoi(r);
      s1 = iter_insert_copy(s1, i);
    }
    // init s2
    else if (s2.empty()) {
      s2 = r;
    }
    // copy for s2
    else if (0 <= r[0] && r[0] <= '9') {
      int i = stoi(r);
      s2 = iter_insert_copy(s2, i);
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
