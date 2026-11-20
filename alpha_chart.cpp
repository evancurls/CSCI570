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
