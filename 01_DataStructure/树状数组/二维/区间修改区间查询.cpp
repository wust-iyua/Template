#include <bits/stdc++.h>
using namespace std;
#define int  long long 
inline int lowbit(int x) { return x & (-x);}
const int maxn = 5e3 + 7;
int n, m;
int t1[maxn][maxn], t2[maxn][maxn], t3[maxn][maxn], t4[maxn][maxn];
void add(int x, int y, int k) {
    for(int X = x; X <= n; X += lowbit(X)) {
        for(int Y = y; Y <= m; Y += lowbit(Y)) {
            t1[X][Y] += k;
            t2[X][Y] += x * k;
            t3[X][Y] += y * k;
            t4[X][Y] += x * y * k;
        }
    }
}
void range_add(int a, int b, int c, int d, int k) {
    add(a, b, k);
    add(a, d + 1, -k);
    add(c + 1, b, -k);
    add(c + 1, d + 1, k);
}
int ask(int x, int y) {
    int res = 0;
    for(int X = x; X >= 1; X -= lowbit(X)) {
        for(int Y = y; Y >= 1; Y -= lowbit(Y)) {
            res += (x + 1) * (y + 1) * t1[X][Y] 
                - (y + 1) * t2[X][Y]
                - (x + 1) * t3[X][Y]
                + t4[X][Y];
        }
    }
    return res;
}
int range_ask(int a, int b, int c, int d) {
    return ask(c, d) - ask(c, b - 1) - ask(a - 1, d) + ask(a - 1, b - 1);
}
signed main () {
    scanf("%lld %lld", &n, &m);
    int option, a, b, c, d, k;
    while(~scanf("%lld", &option)) {
        if(option == 1) {
            scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &k);
            range_add(a, b, c, d, k);
        } else {
            scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
            printf("%lld\n", range_ask(a, b, c, d));
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}