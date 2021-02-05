//输入n个数  
//然后再输入m个数 并在前n个数里找出与这个数异或最大的数为多少
//贪心思想  高位向低位尽量找大的
int tree[maxn][2],be[maxn],arr[maxn];
int tot = 0;
void insert(int val,int id){
    int root = 0;
    for(int i = 31; i >= 0 ; i--){
        int pos = ((val >> i) & 1);
        if(!tree[root][pos]){
            tree[root][pos] = ++tot;
        }
        root = tree[root][pos];
    }
    be[root] = id;
}
int seek(int val){
    int root = 0;
    for(int i = 31;i >= 0; i--){
        int pos = ((val >> i) & 1);
        if(tree[root][pos^1]){
            root = tree[root][pos^1];
        }else{
            root = tree[root][pos];
        }
    }
    return arr[be[root]];
}
void solve(){
    int n, m;
    scanf("%d",&n);
    for(int i = 1;i <= n; i++){
        scanf("%d",&arr[i]);
        insert(arr[i],i);
    }
    scanf("%d",&m);
    while(m--){
        int tmp;
        scanf("%d",&tmp);
        int ans = seek(tmp);
        printf("数组中与%d异或后结果最大的数为%d，异或结果为%d",ans,ans^tmp);
    }
}