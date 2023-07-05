#include <iostream>
#include <cstdio>
#include <cstring>

struct heel {
    long long val = 0;
    int iMax = 0;
    int iMin = 0;
};

class Heap {

        heel* heapMax;
        heel* heapMin;
        int curSize;
        int size;

    public:

        Heap () {
            size = 2;
            curSize = 0;
            heapMax = new heel [size];
            heapMin = new heel [size];
        }

        ~Heap () {
            delete [] heapMax;
            delete [] heapMin;
        }

        void exchMax(int v, int u) {
            std::swap(heapMin[heapMax[v].iMin].iMax, heapMin[heapMax[u].iMin].iMax);
            long long tmp = heapMax[v].iMin;
            heapMax[v] = heapMin[heapMax[u].iMin];
            heapMax[u] = heapMin[tmp];
        }

        void exchMin(int v, int u) {
            std::swap(heapMax[heapMin[v].iMax].iMin, heapMax[heapMin[u].iMax].iMin);
            long long tmp = heapMin[v].iMax;
            heapMin[v] = heapMax[heapMin[u].iMax];
            heapMin[u] = heapMax[tmp];
        }

        void siftUpMin(int v) {
            while (v > 1) {
                if (heapMin[v].val < heapMin[v/2].val) {

                    exchMin(v, v/2);

                    v /= 2;
                }
                else break;
            }
        }

        void siftUpMax(int v) {
            while (v > 1) {
                if (heapMax[v].val > heapMax[v/2].val) {

                    exchMax(v, v/2);

                    v /= 2;
                }
                else break;
            }
        }

        void siftDownMin(int v) {
            while (2 * v <= curSize) {
                int u = 2 * v;
                if (2 * v + 1 <= curSize && heapMin[2 * v + 1].val < heapMin[2 * v].val) {
                    u = 2 * v + 1;
                }
                if (heapMin[u].val < heapMin[v].val) {

                    exchMin(v, u);

                    v = u;
                }
                else break;
            }
        }

        void siftDownMax(int v) {
            while (2 * v <= curSize) {
                int u = 2 * v;
                if (2 * v + 1 <= curSize && heapMax[2 * v + 1].val > heapMax[2 * v].val) {
                    u = 2 * v + 1;
                }
                if (heapMax[u].val > heapMax[v].val) {

                    exchMax(v, u); 

                    v = u;
                }
                else break;
            }

        }

        void checkSize() {
            if (curSize >= size - 1) {
                updateSize();
            }
        }

        void updateSize() {
            heel* heapMaxCopy = new heel [std::min(size * 2, 100001)];
            heel* heapMinCopy = new heel [std::min(size * 2, 100001)];
            for (int i = 0; i < size; i++) {
                heapMaxCopy[i] = heapMax[i];
                heapMinCopy[i] = heapMin[i];
            }
            size = std::min(size * 2, 100001);
            delete [] heapMax;
            delete [] heapMin;
            heapMax = heapMaxCopy;
            heapMin = heapMinCopy;
        }

        void insert(long long x) {
            checkSize();
            ++curSize;
            heel elem;
            elem.val = x;
            elem.iMax = curSize;
            elem.iMin = curSize;
            heapMax[curSize] = elem;
            heapMin[curSize] = elem;
            siftUpMax(curSize);
            siftUpMin(curSize);
        }

        long long getMin() {

            long long answer = heapMin[1].val;

            exchMin(1, curSize);

            long long tmp = heapMin[curSize].iMax;

            exchMax(tmp, curSize);

            --curSize;

            siftDownMin(1);

            if (heapMax[tmp].val > heapMax[curSize + 1].val) {
                siftUpMax(tmp);
            }
            else {
                siftDownMax(tmp);
            }

            return answer;
        }


        long long getMax() {

            long long answer = heapMax[1].val;

            exchMax(1, curSize);

            long long tmp = heapMax[curSize].iMin;

            exchMin(tmp, curSize);

            --curSize;
            
            siftDownMax(1);

            if (heapMin[tmp].val > heapMin[curSize + 1].val) {
                siftDownMin(tmp);
            }
            else {
                siftUpMin(tmp);
            }

            return answer;
        }
};

long long getNumber(std::string cmd) {
    long long result = 0;
    for (int i = 7; i < cmd.size() - 1; ++i) {
        result = result * 10 + (cmd[i] - '0');
    }
    return result;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int q;
    std::cin >> q;

    Heap h;

    for (int i = 1; i <= q; ++i) {

        std::string cmd;
        std::cin >> cmd;

        if (cmd[0] == 'I') {

            h.insert(getNumber(cmd));
        }
        if (cmd == "GetMin") {
            printf("%lld\n", h.getMin());
        }
        if (cmd == "GetMax") {
            printf("%lld\n", h.getMax());
        }
    }
    return 0;
}

