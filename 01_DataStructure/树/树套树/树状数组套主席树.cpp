// https://www.luogu.com.cn/problem/P2617
// 洛谷P2617
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n, m, Q, a[maxn], b[maxn << 1];
int root[maxn], top = 0;
struct INPUT {
    char ch[2];
    int x, y, z;
};
vector<INPUT> input;
#define ls(x)   Tree[x].l
#define rs(x)   Tree[x].r
#define tum(x)  Tree[x].sum
struct PresindentTree {
    int l, r, sum;
}Tree[maxn * 60];
void updata(int& rt, int l, int r, int id, int val) {
    if(!rt) rt = ++ top;
    if(top >= maxn * 60) {
        while(1);
    }
    Tree[rt].sum += val;
    if(l == r) return;
    int md = l + r >> 1;
    if(id <= md) updata(ls(rt), l, md, id, val);
    else {
        updata(rs(rt), md + 1, r, id, val);
    }
}
void singlechange(int x, int be) {
    int k = lower_bound(b + 1, b + m + 1, a[x]) - b;
    for (int i = x; i <= n; i += (i & -i)) {
        updata(root[i], 1, m, k, be);
    }
}
int temp[2][22];
int query(int l, int r, int k) {
    if(l == r) return b[l];
    int md = l + r >> 1, sum = 0;
    for (int i = 1; i <= temp[1][0]; ++ i) {
        sum += tum(ls(temp[1][i]));
    }
    for (int i = 1; i <= temp[0][0]; ++ i) {
        sum -= tum(ls(temp[0][i]));
    }
    if(k <= sum) {
        for (int i = 1; i <= temp[1][0]; ++ i) {
            temp[1][i] = ls(temp[1][i]);
        }
        for (int i = 1; i <= temp[0][0]; ++ i) {
            temp[0][i] = ls(temp[0][i]);
        }
        return query(l, md, k);
    } else {
        for (int i = 1; i <= temp[1][0]; ++ i) {
            temp[1][i] = rs(temp[1][i]);
        }
        for (int i = 1; i <= temp[0][0]; ++ i) {
            temp[0][i] = rs(temp[0][i]);
        }
        return query(md + 1, r, k - sum);
    }
}
int rangequery(int l, int r, int k) {
    temp[0][0] = temp[1][0] = 0;
    for (int i = r; i >= 1; i -= (i & -i)) temp[1][++ temp[1][0]] = root[i];
    for (int i = l - 1; i >= 1; i -= (i & -i)) {
        temp[0][++ temp[0][0]] = root[i];
    }
    return query(1, m, k);
}
int main () {
    scanf("%d %d", &n, &Q);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    int len = n;
    input.resize(Q);
    for (int i = 0; i < Q; ++ i) {
        scanf("%s %d %d", input[i].ch, &input[i].x, &input[i].y);
        if(input[i].ch[0] == 'Q') {
            scanf("%d", &input[i].z);
        } else {
            b[++ len] = input[i].y;
        }
    }
    sort(b + 1, b + len + 1); 
    m = unique(b + 1, b + len + 1) - b - 1;
    for (int i = 1; i <= n; ++ i) singlechange(i, 1);
    for (int i = 0; i < Q; ++ i) {
        if(input[i].ch[0] == 'Q') {
            printf("%d\n", rangequery(input[i].x, input[i].y, input[i].z));
        } else {
            singlechange(input[i].x, -1);
            a[input[i].x] = input[i].y;
            singlechange(input[i].x, 1);
        }
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}