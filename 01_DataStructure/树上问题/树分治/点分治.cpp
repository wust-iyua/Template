//  dis <= k 点对数目
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 7;
const int inf = 0x3f3f3f3f;
int n, k, top;
int head[maxn], siz[maxn];
bool vis[maxn];
struct Edge{
    int v, w, nx;
}edge[maxn << 1];
void addedge(int u, int v, int w) {
    ++ top; 
    edge[top].v = v, edge[top].w = w, edge[top].nx = head[u], head[u] = top;
}
int Size, root, mxsiz;
void seekroot(int u, int fr) {
    siz[u] = 1; int mx = 0;

    for (int i = head[u]; i ; i = edge[i].nx) {
        int v = edge[i].v, w = edge[i].w;
        if(vis[v] || v == fr) continue;
        seekroot(v, u);
        siz[u] += siz[v];
        mx = max(mx, siz[v]);
    }
    mx = max(mx, Size - siz[u]);
    if(mx < mxsiz) {
        mxsiz = mx;
        root = u;
    }
}
int dis[maxn], d[maxn];
void getdis(int& r, int u, int fr) {
    d[++ r] = dis[u];
    for (int i = head[u]; i ; i = edge[i].nx) {
        int v = edge[i].v, w = edge[i].w;
        if(v == fr || vis[v]) continue;
        dis[v] = dis[u] + w;
        getdis(r, v, u);
    }
}
int cal(int u, int val) {
    int l = 1, r = 0;
    dis[u] = val;
    getdis(r, u, 0);
    int res = 0;
    sort(d + l, d + r + 1);
    while(l < r) {
        if(d[l] + d[r] <= k) res += r - l, ++ l;
        else -- r;
    }
    return res;
}
int ans;
void divide(int u) {
    ans += cal(u, 0);
    vis[u] = 1;
    for (int i = head[u]; i ; i = edge[i].nx) {
        int v = edge[i].v;
        if(vis[v]) continue;
        ans -= cal(v, edge[i].w);
        Size = siz[v];
        mxsiz = inf;
        seekroot(v, 0);
        divide(root);
    }
}
int main () {
    while(~scanf("%d %d", &n, &k) && (n || k)) {
        top = 0;
        Size = n; mxsiz = n;
        for (int i = 1; i <= n; ++ i) head[i] = 0, vis[i] = false;
        for (int i = 1; i < n; ++ i) {
            int u, v, w; scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        ans = 0;
        seekroot(1, 0);
        divide(root);
        printf("%d\n", ans);
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}