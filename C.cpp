#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <complex>
using namespace std;
typedef complex<double> point;

int N;
int x[110];
int y[110];
int a[4];
int b[4];

double outer_product(point x, point y) {
  return (conj(x) * y).imag();
} 
bool opposite(point a1, point a2, point b1, point b2) {
  return (outer_product(a2-a1, b1-a1) * outer_product(a2-a1, b2-a1) < 0);
}
 
bool crossed(point a1, point a2, point b1, point b2) {
  return ( opposite(a1, a2, b1, b2) && opposite(b1, b2, a1, a2) );
}

int main() {
  point inner = point((double)0.5, (double)0.5);
  point outer = point((double)-1000, (double)-1);
  point b1 = point(1, 2);
  point b2 = point(1, 0);
  cerr << crossed(inner, outer, b1, b2) << endl;
  while (cin >> N && N) {
    vector<int> tx[2];
    for (auto i = 0; i < N; i++) {
      cin >> x[i] >> y[i];
      tx[0].push_back(x[i]);
      tx[1].push_back(y[i]);
    }
    for (auto i = 0; i < 4; i++) {
      cin >> a[i] >> b[i];
      tx[0].push_back(a[i]);
      tx[1].push_back(b[i]);
    }
    map<int, double> M[2];
    vector<int> T[2];
    for (auto i = 0; i < 2; i++) {
      sort(tx[i].begin(), tx[i].end());
      for (auto x : tx[i]) {
        if (M[i].find(x) == M[i].end()) {
          M[i][x] = (double)T[i].size();
          T[i].push_back(x);
        }
      }
    }
    int A, B;
    A = M[0].size();
    B = M[1].size();
    vector<point> P;
    vector<point> Q;
    for (auto i = 0; i < N; i++) {
      P.push_back(point(M[0][x[i]], M[1][y[i]]));
    }
    for (auto i = 0; i < N; i++) {
      cerr << "P[" << i << "] = ("
           << P[i].real() << " " << P[i].imag() << ")" << endl;
    }
    for (auto i = 0; i < 4; i++) {
      Q.push_back(point(M[0][a[i]], M[1][b[i]]));
    }
    for (auto i = 0; i < 4; i++) {
      cerr << "Q[" << i << "] = ("
           << Q[i].real() << " " << Q[i].imag() << ")" << endl;
    }
    bool F[110][110];
    fill(&F[0][0], &F[0][0]+110*110, false);
    for (auto i = 0; i < A-1; i++) {
      for (auto j = 0; j < B-1; j++) {
        point inner = point((double)i+0.5, (double)j+0.5);
        point outer = point((double)-1000, (double)-1);
        int cnt = 0;
        for (auto i = 0; i < (int)P.size(); i++) {
          if (crossed(inner, outer, P[i], P[(i+1)%N])) {
            cnt++;
          }
        }
        int cnt2 = 0;
        for (auto i = 0; i < (int)Q.size(); i++) {
          if (crossed(inner, outer, Q[i], Q[(i+1)%4])) {
            cerr << "i = " << i << endl;
            cnt2++;
          }
        }
        cerr << cnt << ", " << cnt2 << endl;
        if (cnt%2 == 1 && cnt2%2 == 0) {
          F[i][j] = true;
        }
      }
    }
    cerr << A << " x " << B << endl;
    for (auto i = 0; i < A; i++) {
      for (auto j = 0; j < B; j++) {
        cerr << "(" << T[0][i] << ", " << T[1][j] << "), ";
      }
      cerr << endl;
    }
    for (auto i = 0; i < A-1; i++) {
      for (auto j = 0; j < B-1; j++) {
        cerr << (F[i][j] ? "#" : ".");
      }
      cerr << endl;
    }
    int ans = 0;
    for (auto i = 0; i < A-1; i++) {
      for (auto j = 0; j < B-1; j++) {
        cerr << (T[0][i+1] - T[0][i]) * (T[1][j+1] - T[1][j]) << " ";
        if (F[i][j]) {
          ans += (T[0][i+1] - T[0][i]) * (T[1][j+1] - T[1][j]);
        }
      }
      cerr << endl;
    }
    cout << ans << endl;
  }
}
