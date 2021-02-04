// 求出每个位置每个字母下一次出现的位置
// 十分灵活
const int maxn = 1e6 + 7;
char str[maxn];
int nxt[maxn][26];
void build() {
    // 字符串下标1开始
    int n = strlen(str + 1);
    memset(nxt, -1, sizeof(nxt));
    for (int i = n - 1; ~i; -- i) {
        for (int j = 0; j < 26; ++ j) nxt[i][j] = nxt[i + 1][j];
        nxt[i][str[i + 1] - 'a'] = i + 1;
    }
}