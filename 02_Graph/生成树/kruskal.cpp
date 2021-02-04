const int maxn = 1e3+5;
struct node{
    int fr,to,cost;
    bool operator < (const node &b) const{
        return cost < b.cost;
    }
}arr[maxn];
int dad[maxn];
int seek(int x){
    if(x == dad[x]){
        return x;
    }else{
        return dad[x] = seek(dad[x]);
    }
}
int n,m;
void kruskal(){
	int cnt = 0, sum = 0;
    sort(arr + 1, arr + m + 1);
    for(int i = 1; i <= m; i++){
        int a = arr[i].fr, b = arr[i].to, c = arr[i].cost;
        int fa = seek(a), fb = seek(b);
        if(fa != fb){
            dad[fa] = fb;
            sum += c;
            cnt++;
        }
    }
    if(cnt != n-1){
		puts("无法构成最小生成树");
    }else{
        printf("最小生成树权值为%d\n",sum);
    }
}
void solve(){
	scanf("%d %d",&n,&m);
    for(int i = 1; i <= m; i++){
        int fr, to, cost;
        scanf("%d %d %d",&fr,&to,&cost);
        arr[i] = (node){fr,to,cost};
    }
    kruskal();
}