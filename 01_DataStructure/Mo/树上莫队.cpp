// 用欧拉序来映射出一棵树就可以了，同时vis数组代表被覆盖几次，偶数就相当于不覆盖
// 同时注意处理 lca的影响
//  下面是求一棵树上一条路径上不同颜色数  每个点都有一种颜色
#include <bits/stdc++.h>
// #define de(x)   cerr << "  debug  " << #x << "  ==  " << x << endl;
using namespace std;
#define belong(x)   ((x - 1) / block + 1)
typedef long long  LL;
const int maxn = 1e5 + 7;
int st[maxn], ed[maxn], rk[maxn], V[maxn], tmp[maxn], n, m, tim, block;
int vis[maxn], siz[maxn], son[maxn], fa[maxn][21], dep[maxn];
vector<int> G[maxn];
void DFS1(int u, int fr) {
    st[u] = ++ tim;
    rk[tim] = u;
    fa[u][0] = fr;
    dep[u] = dep[fr] + 1;
    for (int i = 1; (1 << i) <= n; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    siz[u] = 1; son[u] = -1;
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v == fr) continue;
        DFS1(v, u);
        siz[u] += siz[v];
        if(son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }
    ed[u] = ++ tim;
    rk[tim] = u;
}
inline int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; (1 << i) <= d; ++ i) if((d >> i) & 1) u = fa[u][i];
    if(u == v) return u;
    for (int i = 20; i >= 0; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
struct Mo {
    int l, r, lca, id;
    bool operator < (const Mo& B) const {
        if(belong(l) == belong(B.l)) return r < B.r;
        else {
            return l < B.l;
        }
    }
} Q[maxn];
int res[maxn], cnt[maxn], L, R, ans;
inline void add(int x) {
    // cout << " add  " << x << endl;
    ans += (++ cnt[x] == 1);
}
inline void del(int x) {
    // cout << "  del " << x << endl; 
    ans -= (-- cnt[x] == 0);
}
inline void Fly(int x) {
    (vis[x] ^= 1);
    vis[x] ? add(V[x]) : del(V[x]);
}
void solve () {
    scanf("%d %d", &n, &m);
    block = sqrt(2.0 * n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", V + i);
        tmp[i] = *(V + i);
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; ++ i) V[i] = lower_bound(tmp + 1, tmp + len + 1, V[i]) - tmp;
    for (int i = 1; i < n; ++ i) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    DFS1(1, 0);
    for (int i = 1; i <= m; ++ i) {
        int u, v; scanf("%d %d", &u, &v);
        if(st[u] > st[v]) swap(u, v);
        int lca = LCA(u, v);
        if(lca == u) {
            Q[i] = (Mo) {st[u], st[v], 0, i};
            // cout << "===" <<  st[u] << ' ' << st[v] << endl;
        } else {
            Q[i] = (Mo) {ed[u], st[v], lca, i};
            // cout << "====" << ed[u] << ' ' << st[v] << endl;
        }
    }
    sort(Q + 1, Q + m + 1);
    ans = 0; L = 1; R = 0;
    for (int i = 1; i <= m; ++ i) {
        int l = Q[i].l, r = Q[i].r, lca = Q[i].lca, id = Q[i].id;
        while(R < r) Fly(rk[++ R]);
        while(R > r) Fly(rk[R --]);
        while(L < l) Fly(rk[L ++]);
        while(L > l) Fly(rk[-- L]);
        if(lca) Fly(lca);
        res[id] = ans;
        if(lca) Fly(lca);
        // de(l)
        // de(r)
        // de(lca)
    }
    for (int i = 1; i <= m; ++ i) printf("%d\n", res[i]);
}
int main () {
    int T = 1; //scanf("%d", &T);
    while(T --) {
        solve ();
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}