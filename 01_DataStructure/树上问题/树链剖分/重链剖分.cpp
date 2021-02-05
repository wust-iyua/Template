// 利用DFS序的思想  把树分割成若干条链  对于每条链用线段树维护
// 树上区间操作时  用一个函数 将这个区间映射为一条条线段  再在线段树上进行修改即可
const int maxn = 1e5 + 7;
int tot, id[maxn], rk[maxn], top[maxn];
int dep[maxn], fa[maxn], siz[maxn], son[maxn];
// 处理出dep fa siz son
void DFS1(int u,int fr) {
	dep[u] = dep[fr] + 1;
	fa[u] = fr, siz[u] = 1, son[u] = -1;
	for (int i = 0; i < G[u].size(); ++ i) {
		int v = G[u][i];
		if(v == fr) continue;
		DFS(v, u);
		siz[u] += siz[v];
		if(son[u] == -1 || siz[v] > siz[son[u]]) {
			son[u] = v;
		}
	}
}
// 处理出 id rk top数组
void DFS2(int u, int fr) {
	id[u] = ++ tot, rk[tot] = u;
	top[u] = fr;
	if(son[u] == -1) return ;
	DFS2(son[u], fr);
	for (int i = 0; i < G[u].size(); ++ i) {
		int v = G[u][i];
		if(v == fa[u] || v == son[u]) continue;
		DFS2(v, v);
	}
}
// 操作树上u v区间
void updataUV(int u, int v) {
	// 当两者不在同一条链的时候  
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
        // solve(id[top[u]], id[u])   操作这条链
        u = fa[top[u]];
	}
	// 注意如果是边  是一个道理的  因为每条边都相当于一个父子边
	// 每条父子边对应只有一个儿子  下放权值就可以了
	// 但是边的话  此时如果  u == v 就该直接return 了
	// 感性理解一下
	// 此时已经在同一条链
	if(id[u] > id[v]) swap(u, v);
	// solve(id[u], id[v])
    //  边的话就是  solve(id[u] + 1, id[v]);
}