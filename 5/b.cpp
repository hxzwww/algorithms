#include <iostream>
#include <utility>
#include <vector>

using std::vector;


// dp_by_val - динамика, в которой расположены элементы начальной
// последовательности в порядке убывания
// dp_by_ind - то же самое, только хранится индекс этого элемента в начальной
// последовательности
// prev_elem - очевидно, для i-го элемента хранится соседний слева (в момент
// добавления) элемент в dp_by_val

// пересчет - вставка в обе dp при помощи бинпоиска

// ответ: последний элемент в dp - первый элемент в искомой НВП; при помощи 
// prev_elem восстанавливаем ответ


void bin_insert(vector<int>& dp_by_val, vector<int>& dp_by_ind, int val, 
        vector<int>& prev_elem, int i, int n) {
    if (dp_by_val[0] < val) {
        dp_by_val[0] = val;
        dp_by_ind[0] = i;
        prev_elem[i] = n;
        return;
    }
    int l = 0, r = n - 1, mid;
    while (l != r) {
        mid = (l + r) / 2 + 1;
        if (dp_by_val[mid - 1] >= val && dp_by_val[mid] < val) {
            dp_by_val[mid] = val;
            dp_by_ind[mid] = i;
            prev_elem[i] = dp_by_ind[mid - 1];
            return;
        }
        if (dp_by_val[mid] >= val) {
            l = mid;
        }
        if (dp_by_val[mid] < val) {
            r = mid - 1;
        }
    }
}

void count(vector<int>& array, vector<int>& dp_by_val, vector<int>& dp_by_ind,
        vector<int>& prev_elem, int n) {
    for (int i = 0; i < n; ++i) {
        bin_insert(dp_by_val, dp_by_ind, array[i], prev_elem, i, n);
    }
}

std::pair<int, vector<int>> solve(int n, vector<int>& array) {
    vector<int> dp_by_val(n, -1e9);                                              
    vector<int> prev_elem(n);                                                    
    vector<int> dp_by_ind(n);                                                    
    count(array, dp_by_val, dp_by_ind, prev_elem, n);                            
    int len;                                                                     
    for (int i = 0; i < n; ++i) {                                                
        if (dp_by_val[i + 1] == -1e9 || i == n - 1) {                            
            len = i + 1;                                                         
            break;                                                               
        }                                                                        
    }                                                                            
    vector<int> sequence(len);                                                   
    sequence[len - 1] = dp_by_ind[len - 1];                                      
    for (int i = len - 1; i > 0; --i) {                                          
        sequence[i - 1] = prev_elem[sequence[i]];                                
    }

    return std::make_pair(len, sequence);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    std::pair<int, vector<int>> result = solve(n, array);
    std::cout << result.first << '\n';
    for (int i = 0; i < result.first; ++i) {
        std::cout << result.second[i] + 1 << ' ';
    }
}

