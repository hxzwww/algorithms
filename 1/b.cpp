#include <iostream>
#include <stack>
#include <string>

int main(){
        std::stack <char> pspcheck;
        std::string sp;
        std::cin >> sp;
        bool psp = 1;
        for (char x: sp){
                if (x == '(' or x == '[' or x == '{'){
                        pspcheck.push(x);
                }
                else{
                        if (pspcheck.empty()){
                                psp = 0;
                                break;
                        }
                        if (x == ')'){
                                if (pspcheck.top() == '('){
                                        pspcheck.pop();
                                }
                                else{
                                        psp = 0;
                                        break;
                                }
                        }
                        if (x == ']'){
                                if (pspcheck.top() == '['){
                                        pspcheck.pop();
                                }
                                else{
                                        psp = 0;
                                        break;
                                }
                        }
                        if (x == '}'){
                                if (pspcheck.top() == '{'){
                                        pspcheck.pop();
                                }
                                else{
                                        psp = 0;
                                        break;
                                }
                        }
                }
        }
        if (!pspcheck.empty()) psp = 0;
        if (psp) std::cout << "yes" << "\n";
        else std::cout << "no" << "\n";
}
