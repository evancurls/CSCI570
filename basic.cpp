#include "alpha_chart.cpp"
#include <string>
#include <vector>

using namespace std;

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

  // bottom up
  for (int i = 1; i < OPT.size(); ++i) {
    for (int j = 1; j < OPT[0].size();) {

    }
  }



  

  return vector<string>();
}
