int ST[maxn][25],Log[maxn],arr[maxn];//ST第二维开到25就够用了
int n,m;
void init(){
    Log[1]=0;
    for(int i=2;i<=n;i++){
        Log[i]=Log[i/2]+1;
    }
    for(int i=1;i<=n;i++){
        ST[i][0]=arr[i];
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            ST[i][j]=max(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
        }
    }
}
int ask(int l,int r){
    int k = Log[r-l+1];
    return max(ST[l][k],ST[r-(1<<k)+1][k]);
}
void solve(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        arr[i] = read();
    }
    init();
    while(m--){
        int l,r;scanf("%d %d",&l,&r);
        printf("l到r的最大值为%d\n",ask(l,r));
    }
}