// int_max   (1 << 31) - 1  取 30
// LL_max   (1 << 63) - 1   取 62
// uLL_max  (1 << 64) - 1   取 63
// 注意求 kth  rank之时必须要提前 rebuild
template<typename T, const size_t len = 30>
class LineBase {
    public :
        int cnt;
        T d[len + 1], p[len + 1];
    	T f[len + 1]; 前缀线性基
        bool zero, build;
        void Init() {
            for (int i = 0; i < len + 1; ++ i) d[i] = p[i] = f[i] = 0;
            zero = build = false;
            cnt = 0;
        }
        void Insert(T x) {
            for (int i = len; ~i; -- i) {
                if(!((x >> i) & 1)) continue;
                if(!d[i]) {
                    d[i] = x;
                    ++ cnt;
                    return ;
                }
                x ^= d[i];
            }
            zero = true;
        }
    // 判断是否能被异或出来
        bool Exist(T x) {
            for (int i = len; ~i; -- i) {
                if(((x >> i) & 1)) {
                    if(d[i]) x ^= d[i];
                    else return false;
                }
            }
            return true;
        }
        void Rebuild() {
            cnt = 0;
            build = true;
            for (int i = len; ~i; -- i) {
                for (int j = i - 1; ~j; -- j) {
                    if((d[i] >> j) & 1) d[i] ^= d[j];
                }
            }
            for (int i = 0; i <= len; ++ i) {
                if(d[i]) p[cnt ++] = d[i];
            }
        }
    // 查询异或最大
        T mx() {
            T res = 0;
            for (int i = len; ~i; -- i) res = max(res, res ^ d[i]);
            return res;
        }
        T mn() {
            if(zero) return 0;
            for (int i = 0; i <= len; ++ i) {
                if(d[i]) return d[i];
            }
            return -1;
        }
        T kth(T k) {
            if(!build) Rebuild();
            if(k >= (((T)1) << cnt)) return -1; // 无解
            T res = 0;
            for (int i = len; ~i; -- i) {
                if((k >> i) & 1) res ^= p[i];
            }
            return res;
        }
        T kmx(T k) {
            if(!build) Rebuild();
            if(k <= 0) return -1;
            T num = (((T)1) << cnt);
            if(!zero) -- num;
            return kmn(num - k + 1);
        }
        T kmn(T k) {
            if(!build) Rebuild();
            if(k <= 0) return -1;
            return k - zero ? kth(k - zero) : 0;
        }
        // 从小到大排  且要求这个数必须能被线性基异或出来才可以查询rank
        T Rank(T x) {
            if(!build) Rebuild();
            T res = 0;
            for (int i = cnt - 1; ~i; -- i) {
                if(x >= p[i]) {
                    res += (((T)1) << i);
                    x ^= p[i];
                }
            }
            return res + zero;
        }
        // 获取此时能获得的元素的个数
        T checkall() {
            return (((T)1) << cnt) - (!zero);
        }
    	//  前缀线性基
    	// T f[len + 1]; 放前面
        void Insert(int x, int id) {
            for (int i = 30; ~i; -- i) {
                if(!((x >> i) & 1)) continue;
                if(!d[i]) {
                    d[i] = x;
                    f[i] = id;
                    return ;
                } else if(f[i] < id) {
                    swap(f[i], id);
                    swap(x, d[i]);
                }
                x ^= d[i];
            }
        }
    	int query(int l) {
            int x = 0;
            for (int i = 30; ~i; -- i) {
                if(d[i] && f[i] >= l)
                x = max(x, x ^ d[i]);
            }
            return x;
    	}
};