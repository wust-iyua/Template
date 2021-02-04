const int maxn = 1e5+7;
int nxt[maxn];
void get_nxt(char ptr[]){
	int len = strlen(ptr), i = 0, k = -1;
    nxt[0] = -1;
    while(i < len){
        if(k == -1 || ptr[i] == ptr[k]){
            nxt[++ i] = ++ k;
        }else{
            k = nxt[k];
        }
    }
}
int kmp(char str[],char ptr[]){
	get_nxt(ptr);
    int i = 0,j = 0,pos = -1;
    int len1 = strlen(str), len2 = strlen(ptr);
    while(i < len1){
	    if(j == -1 || str[i] == ptr[j]){
            i++;
            j++;
        }else{
            j = nxt[j];
        }
        if(j == len2){
			pos = i - len2;
            break;
        }
    }
    if(len2 % (len2 - nxt[len2]) == 0 && len2 / (len2 - nxt[len2]) != 1){
		cout << "ptr最小循环节长度为" << len2 - nxt[len2] << endl;
	}else{
		cout << "不含循环节" << endl;
    }
    return pos;
}
void solve(){
	char str[maxn],ptr[maxn];
	scanf("%s %s",str,ptr);
	cout<<"ptr在str中第一次出现的位置是"<<kmp(str,ptr)<<endl;
}