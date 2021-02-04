char s1[maxn], s2[maxn];
int nxt[maxn], ext[maxn];
//可以用来求解s1后缀与s2前缀重叠部分的长度
// ext[i]  s1{i -> n}  &&  s2 {1 -> n} LCP
//s2
void NXT(char x[], int len) {
    int i = 0, j, po;
    nxt[0] = len;
    while(i + 1 < len && x[i] == x[i + 1]) {++ i;}
    nxt[1] = i;
    po = 1;
    for(i = 2; i < len; ++ i) {
        if(nxt[i - po] + i < nxt[po] + po) {
            nxt[i] = nxt[i - po];
        } else {
            j = max(0, nxt[po] + po - i);
            while(i + j < len && x[j] == x[j + i]) {++ j;}
            nxt[i] = j;
            po = i;
        }
    }
}
void EKMP(char s1[], char s2[]) {
    int i = 0, j, po, len1 = strlen(s1), len2 = strlen(s2);
    NXT(s2, len2);
    while(s1[i] == s2[i] && i < len1 && i < len2) {++ i;}
    ext[0] = i;
    po = 0;
    for(i = 1; i < len1; ++ i) {
        if(nxt[i - po] + i < ext[po] + po) {
            ext[i] = nxt[i - po];
        } else {
            j = max(0, ext[po] + po - i);
            while(i + j < len1 && j < len2 && s1[i + j] == s2[j]) {++ j;}
            ext[i] = j;
            po = i;
        }
    }
}