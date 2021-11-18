#include <iostream>
#include <cstdio>
#include <cstring>

class Heap {

        int* pointer;
        int* num;
        long long* heap;
        int curHeapSize;
        int curPointerSize;
        int heapSize;
        int pointerSize;

    public:

        Heap() {
            heapSize = 32;
            pointerSize = 32;
            curHeapSize = 0;
            curPointerSize = 0;
            pointer = new int [pointerSize];
            num = new int [heapSize];
            heap = new long long [heapSize];
        }

        Heap(const Heap& other) {
            *this = other;
        }

        Heap& operator=(const Heap& other) {
            if (this == &other) {
                return *this;
            }
            heapSize = other.heapSize;
            pointerSize = other.pointerSize;
            curHeapSize = other.curHeapSize;
            curPointerSize = other.curPointerSize;
            pointer = new int [pointerSize];
            num = new int [heapSize];
            heap = new long long [heapSize];
            memcpy(pointer, other.pointer, curPointerSize);
            memcpy(heap, other.heap, curHeapSize);
            memcpy(num, other.num, curHeapSize);
        }

        ~Heap () {
            delete [] heap;
            delete [] pointer;
            delete [] num;
        }

        void exchange(int u, int v) {
            std::swap(pointer[num[u]], pointer[num[v]]);
            std::swap(num[u], num[v]);
            std::swap(heap[u], heap[v]);
        }
        
        void siftUp(int v) {
            while (v > 1) {
                if (heap[v] < heap[v / 2]) {
                    
                    exchange(v, v / 2);
                    v /= 2;
                }
                else break;
            }
        }

        void siftDown(int v) {
            while (2 * v <= curHeapSize) {
                int u = 2 * v;
 
                if (2 * v + 1 <= curHeapSize && heap[2 * v + 1] < heap[2 * v]) {
                    u = 2 * v + 1;
                }
                if (heap[u] < heap[v]) {
 
                    exchange(u, v); 
                    v = u;
                }
                else break;
            }
        }

        void checkSize() {
            if (curHeapSize >= heapSize - 1) {
                updateHeapSize();
            }
            if (curPointerSize >= pointerSize -1) {
                updatePointerSize();
            }
        }

        void updateHeapSize() {
            heapSize = std::min(heapSize * 2, 1000000);
            long long* heapCopy = new long long [heapSize];
            int* numCopy = new int [heapSize];
            memcpy(heapCopy, heap, (curHeapSize + 1) * sizeof(long long));
            memcpy(numCopy, num, (curHeapSize + 1) * sizeof(int));
            delete [] heap;
            delete [] num;
            heap = heapCopy;
            num = numCopy;
        }

        void updatePointerSize() {
            pointerSize = std::min(pointerSize * 2, 1000000);
            int* pointerCopy = new int [pointerSize];
            memcpy(pointerCopy, pointer, (curPointerSize + 1) * sizeof(int));
            delete [] pointer;
            pointer = pointerCopy;
        }

        void insert(long long x) {
            checkSize();
            ++curHeapSize;
            ++curPointerSize;
            num[curHeapSize] = curPointerSize;
            heap[curHeapSize] = x;
            pointer[curPointerSize] = curHeapSize;
            siftUp(curHeapSize);
        }

        long long getMin() {
            checkSize();
            ++curPointerSize;
            return heap[1];
        }

        void extractMin() {
            checkSize();
            ++curPointerSize;
            exchange(1, curHeapSize);
            --curHeapSize;
            siftDown(1);
        }

        void decreaseKey(int v, int delta) {
            checkSize();
            ++curPointerSize;
            heap[pointer[v]] -= delta;
            siftUp(pointer[v]);
            siftDown(pointer[v]);
        }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);std::cout.tie(nullptr);

    int q = 0;
    std::cin >> q;

    Heap h;

    for (int i = 1; i <= q; ++i) {

        std::string cmd;
        std::cin >> cmd;

        if (cmd == "insert") {
            long long x;
            std::cin >> x;
            h.insert(x);
        }
        if (cmd == "getMin") {
            printf("%lld\n", h.getMin());
        }
        if (cmd == "extractMin") {
            h.extractMin();
        }
        if (cmd == "decreaseKey") {
            int v, delta;
            std::cin >> v >> delta;
            h.decreaseKey(v, delta);
        }
    }
    return 0;
}            
