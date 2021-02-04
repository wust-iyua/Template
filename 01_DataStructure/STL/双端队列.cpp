template<typename T, const size_t MXSIZ = 100007>
class Dqueue {
    public :
        Dqueue() : posl(1), posr(0) {}
        T& front() {
            return val[posr];
        }
        T& back() {
            return val[posl];
        }
        bool empty() {
            return posl > posr;
        }
        void pop() {
            -- posr;
        }
        void pop_back() {
            ++ posl;
        }
        void push(const T& x) {
            val[++ posr] = x;
        }
        void clear() {
            posl = 1, posr = 0;
        }
    private :
        T val[MXSIZ];
        int posl, posr;
};