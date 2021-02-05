//  洛谷P4556
// 合并过程很简单，空节点就返回另一个，非空就把第二个信息合并在第一个根上，然后继续递归下去
// 合并时理清根节点如何变化，建议使用一个并查集来辅助维护根的记录
#include <bits/stdc++.h>
#define de(x)   cerr << "  debug  " << #x << "  ==  " << x << endl;
using namespace std;
const int maxn = 2e5 + 7;
struct SegTree {
    #define md  (l + r >> 1)
    int ls[maxn * 40], rs[maxn * 40], mx[maxn * 40], id[maxn * 40], tot;
    void clear() {
        tot = 0;
    }
    inline void push_up(int rt) {
        if(mx[ls[rt]] >= mx[rs[rt]]) {
            mx[rt] = mx[ls[rt]];
            id[rt] = id[ls[rt]];
        } else {
            mx[rt] = mx[rs[rt]];
            id[rt] = id[rs[rt]];
        }
    }
    void ins(int& rt, int l, int r, int pos, int tag) {
        if(!rt) {
            rt = ++ tot;
            ls[rt] = rs[rt] = mx[rt] = id[rt] = 0;
        }
        if(l == r) {
            mx[rt] += tag;
            id[rt] = pos;
            return ;
        }
        if(pos <= md) ins(ls[rt], l, md, pos, tag);
        else {
            ins(rs[rt], md + 1, r, pos, tag);
        }
        push_up(rt);
    }
    int Merge(int u, int v, int l, int r) {
        if(!u || !v) return u | v;
        if(l == r) {
            mx[u] = mx[u] + mx[v];
            id[u] = l;
            return u;
        }
        ls[u] = Merge(ls[u], ls[v], l, md);
        rs[u] = Merge(rs[u], rs[v], md + 1, r);
        push_up(u);
        return u;
    }
} T;
int root[maxn], first[maxn], tot = 0, fa[maxn][21], dep[maxn], res[maxn];
struct Edge {int v, nx;} edge[maxn << 1];
inline void addedge(int u, int v) {
    edge[++ tot] = (Edge) {v, first[u]};
    first[u] = tot;
}
void dfs(int u, int fr) {
    dep[u] = dep[fr] + 1;
    fa[u][0] = fr;
    for (int i = 1; i <= 20; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = first[u]; i; i = edge[i].nx) {
        int v = edge[i].v;
        if(v == fr) continue;
        dfs(v, u);
    }
}
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; (1 << i) <= d; ++ i) {
        if((d >> i) & 1) u = fa[u][i];
    }
    if(u == v) return u;
    for (int i = 20; ~i; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
void solve(int u, int fr) {
    for (int i = first[u]; i; i = edge[i].nx) {
        int v = edge[i].v;
        if(v == fr) continue;
        solve(v, u);
        root[u] = T.Merge(root[u], root[v], 1, 100000);
    }
    res[u] = T.id[root[u]];
    if(T.mx[root[u]] == 0) res[u] = 0;
}
int main () {
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 1; i < n; ++ i) {
        int u, v; scanf("%d %d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0);
    while(m --) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        int lca = LCA(u, v);
        T.ins(root[u], 1, 100000, w, 1);
        T.ins(root[v], 1, 100000, w, 1);
        T.ins(root[lca], 1, 100000, w, -1);
        T.ins(root[fa[lca][0]], 1, 100000, w, -1);
    }
    solve(1, 0);
    for (int i = 1; i <= n; ++ i) printf("%d\n", res[i]);
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}