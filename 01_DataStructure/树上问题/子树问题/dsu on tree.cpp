// CF600E
#include <bits/stdc++.h>
#define de(x)   cerr << "   debug   " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 1e5 + 7;
int n, col[maxn];
vector<int> G[maxn];
int C[maxn], mxcnt, flag;
LL res[maxn], sum;
int siz[maxn], son[maxn];
void DFS1(int u, int fr) {
    son[u] = -1, siz[u] = 1;
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr) continue;
        DFS1(v, u);
        siz[u] += siz[v];
        if(son[u] == -1 || siz[v] > siz[son[u]]) {
            son[u] = v;
        }
    }
}
void solve(int u, int fr, int tag) {
    C[col[u]] += tag;
    if(C[col[u]] > mxcnt) {
        mxcnt = C[col[u]];
        sum = col[u];
    } else if(C[col[u]] == mxcnt) {
        sum += col[u];
    }
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr || v == flag) continue;
        solve(v, u, tag);
    }
}
void DFS(int u, int fr, bool del) {
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr || v == son[u]) continue;
        DFS(v, u, true);
    }
    if(son[u] != -1) {
        DFS(son[u], u, false);
        // flag = son[u];
    }
    flag = son[u];
    solve(u, fr, 1);
    res[u] = sum;
    flag = 0;
    if(del) {
        solve(u, fr, -1);
        mxcnt = sum = 0;
    }
}
int main () {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) scanf("%d", col + i);
    for (int i = 1; i < n; ++ i) {
        int u, v; scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    flag = sum = mxcnt = 0;
    DFS1(1, 0);
    DFS(1, 0, false); // 单组传false  多组需清空就true
    for (int i = 1; i <= n; ++ i) printf("%lld%c", res[i], i == n ? '\n' : ' ');
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}