#include <iostream>
#include <stack>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    int N;
    std::cin >> N;
    std::stack<long long> sti;
    std::stack<long long> sth;
    long long maxS = 0;
    for (int i = 0; i <= N; i++){
        long long val;
        if (i == N){
            val = 0;
        }
        else{
            std::cin >> val;
        }
        int c = 0, it = -1;
        if (!sth.empty()){
            while (!sth.empty() && val < sth.top()){
                long long curS = sth.top() * (i - sti.top());
                if (curS > maxS) maxS = curS;
                sth.pop();
                it = sti.top();
                sti.pop();
                c++;

            }
        }
        if (c){
           sth.push(val);
           sti.push(it);
        }
        sth.push(val);
        sti.push(i);
     
    }   
    std::cout << maxS << "\n";
}

