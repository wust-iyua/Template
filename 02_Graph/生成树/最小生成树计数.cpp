#include <bits/stdc++.h>
using namespace std;
const int mod = 31011;
struct edge1{
    int a, b, c;
    edge1(){}
    edge1(int a, int b, int c) : a(a), b(b), c(c) {}
    bool operator <(const edge1 &rhs) const{
        return c < rhs.c;
    }
}E1[10005];
struct edge2{
    int st, en, len;
    edge2(){}
    edge2(int st, int en, int len) : st(st), en(en), len(len) {}
}E2[10005]; //存的是边权想等的一个联通块

int fa[105];
int n, m, tot, ans = 1;
int cnt, sum;
int find_set(int x){ //不能用路径压缩，因为要连通块分离
    if(x == fa[x]) return x;
    else return find_set(fa[x]);
}
void dfs(int x, int now, int k){ //起点，终点，联通块的权值和
    if(now == E2[x].en + 1){
        if(k == E2[x].len){
            sum++;
        }
        return;
    }
    int fx = find_set(E1[now].a), fy = find_set(E1[now].b);
    if(fx != fy){
        fa[fx] = fy;
        dfs(x, now + 1, k + 1);
        fa[fx] = fx;
        fa[fy] = fy;
    }
    dfs(x, now + 1, k);
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) fa[i] = i; //每个点都在一个连通块
    for(int i = 1; i <= m; i++){ //Kruskal cal MST
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        E1[i] = edge1(u, v, w);
    }
    sort(E1 + 1, E1 + m + 1);
    for(int i = 1; i <= m; i++){
        if(E1[i].c != E1[i-1].c){
            E2[++cnt].st = i;
            E2[cnt-1].en = i - 1;
        }
        int x = find_set(E1[i].a), y = find_set(E1[i].b);
        if(x != y){
            fa[x] = y;
            E2[cnt].len++;
            tot++;
        }
    }
    E2[cnt].en = m;
    if(tot != n - 1){
        puts("0");
        return 0;
    }
    for(int i = 1; i <= n; i++) fa[i] = i; //求出生成树之后，还原连通块
    for(int i = 1; i <= cnt; i++)
    {
        sum = 0;
        dfs(i, E2[i].st, 0);
        ans = (ans * sum) % mod;
        for(int j = E2[i].st; j <= E2[i].en; j++){ //消除前面联通块的影响，不然会WA，sample就是前一阶段有没有用完的点，并且和现在的联通块连边
            int x = find_set(E1[j].a), y = find_set(E1[j].b);
            if(x != y){
                fa[x] = y;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}