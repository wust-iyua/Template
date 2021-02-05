// 在前两个块相等时，时间从小到大排就可以了
// 注意更改时间轴时要考虑是否涵盖了当前区间来修改

// 洛谷P1903
#include <bits/stdc++.h>
using namespace std;
typedef long long  LL;
const int maxn = 2e5 + 7;
int n, m, block, belong[maxn], V[maxn], Num[maxn * 5];
int L, R, T, res, ans[maxn];
struct Mo {
    int l, r, t, id;
    bool operator < (const Mo& B) const {
        if(belong[l] != belong[B.l]) return belong[l] < belong[B.l];
        else if(belong[r] != belong[B.r]) return belong[l] & 1 ? r < B.r : r > B.r;
        else {
            return t < B.t;
        }
    }
} Q[maxn];
struct C {
    int pos, val;
} change[maxn];
inline void add(int x) {
    if(++ Num[x] == 1) ++ res;
}
inline void del(int x) {
    if(-- Num[x] == 0) -- res;
}
inline void Fly(int pos) {
    if(change[pos].pos >= L && change[pos].pos <= R) {
        del(V[change[pos].pos]);
        add(change[pos].val);
    }
    swap(V[change[pos].pos], change[pos].val);
}
int main () {
    scanf("%d %d", &n, &m);
    // block = sqrt(1.0 * n);
    block = pow(n, 2.0 / 3);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", V + i);
        belong[i] = (i - 1) / block + 1;
    }
    int nowT = 0, cnt = 0; char op[10];
    for (int i = 1; i <= m; ++ i) {
        int l, r; scanf("%s %d %d", op, &l, &r);
        if(op[0] == 'Q') {
            ++ cnt;
            Q[cnt] = (Mo) {l, r, nowT, cnt};
        } else {
            change[++ nowT] = (C) {l, r};
        }
    }
    sort(Q + 1, Q + cnt + 1);
    L = 1, R = 0, T = 0, res = 0;
    for (int i = 1; i <= cnt; ++ i) {
        int l = Q[i].l, r = Q[i].r, t = Q[i].t, id = Q[i].id;
        while(T < t) Fly(++ T);
        while(T > t) Fly(T --);
        while(R < r) add(V[++ R]);
        while(R > r) del(V[R --]);
        while(L < l) del(V[L ++]);
        while(L > l) add(V[-- L]);
        ans[id] = res;
    }
    for (int i = 1; i <= cnt; ++ i) {
        printf("%d\n", ans[i]);
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}