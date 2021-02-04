// true -- min_express
// false -- max_express
// 返回值为对应表示法的答案的第一个下标(0开始)
// 注意异构循环节都是一样的，所以循环节直接对原始的来求就可以了
int max_min_express(char s[], bool flag) {
    int len = strlen(s), i = 0, j = 1, k = 0;
    while(i < len && j < len && k < len) {
        int t = s[(j + k) % len] - s[(i + k) % len];
        if(t == 0) ++ k;
        else {
            if(flag) {
                if(t > 0)   j += k + 1;
                else    i += k + 1;
            } else {
                if(t > 0)   i += k + 1;
                else    j += k + 1;
            }
            if(i == j) ++ j;
            k = 0;
        }
    }
    return min(i, j);
}