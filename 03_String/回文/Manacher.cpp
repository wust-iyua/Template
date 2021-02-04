//文本串  答案长度  答案起始点  答案串  字符串每个位置的最大半径容器
void manacher(string& str, int& mxlen, int& st, string& ans, vector<int>& v){
    mxlen = 0, st = 0, ans = "", v.clear();
    //处理成新串
	string tmp = "$#";
    int sz = str.size();
    for(int i = 0; i < sz; ++ i){
		tmp += str[i];
        tmp += '#';
    }
    //辅助变量  
    //最右边下标  最右下标的中间点  目前长度  目前起始点
    int mx = 0, id = 0, len = 0, pos = 0;
    sz = tmp.size();
    vector<int> p(sz,0);
    
    for(int i = 1;i < sz; i ++){
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while(i + p[i] < sz && tmp[i + p[i]] == tmp[i - p[i]]){p[i] ++;}
        
        if(mx < i + p[i]){//此处和下面的小于号代表多种情况找第一个出现的
            mx = i + p[i];//小于等于则代表多种情况找最后出现的
            id = i;
        }
        if(len < p[i]){
            len = p[i];
            pos = i;
        }
    }
    //放入每个点的扩展出来的最大半径
    for(int i = 2; i < sz; i += 2) {
        v.push_back(p[i] - 1);
    }
    mxlen = len - 1;
    st = (pos - len) / 2;
    //substr简易用法  str.substr(st, len)  
    //返回str下标从st开始后面长度为len的串  最长截至到str.end()
    //len可以省略 默认到结尾
    ans = str.substr(st, mxlen);
}