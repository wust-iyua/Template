#include <bits/stdc++.h>
#define de(x)   cerr << "  debug  " << #x << "  ==  " << x << endl;
using namespace std;
typedef long long  LL;
const int maxn = 2e5 + 7;
template<typename T, const size_t mxsiz = 10007>
class Heap {
    private :

    size_t top;
    T arr[mxsiz];
    public :

    bool empty() {return top == 0;}
    void Init() {
        top = 0;
    }
    void Insert(T x) {
        cout << "Insert  " << x << endl;
        arr[++ top] = x;
        size_t pos = top;
        while(pos > 1) {
            size_t id = pos >> 1;
            // cout << pos << ' ' << id << endl;
            if(arr[id] < arr[pos]) {
                swap(arr[id], arr[pos]);
                pos = id;
            } else return ;
        }
    }
    T Front() {
        return arr[1];
    }
    void Del() {
        swap(arr[1], arr[top]);
        -- top;
        size_t pos = 1;
        while(pos < top) {
            int id = pos << 1;
            if(id > top) return ;
            if(id < top && arr[id] < arr[id + 1]) ++ id;
            if(arr[pos] < arr[id]) {
                swap(arr[pos], arr[id]);
                pos = id;
            } else return ;
        }
    }
};
void solve () {
    int n; while(cin >> n) {
        Heap<int> Q;
        Q.Init();
        for (int i = 1; i <= n; ++ i) {
            Q.Insert(rand() % 11);
        }
        while(!Q.empty()) {
            cout << Q.Front() << ' ';
            Q.Del();
        }
        cout << endl;
    }
}
int main () {
    int T = 1;
    // scanf("%d", &T);
    while(T --) {
        solve ();
    }
    #ifdef iyua
        system("pause");
    #endif 
    return 0;
}