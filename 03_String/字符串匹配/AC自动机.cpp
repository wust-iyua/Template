// 多模式匹配
//  在这里是统计一系列字符串多少个在文本串出现过
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
struct AC {
    int fail, son[26], flag;
}trie[maxn];
int tot = 1;
char str[maxn];
void Insert() {
    int root = 1, i = 0;
    while(str[i]) {
        int v = str[i] - 'a';
        if(!trie[root].son[v]) trie[root].son[v] = ++ tot;
        root = trie[root].son[v];
        ++ i;
    }
    ++ trie[root].flag;
}
void build() {
    for (int i = 0; i < 26; ++ i) trie[0].son[i] = 1;
    trie[1].fail = 0;
    queue<int> Q; Q.push(1);
    while(!Q.empty()) {
        int u = Q.front(), fail = trie[u].fail;
        Q.pop();
        for (int i = 0; i < 26; ++ i) {
            int& v = trie[u].son[i];
            if(v == 0) {
                v = trie[fail].son[i];
            } else {
                trie[v].fail = trie[fail].son[i];
                Q.push(v);
            }
        }
    }
}
int query() {
    int res = 0,u = 1;
    for (int i = 0; str[i]; ++ i) {
        int v = str[i] - 'a';
        int k = trie[u].son[v];
        while(k > 1 && trie[k].flag != -1) {
            res += trie[k].flag;
            trie[k].flag = -1;
            k = trie[k].fail;
        }
        u = trie[u].son[v];
    }
    return res;
}
int main () {
    int n; scanf("%d", &n);
    while(n --) {
        scanf("%s", str);
        Insert();
    }
    build();
    scanf("%s", str);
    printf("%d\n", query());
    return 0;
}