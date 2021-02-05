//假设  N个字符串  每个字符串长度最大为M
//则需要开的空间为 N*M  即个数乘于最大长度
// 形式多变  可在插入时记录下标方便更多操作
const int maxn = N*M + 7;
int tree[maxn][27];
int tot,sum[maxn];
void insert(char str[]){
	int root = 0;
    for(int i = 0; str[i] ; i++){
        int pos = str[i] - 'a' + 1;
        if(!tree[root][pos]){
            tree[root][pos] = ++tot;
        }
        root = tree[root][pos];
        sum[root]++;
    }
}
//查询多少个字符串有一个为str的前缀
int seek(char str[]){
    int root = 0;
    for(int i = 0 ; str[i] ; i++){
        int pos = str[i] - 'a' + 1;
        if(!tree[root][pos]){
			return 0;
        }
        root = tree[root][pos];
    }
    return sum[root];
}
void solve(){
    tot = 0;
    memset(tree,0,sizeof(tree));
    int n,m;
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        char str[105];
        scanf("%s",str);
        insert(str);
    }
    scanf("%d",&m);
    while(m--){
		char str[105];
        scanf("%s",str);
        int num = seek(str);
        printf("以%s这个字符串为前缀的字符串个数有%d个\n",str,ans);
    }
}