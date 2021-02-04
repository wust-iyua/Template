// O(n * sqrt(n) ) 
const int maxn = 2e3 + 7;
const int inf = 0x3f3f3f3f;
struct _HK {
	int mx[maxn], my[maxn], dx[maxn], dy[maxn];
	int n, m, dis;
	bool vis[maxn];
	vector<int> G[maxn];
	
	void init() {
		for(int i = 1; i <= n; ++ i) {
			G[i].clear();
		}
	}
	
	void read_data() {
		scanf("%d %d", &n, &m);
		init();
		while(m --) {
			int a, b;
			scanf("%d %d", &a, &b);
			G[a].push_back(b);
		}
	}
	
	bool bfs() {
		memset(dx, -1, sizeof(dx));
		memset(dy, -1, sizeof(dy));
		queue<int> que;
		dis = inf;
		for(int i = 1; i <= n; ++ i) {
			if(mx[i] == -1) {
				dx[i] = 0;
				que.push(i);
			}
		}
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			if(dx[u] > dis) {
				break;
			}
			int sz = G[u].size();
			for(int i = 0; i < sz; ++ i) {
				int v = G[u][i];
				if(dy[v] == -1) {
					dy[v] = dx[u] + 1;
					if(my[v] == -1) {
						dis = dy[v];
					} else {
						dx[my[v]] = dy[v] + 1;
						que.push(my[v]);
					}
				}
			}
		}
		return dis != inf;
	}
	
	bool dfs(int u) {
		int sz = G[u].size();
		for(int i = 0; i < sz; ++ i) {
			int v = G[u][i];
			if(!vis[v] && dy[v] == dx[u] + 1) {
				vis[v] = true;
				if(my[v] != -1 && dy[v] == dis) {
					continue;
				}
				if(my[v] == -1 || dfs(my[v])) {
					my[v] = u;
					mx[u] = v;
					return  true;
				}
			}
		}
		return false;
	}
	
	int max_match() {
		int res = 0;
		memset(mx, -1, sizeof(mx));
		memset(my, -1, sizeof(my));
		while(bfs()) {
			memset(vis, false, sizeof(vis));
			for(int i = 1; i <= n; ++ i) {
				if(mx[i] == -1 && dfs(i)) {
					++ res;
				}
			}
		}
		return res;
	}
};
