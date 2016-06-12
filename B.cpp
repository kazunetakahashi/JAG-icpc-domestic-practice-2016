#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef vector<vector<bool> > ban;

int a, b, c, d;
int W, H;

ban s_to_ban(string S) {
  // W, H を求める。
  H = 0;
  int now = 0;
  vector<string> preban;
  for (auto i = 0; i < (int)S.size(); i++) {
    if (S[i] == '/') {
      preban.push_back(S.substr(now, i-now));
      now = i+1;
    }
  }
  preban.push_back(S.substr(now, (int)S.size()-now));
  H = (int)preban.size();
  ban B = ban(H, vector<bool>());
  for (auto i = 0; i < H; i++) {
    string co = preban[i];
    for (auto x : co) {
      if (x == 'b') {
        B[i].push_back(true);
      } else {
        int l = x - '0';
        for (auto j = 0; j < l; j++) {
          B[i].push_back(false);
        }
      }
    }
  }
  W = (int)B[0].size();
  return B;
}

string ban_to_s(ban B) {
  string S = "";
  int cnt = 0;
  for (auto i = 0; i < H; i++) {
    for (auto j = 0; j < W; j++) {
      if (B[i][j]) {
        if (cnt > 0) S += to_string(cnt);
        S += 'b';
        cnt = 0;
      } else {
        cnt++;
      }
    }
    if (cnt > 0) S += to_string(cnt);
    cnt = 0;
    if (i < H-1) S += '/';
  }
  return S;
}

int main() {
  string S;
  while (cin >> S && S != "#") {
    cin >> a >> b >> c >> d;
    a--; b--; c--; d--;
    ban B = s_to_ban(S);
    for (auto i = 0; i < H; i++) {
      for (auto j = 0; j < W; j++) {
        cerr << (B[i][j] ? 'b' : '.');
      }
      cerr << endl;
    }
    swap(B[a][b], B[c][d]);
    cout << ban_to_s(B) << endl;
  }
}
