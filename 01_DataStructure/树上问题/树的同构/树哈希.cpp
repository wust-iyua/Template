// https://www.luogu.com.cn/problem/P5043
// T棵树  输出每棵树最靠前的同构的树的位置
#include <bits/stdc++.h>
#define de(x)   cerr << "    debug   " << #x << "  ==  " << x << endl;
typedef long long  LL;
using namespace std;
const int maxn = 1e5 + 7;
const LL mod = 1e9 + 7;
string ans[maxn], F[maxn], V[maxn];
vector<int> G[maxn];
int n, siz[maxn], mx[maxn], mxsiz;
void seekroot(int u, int fr) {
    siz[u] = 1; mx[u] = 0;
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr) continue;
        seekroot(v, u);
        mx[u] = max(mx[u], siz[v]);
        siz[u] += siz[v];
    }
    mx[u] = max(mx[u], n - siz[u]);
    mxsiz = min(mxsiz, mx[u]);
}
void DFS(int u, int fr) {
    F[u] = "0";
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr) continue;
        DFS(v, u);
    }
    int tot = 0;
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr) continue;
        V[++ tot] = F[v];
    }
    sort(V + 1, V + tot + 1);
    for (int i = 1; i <= tot; ++ i) F[u] += V[i];
    F[u] += "1";
}
int main () {
    int T = 1; scanf("%d", &T);
    for (int i = 1; i <= T; ++ i) {
        scanf("%d", &n);
        mxsiz = 0x7fffffff;
        for (int j = 1; j <= n; ++ j) G[j].clear();
        for (int j = 1; j <= n; ++ j) {
            int x; scanf("%d", &x);
            if(x) {
                G[x].push_back(j);
                G[j].push_back(x);
            }
        }
        seekroot(1, 0);
        ans[i] = "1";
        for (int j = 1; j <= n; ++ j) {
            if(mx[j] == mxsiz) {
                DFS(j, 0);
                ans[i] = min(ans[i], F[j]);
            }
        }
        for (int j = 1; j <= i; ++ j) {
            if(ans[j] == ans[i]) {
                printf("%d\n", j);
                break;
            }
        }
    }
    // for (int i = 1; i <= T; ++ i) de(ans[i])
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}