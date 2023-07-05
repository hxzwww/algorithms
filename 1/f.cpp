#include <iostream>
#include <vector>
#include <fstream>
 
std::vector<long long> merge_off(std::vector<long long> a, long long &count);
std::vector<long long> merge_on(std::vector<long long> a, std::vector<long long> b, long long &count);
 
int main(){
    long long n;
    std::vector<long long> a;
    std::ifstream fin;
    fin.open("inverse.in");
    fin >> n;
    for (int i = 0; i < n; i++){
        long long num = 0;
        fin >> num;
        a.push_back(num);
    } 
    long long count = 0;
    a = merge_off(a, count);
    std::ofstream fout("inverse.out");
    fout<<count;
    std::cout<<count<<"\n";
    fin.close();
    fout.close();
}
 
std::vector<long long> merge_off(std::vector<long long> a, long long &count){
    if (a.size() == 1) return a;
    std::vector<long long> b, c;
    for (long long i = 0; i < (a.size() + 1) / 2; i++){
        b.push_back(long(a[i]));
    }
    for (long long i = (a.size() + 1) / 2; i < a.size(); i++){
        c.push_back(long(a[i]));
    }
    return merge_on(merge_off(b, count), merge_off(c, count), count);
}
 
 
std::vector<long long> merge_on(std::vector<long long> a, std::vector<long long> b, long long &count){
    std::vector<long long> c;
    long long i = 0, j = 0;
    while (i != a.size() && j != b.size()){
        if (a[i] <= b[j]){
            c.push_back(long(a[i]));
            i++;
            count += j;
        }
        else{
            c.push_back(long(b[j]));
            j++;
        }
    }
    while (i != a.size()){
        c.push_back(long(a[i]));
        count += j;
        i++;
    }
    while (j != b.size()){
        c.push_back(long(b[j]));
        j++;
    }
 
    return c;
}
