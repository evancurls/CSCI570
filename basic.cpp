#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <errno.h>
#include <sys/resource.h>
#include <sys/time.h>

using namespace std;

extern int errno;

// alpha table

const int ALPHA[4][4] = {
    {0, 110, 48, 94},
    {110, 0, 118, 48},
    {48, 118, 0, 110},
    {94, 48, 110, 0},
};
const int DELTA = 30;

int basetoi(char c) {
  if (c == 'A') {
    return 0;
  }
  if (c == 'C') {
    return 1;
  }
  if (c == 'G') {
    return 2;
  }
  if (c == 'T') {
    return 3;
  }
  return -1;
}

// input generator

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

void bottom_up(vector<vector<int>> &OPT, const vector<string> &s) {
  for (int i = 1; i < OPT.size(); ++i) {
    for (int j = 1; j < OPT[0].size(); ++j) {
      char x = s[0][i - 1], y = s[1][j - 1];
      int xi = basetoi(x), yi = basetoi(y);
      int a = ALPHA[xi][yi];
      OPT[i][j] = min(OPT[i - 1][j - 1] + a,
                      min(OPT[i - 1][j] + DELTA, OPT[i][j - 1] + DELTA));
    }
  }
}

vector<string> top_down(vector<vector<int>> &OPT, const vector<string> &s) {
  /*
   * look at OPT[i-1][j], OPT[i-1,j-1], OPT[i][j-1]
   *
   */
  string result_i = "", result_j = "";
  int i = OPT.size() - 1, j = OPT[0].size() - 1;
  while (i > 0 || j > 0) {
    if (i > 0 && j > 0 &&
        OPT[i][j] == OPT[i - 1][j - 1] +
                         ALPHA[basetoi(s[0][i - 1])][basetoi(s[1][j - 1])]) {
      result_i += s[0][--i];
      result_j += s[1][--j];
    } else if (i > 0 && OPT[i][j] == OPT[i - 1][j] + DELTA) {
      result_i += s[0][--i];
      result_j += '_';
    } else {
      assert(j > 0 && OPT[i][j] == OPT[i][j - 1] + DELTA);
      result_i += '_';
      result_j += s[1][--j];
    }
  }

  reverse(result_i.begin(), result_i.end());
  reverse(result_j.begin(), result_j.end());
  return vector<string>{result_i, result_j};
}

vector<string> basic(const vector<string> &s) {
  if (s.empty()) {
    return vector<string>();
  }

  // initialize OPT
  vector<vector<int>> OPT(s[0].size() + 1, vector<int>(s[1].size() + 1, 0));

  for (int i = 0; i < OPT.size(); ++i) {
    OPT[i][0] = DELTA * i;
  }
  for (int j = 0; j < OPT[0].size(); ++j) {
    OPT[0][j] = DELTA * j;
  }
  // cout << "Initialized OPT" << endl;

  // bottom up
  bottom_up(OPT, s);
  int cost = OPT[OPT.size() - 1][OPT[0].size() - 1];
  // cout << "Cost: " << cost << endl;

  // top down
  vector<string> ans = top_down(OPT, s);

  return vector<string>{ans[0], ans[1], to_string(cost)};
}

long getTotalMemory() {
  struct rusage usage;
  int returnCode = getrusage(RUSAGE_SELF, &usage);
  if (returnCode == 0) {
    return usage.ru_maxrss;
  } else {
    cerr << "error " << errno << endl;
    return -1;
  }
}

int main(int argc, char *argv[]) {
  struct timeval begin, end;
  gettimeofday(&begin, 0);

  vector<string> s = parse_file(argv[1]);
  vector<string> ans = basic(s);

  double totalmemory = getTotalMemory();

  gettimeofday(&end, 0);
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  double totaltime = seconds * 1000 + microseconds * 1e-3;

  vector<string> print = {
      ans[2], ans[1], ans[0], to_string(totaltime), to_string(totalmemory),
  };
  int w = write_file(argv[2], print);
  return w;
}
