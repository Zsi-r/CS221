#include <cmath>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
const int maxnumber = 1e5 + 5;
const int primenumber = 2333;
typedef long long ll;
vector<ll>htemp[primenumber];
ll sum[maxnumber][35], c[maxnumber][35];
int compare(int x, int y) {

    for(int i = 1; i <= m; i++) {
        if(c[x][i] != c[y][i]) return 0;
    }
    return 1;
}
int main() {

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        for(int j = m; j >= 1; j--) {
            sum[i][j] = sum[i - 1][j] + x % 2;
            x /= 2;
        }
    }
    int temp = 0; 
    for(int i = 1; i <= n; i++) {
        int ans = 0;
        int ttt = 0;
        for(int j = 1; j <= m; j++) {
            c[i][j] = sum[i][j] - sum[i][1];
            if(c[i][j] == 0) ans++;
            ttt = (ttt + c[i][j]) % primenumber;
        }
        ttt = abs(ttt);
        if(ans == m) temp = i;
        htemp[ttt].push_back(i);
    }
    for(int i = 1; i < primenumber; i++) {
        int sum = htemp[i].size();
        if(sum > 1) {
            for(int j = 0; j < sum - 1; j++) {
                for(int k = 1; k < sum; k++) {
                    if(compare(htemp[i][j], htemp[i][k]) && htemp[i][k] - htemp[i][j]  > temp) {
                        temp = htemp[i][k] - htemp[i][j];
                    }
                }
            }
        }
    }
    cout << temp <<endl;
    return 0;
}