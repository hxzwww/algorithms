#include <iostream>
#include <cstdio>
#include <cstring>
 
class Heap {

    int heapSize = 0;
    int pointerSize = 0;
    int heap_bufferSize = 2;
    int pointer_bufferSize = 2; 
    int* pointer = new int [pointer_bufferSize];
    int* num = new int [heap_bufferSize];
    long long* heap = new long long [heap_bufferSize];
 
    void exchange(int u, int v) {
        std::swap(pointer[num[u]], pointer[num[v]]);
        std::swap(num[u], num[v]);
        std::swap(heap[u], heap[v]);
    }
 
public:
 
    Heap() = default;
     
    Heap(const Heap& other) : heap_bufferSize(other.heap_bufferSize),
            pointer_bufferSize(other.pointer_bufferSize), 
            heapSize(other.heapSize), pointerSize(other.pointerSize),
            pointer(new int [pointer_bufferSize]),
            num(new int [heap_bufferSize]),
            heap(new long long [heap_bufferSize]) {
        memcpy(pointer, other.pointer, pointerSize);
        memcpy(heap, other.heap, heapSize);
        memcpy(num, other.num, heapSize);
    }
 
    Heap& operator=(const Heap& other) {
        if (this == &other) {
            return *this;
        }
        delete [] heap;
        delete [] pointer;
        delete [] num;
        heap_bufferSize = other.heap_bufferSize;
        pointer_bufferSize = other.pointer_bufferSize;
        heapSize = other.heapSize;
        pointerSize = other.pointerSize;
        pointer = new int [pointer_bufferSize];
        num = new int [heap_bufferSize];
        heap = new long long [heap_bufferSize];
        memcpy(pointer, other.pointer, pointerSize);
        memcpy(heap, other.heap, heapSize);
        memcpy(num, other.num, heapSize);
    }
 
    ~Heap () {
        delete [] heap;
        delete [] pointer;
        delete [] num;
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
            while (2 * v <= heapSize) {
                int u = 2 * v;
                if (u + 1 <= heapSize && heap[u + 1] < heap[u]) {
                    ++u;
                }
                if (heap[u] < heap[v]) {
                    exchange(u, v);
                    v = u;
                }
                else break;
            }
        }
 
        void checkSize() {
            if (heapSize >= heap_bufferSize - 1) {
                updateHeapSize();
            }
            if (pointerSize >= pointer_bufferSize -1) {
                updatePointerSize();
            }
        }
 
        void updateHeapSize() {
            heap_bufferSize = std::min(heap_bufferSize * 2, 1000000);
            long long* heapCopy = new long long [heap_bufferSize];
            int* numCopy = new int [heap_bufferSize];
            memcpy(heapCopy, heap, (heapSize + 1) * sizeof(long long));
            memcpy(numCopy, num, (heapSize + 1) * sizeof(int));
            delete [] heap;
            delete [] num;
            heap = heapCopy;
            num = numCopy;
        }
 
        void updatePointerSize() {
            pointer_bufferSize = std::min(pointer_bufferSize * 2, 1000000);
            int* pointerCopy = new int [pointer_bufferSize];
            memcpy(pointerCopy, pointer, (pointerSize + 1) * sizeof(int));
            delete [] pointer;
            pointer = pointerCopy;
        }

    void insert(int x) {
        checkSize();
        ++heapSize;
        ++pointerSize;
        num[heapSize] = pointerSize;
        heap[heapSize] = x;
        pointer[pointerSize] = heapSize;
        siftUp(heapSize);
    }
 
    long long getMin() {
        checkSize();
        ++pointerSize;
        return heap[1];
    }
 
    void extractMin() {
        checkSize();
        ++pointerSize;
        exchange(1, heapSize);
        --heapSize;
        siftDown(1);
    }
 
    void decreaseKey(int v, int delta) {
        checkSize();
        ++pointerSize;
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
            int x;
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

