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

string insert_copy(string s, int i) {
  string result;
  result.reserve(s.size() * 2);
  result.append(s, 0, i + 1);
  result.append(s);
  result.append(s, i + 1, string::npos);

  return result;
}

vector<string> parse_file(const string &path) {
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
      s1 = insert_copy(s1, i);
    }
    // init s2
    else if (s2.empty()) {
      s2 = r;
    }
    // copy for s2
    else if (0 <= r[0] && r[0] <= '9') {
      int i = stoi(r);
      s2 = insert_copy(s2, i);
    }
  }
  file.close();

  return vector<string>{s1, s2};
}

int write_file(const string &path, const vector<string> ans) {
  ofstream file(path);
  for (string s : ans) {
    file << s << endl;
  }
  return 0;
}
// int main(int argc, char *argv[]) {
//   if (argc != 2) {
//     cout << "usage: input_generator path/to/input_file" << endl;
//     return -1;
//   }
//   vector<string> ans = parse_file(argv[1]);
//   if (ans.empty()) {
//     return -1;
//   }
//   cout << "String 1:" << endl;
//   cout << ans[0] << endl;
//   cout << "String 2:" << endl;
//   cout << ans[1] << endl;
// }
