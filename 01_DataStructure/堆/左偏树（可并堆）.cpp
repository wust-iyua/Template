// 洛谷P1456
// 对每一个猴子维护一个左偏树，用并查集维护根，合并时分割出根，处理完权值变化
// 再合在一起就可以了
#include <bits/stdc++.h>
#define de(x)   cerr << "  debug  " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 1e5 + 7;
int fa[maxn], dis[maxn], ls[maxn], rs[maxn], val[maxn], n;
int seek(int x) {
    return x == fa[x] ? x : (fa[x] = seek(fa[x]));
}
void clear() {
    dis[0] = -1;
    for (int i = 0; i <= n; ++ i) {
        fa[i] = i;
        ls[i] = rs[i] = 0;
    }
}
int Merge(int u, int v) {
    if(!u || !v) return u | v;
    if(val[u] < val[v]) swap(u, v);
    rs[u] = Merge(rs[u], v);
    if(dis[ls[u]] < dis[rs[u]]) swap(ls[u], rs[u]);
    dis[u] = dis[rs[u]] + 1;
    return u;
}
void damage(int x) {
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    int a = ls[x], b = rs[x];
    ls[x] = rs[x] = 0;
    val[x] /= 2;
    fa[a] = fa[x] = Merge(a, fa[x]);
    fa[a] = fa[b] = fa[x] = Merge(b, fa[x]);
}
int main () {
    while(~scanf("%d", &n)) {
        clear();
        for (int i = 1; i <= n; ++ i) scanf("%d", val + i);
        int m; scanf("%d", &m);
        while(m --) {
            int u, v;
            scanf("%d %d", &u, &v);
            int fu = seek(u), fv = seek(v);
            if(fu == fv) {
                puts("-1");
                continue;
            }
            damage(fu);
            damage(fv);
            fu = seek(fu);
            fv = seek(fv);
            fa[fv] = fa[fu] = Merge(fu, fv);
            // for (int i = 1; i <= n; ++ i) {
            //     printf("%d %d\n", seek(i), val[i]);
            // }
            printf("%d\n", val[seek(fu)]);
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}
// 洛谷P1552
// 明显在每个叶子节点维护一个优先队列，直接pop到元素符合要求为止
// 但合并到父亲节点时，优先队列就太慢了， 所以用左偏树实现可并堆快速合并
#include <bits/stdc++.h>
#define de(x)   cerr << "  debug  " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 1e5 + 7;
int cnt[maxn], fa[maxn], n;
int seek(int x) {
    return x == fa[x] ? x : (fa[x] = seek(fa[x]));
}
LL heap[maxn], tot[maxn], sum, C[maxn], L[maxn], res = 0;
int ls[maxn], rs[maxn], dis[maxn];
vector<int> G[maxn];
int Merge(int u, int v) {
    if(!u || !v) return u + v;
    if(heap[u] < heap[v]) swap(u, v);
    rs[u] = Merge(rs[u], v);
    if(dis[ls[u]] < dis[rs[u]]) swap(ls[u], rs[u]);
    dis[u] = dis[rs[u]] + 1;
    return u;
}
void pop(int u) {
    fa[ls[u]] = ls[u];
    fa[rs[u]] = rs[u];
    LL tmp = tot[u] - heap[u], p = cnt[u] - 1;
    fa[u] = Merge(ls[u], rs[u]);
    tot[fa[u]] = tmp;
    cnt[fa[u]] = p;
}
void DFS(int u) {
    int fu = seek(u);
    for (int i = 0; i < G[u].size(); ++ i) {
        int v = G[u][i];
        DFS(v);
        int fv = seek(v);
        int tmp1 = cnt[fu] + cnt[fv];
        LL tmp2 = tot[fu] + tot[fv];
        fu = fa[u] = Merge(fu, fv);
        cnt[fu] = tmp1;
        tot[fu] = tmp2;
    } 
    while(tot[fu] > sum) {
        pop(fu);
        fu = fa[u] = seek(fu);
    }
    res = max(res, 1ll * L[u] * cnt[fu]);
}
int main () {
    dis[0] = -1;
    scanf("%d %lld", &n, &sum);
    int root;
    for (int i = 1; i <= n; ++ i) {
        fa[i] = i;
        cnt[i] = 1;
        int a; scanf("%d", &a);
        if(a) {
            G[a].push_back(i);
        } else root = i;
        scanf("%lld %lld", &C[i], &L[i]);
        heap[i] = C[i];
        tot[i] = C[i];
    }
    DFS(root);
    printf("%lld\n", res);
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}