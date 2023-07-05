#include <iostream>
#include <cstdio>

class Heap {

        long long* heap;
        int curHeapSize;
        int size;

    public:

        Heap (int k) {
            size = k + 1;
            curHeapSize = 0;
            heap = new long long [size];
        }

        ~Heap () {
            delete [] heap;
        }

        void exchange(int u, int v) {
            std::swap(heap[u], heap[v]);
        }

        void siftUp(int v) {
            while (v > 1) {
                if (heap[v] > heap[v / 2]) {
                    std::swap(heap[v/2], heap[v]);
                    v /= 2;
                }
                else break;
            }
        }

        void siftDown(int v) {
            while (2 * v <= curHeapSize) {
                int u = 2 * v;
                if (2 * v + 1 <= curHeapSize && heap[2 * v + 1] > heap[2 * v]) {
                    u = 2 * v + 1;
                }
                if (heap[u] > heap[v]) {
                    std::swap(heap[u], heap[v]);
                    v = u;
                }
                else break;
            }
        }

        void insert(long long x) {
            if (curHeapSize < size - 1) {
                ++curHeapSize;
                heap[curHeapSize] = x;
                siftUp(curHeapSize);
            }
            else if (x < heap[1]) {
                heap[1] = x;
                siftDown(1);
            }
        }

        long long getMin() {
            return heap[1];
        }

        void extractMin() {
            heap[1] = heap[curHeapSize];
            --curHeapSize;
            siftDown(1);
        }

        int* masOut() {
            int* mas = new int [size];
            for (int i = 0; i < size; ++i) {
                mas[i] = getMin();
                extractMin();
            }
            return mas;
        }
};

int main() {
    
    long long n, k, a, x, y;
    std::cin >> n >> k >> a >> x >> y;

    Heap h(k);

    for (int i = 0; i < n; i++) {

        a = (a * x + y) % 1073741824;
        h.insert(a);
    }
    
    int* answer = h.masOut();

    for (int i = 0; i < k; i++) {
        std::cout << answer[k - i - 1] << " ";
    }
}

