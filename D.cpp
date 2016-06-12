#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <iomanip>
using namespace std;

int N;
double p[110];
int m[110];
vector<int> V[110];
bool W[110][110];

int main() {
  while (cin >> N && N) {
    for (auto i = 0; i < N; i++) {
      cin >> p[i];
      cin >> m[i];
      V[i].clear();
      for (auto j = 0; j < m[i]; j++) {
        int a;
        cin >> a;
        a--;
        V[i].push_back(a);
      }
    }
    //cerr << "aa" << endl;
    fill(&W[0][0], &W[0][0]+110*110, false);
    for (auto i = 0; i < N; i++) {
      stack<int> S;
      bool visited[110];
      fill(visited, visited+110, false);
      visited[i] = true;
      for (auto x : V[i]) {
        S.push(x);
      }
      while (!S.empty()) {
        int now = S.top();
        S.pop();
        if (!visited[now]) {
          W[i][now] = true;
          visited[now] = true;
          for (auto y : V[now]) {
            if (!visited[y]) S.push(y);
          }
        }
      }
    }
    //cerr << "aa" << endl;
    vector< vector <int> > G;
    bool visited[110];
    fill(visited, visited+110, false);
    for (auto i = 0; i < N; i++) {
      if (visited[i]) continue;
      visited[i] = true;
      vector<int> g;
      g.push_back(i);
      for (auto j = i+1; j < N; j++) {
        if (W[i][j] && W[j][i]) {
          g.push_back(j);
          visited[j] = true;
        }
      }
      G.push_back(g);
    }
    /*
    for (auto x : G) {
      for (auto y : x) {
        cerr << y << " ";
      }
      cerr << endl;
    }
    */
    bool need[110];
    fill(need, need+110, true);
    for (auto i = 0; i < (int)G.size(); i++) {
      for (auto j = 0; j < (int)G.size(); j++) {
        if (i == j) continue;
        int src = G[i][0];
        int dst = G[j][0];
        if (W[src][dst]) {
          need[j] = false;
        }
      }
    }
    double ans = 1;
    for (auto i = 0; i < (int)G.size(); i++) {
      if (!need[i]) continue;
      double temp = 1;
      for (auto x : G[i]) {
        temp *= p[x];
      }
      ans *= (1 - temp);
    }
    cout << fixed << setprecision(10) << ans << endl;
  }
}
