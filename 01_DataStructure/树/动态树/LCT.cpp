#include <bits/stdc++.h>
#define de(x)   cerr << "   debug  " << #x << "   ==   " << x << endl;
using namespace std;
// https://www.luogu.com.cn/problem/P3690
// 洛谷P3690
/*
    0. 查询边权信息  sum / max / min / xor
    1. 开链
    2. 断链
    3. 修改点权
    
    对于维护边，可以将一条边映射为一个点  例如<u, v>
    改成 <u, id>  <id, v> 这样就用点权表示出了边权
    常用套路是维护一条链上 max/min 那个边的点id值（注意维护的是下标不是权值）
    id为代表哪条边
    然后动态割开/合并
    常用来动态维护生成树, 记录最大最小边权的下标，之后动态加边时定位下标到那条边
    之后cut掉  再link新边

    若题目保证不含删边操作 请使用并查集维护根而不是 Findroot()
    Findroot() 常数大  可能会TLE

    准确来说不是不含删边  而是在同一个集合内之后保证不会分离  就可以使用并查集了
    例如 UOJ THU集训2016  《温暖会指引我们前行》
    https://uoj.ac/problem/274

    but 如果是询问一条边是否存在  那么在一个集合内也不行  
    可能会破开  这时候要用Findroot
*/
#define ls(x)   son[x][0]
#define rs(x)   son[x][1]
template<typename T, const size_t MAX = 300007>
class Link_Cut_Tree {
    public :
        // 点值与路径权值
        T val[MAX], sum[MAX];
        // 栈  splay要从上往下放标记， 所以单独开的栈来push_down
        int sta[MAX], top;
        inline void clear(int n) {
        // 注意这里清空是从0开始的  如果初始化每个点权值并不是1这种问题
        // 则需从1开始清，0点单独清，因为0时空节点，给0赋值会导致统计出错
            for (int i = 0; i <= n; ++ i) {
                val[i] = sum[i] = 0;
                revtag[i] = 0;
                ls(i) = rs(i) = Fa[i] = 0;
            }
        }
        inline void Splay(int x) {
            int y = x;
            top = 0; sta[++ top] = y;
            while(!isroot(y)) {
                sta[++ top] = Fa[y];
                y = Fa[y];
            }
            while(top) push_down(sta[top --]);
            while(!isroot(x)) {
                y = Fa[x]; int z = Fa[y];
                if(!isroot(y)) Rotate((chk(x) ^ chk(y)) ? x : y);
                Rotate(x);
            }
        }
        // 换根  使x变成这个树的根
        // 森林 > 树 > 若干splay
        inline void makeroot(int x) {
            Access(x); Splay(x);
            Rev(x);
        }
        // 提取边  单独拎出来
    	// Split时反转y到了顶端  且更新好了  此时y储存的就是这条链信息
        inline void Split(int x, int y) {
            makeroot(x);
            Access(y); Splay(y);
        }
        // // 是否有边
        // inline bool islink(int x, int y) {
        //     makeroot(x);
        //     return findroot(y) == x && Fa[y] == x && !ls(y);
        // }
        // 连边
        inline void Link(int x, int y) {
            makeroot(x);
            // 写成 fa[x] = y 
            // 因为此时x是根  一定无父节点 所以不会出错
            if(findroot(y) != x) Fa[x] = y;
        }
        // 断边
        inline void cut(int x, int y) {
            makeroot(x);
            if(findroot(y) == x && Fa[y] == x && !ls(y)) {
                Fa[y] = rs(x) = 0;
                push_up(x);
            }
        }
        // 若边一定存在
        // 可以直接  split(x, y)  Fa[x] = ls(y) = 0   push_up(y)
    	// 维护信息
        inline void push_up(int x) {
            sum[x] = (sum[ls(x)] ^ sum[rs(x)] ^ val[x]);
        }
    private :
        int Fa[MAX], son[MAX][2], revtag[MAX];
        // 判断是否为 splay 的根  只需父亲节点不含这个儿子即可
        // 即父子边为虚
        inline bool isroot(int x) {
            return ls(Fa[x]) != x && rs(Fa[x]) != x;
        }
        // 换根后反转 splay 维持性质
        inline void Rev(int x) {
            swap(ls(x), rs(x));
            revtag[x] ^= 1;
        }
        // 下放标记
        inline void push_down(int x) {
            if(revtag[x]) {
                if(ls(x)) Rev(ls(x));
                if(rs(x)) Rev(rs(x));
                revtag[x] ^= 1;
            }
        }
        // 判断是 左/右 儿子
        inline int chk(int x) {
            return rs(Fa[x]) == x;
        }
        // 上旋
        inline void Rotate(int x) {
            int y = Fa[x], z = Fa[y];
            int sx = chk(x), sy = chk(y), s = son[x][sx ^ 1];
            if(!isroot(y)) {
                son[z][sy] = x;
            }
            son[x][sx ^ 1] = y;
            son[y][sx] = s;
            if(s) Fa[s] = y;
            Fa[y] = x; Fa[x] = z;
            push_up(y);
            push_up(x);
        }
        // 开辟 根到x  这条路为重链
        inline void Access(int x) {
            for (int y = 0; x; x = Fa[y = x]) {
                Splay(x);
                rs(x) = y;
                push_up(x);
            }
        }
        // 找到这个点所处的树的根
        inline int findroot(int x) {
            Access(x); Splay(x);
            //  因为lazy标记是覆盖的同时反转
            //  所以这里可以直接判断左儿子
            while(ls(x)) {
                push_down(x);
                x = ls(x);
            }
            Splay(x);
            return x;
        }
};
Link_Cut_Tree<int> LCT;
int main () {
    int n, m; scanf("%d %d", &n, &m);
    LCT.clear(n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &LCT.val[i]);
        LCT.sum[i] = LCT.val[i];
    }
    while(m --) {
        int op, x, y; scanf("%d %d %d", &op, &x, &y);
        // 查询 x~y  异或之和
        if(op == 0) {
            // Split时反转y到了顶端  且更新好了  此时y储存的就是这条链信息
            LCT.Split(x, y);
            printf("%d\n", LCT.sum[y]);
        } else if(op == 1) {
            // 链接 x~y
            LCT.Link(x, y);
        } else if(op == 2) {
            // 断开 x~y
            LCT.cut(x, y);
        } else {
            //  修改点x
            LCT.Splay(x);
            LCT.val[x] = y;
            LCT.push_up(x);
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}