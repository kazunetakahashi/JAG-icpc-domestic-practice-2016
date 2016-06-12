#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int R0, W0, C, R;
  while (cin >> R0 >> W0 >> C >> R && R0) {
    for (auto X = 0; ; X++) {
      if ((R0+X*R)/(double)C - W0 >= 0) {
        cout << X << endl;
        break;
      }
    }
  }
}
