// O1求 k 级祖先
#include <bits/stdc++.h>
#define de(x)   cerr << "   debug   " << #x << "   ==  " << x << endl;
using namespace std;
const int maxn = 5e5 + 7;
typedef long long  LL;
#define ui unsigned int
ui s;
inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}
int root, n, Q;
int dep[maxn], mdep[maxn], son[maxn], top[maxn];
int fa[maxn][22];
int HeiBit[maxn];
vector<int> G[maxn], up[maxn], down[maxn];
void DFS1(int u) {
    son[u] = -1;
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        mdep[v] = dep[v] = dep[u] + 1;
        fa[v][0] = u;
        for (int j = 1; (1 << j) <= n; ++ j) fa[v][j] = fa[fa[v][j - 1]][j - 1];
        DFS1(v);
        if(son[u] == -1 || mdep[v] > mdep[son[u]]) {
            son[u] = v;
            mdep[u] = mdep[v];
        }
    }
}
void DFS2(int u, int fr) {
    top[u] = fr;
    if(u == fr) {
        for (int i = 0, f = u; i <= mdep[u] - dep[u]; ++ i) {
            up[u].push_back(f); f = fa[f][0];
        }
        for (int i = 0, f = u; f != -1 && i <= mdep[u] - dep[u]; ++ i) {
            down[u].push_back(f); f = son[f];
        }
    }
    if(son[u] != -1) DFS2(son[u], fr);
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        if(v ^ son[u]) DFS2(v, v);
    }
}
// O(1) 求 x 的 k 级祖先
inline int ASK(int x, int k) {
    if(!k) return x;
    x = fa[x][HeiBit[k]];
    k -= (1 << HeiBit[k]);
    k -= dep[x] - dep[top[x]];
    x = top[x];
    return k >= 0 ? up[x][k] : down[x][-k];
}
int main () {
    scanf("%d %d %u", &n, &Q, &s);
    LL ans = 0, res = 0;
    HeiBit[1] = 0;
    for (int i = 1; i <= n; ++ i) {
        if(i != 1) HeiBit[i] = HeiBit[i >> 1] + 1;
        int f; scanf("%d", &f);
        if(f) {
            G[f].push_back(i);
        } else {
            root = i;
        }
    }
    dep[root] = 1;
    DFS1(root);
    DFS2(root, root);
    for (int i = 1; i <= Q; ++ i) {
        int x = ((get(s) ^ ans) % n) + 1;
        int k = (get(s) ^ ans) % dep[x];
        ans = ASK(x, k);
        res ^= (1ll * i * ans);
    }
    printf("%lld\n", res);
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}