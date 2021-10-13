#include <stack>
#include <string>

using namespace std; 

class Solution {
public:
    string addBinary(string a, string b) {
               
        string result = ""; 
        
        stack<int> stk_a = buildStack(a); 
        stack<int> stk_b = buildStack(b);
                        
        int carry = 0; 
        
        while (!stk_a.empty() || !stk_b.empty() || carry != 0) { 
            
            if (!stk_a.empty()) {
                carry += stk_a.top();
                stk_a.pop();
            }
            
            if (!stk_b.empty()) {
                carry += stk_b.top();
                stk_b.pop();                
            }
            
            result = to_string(carry%2) + result;            
            carry = carry / 2;             
        }
        
        return result;
        
    }
    
private:        
    stack<int> buildStack(const string& str) {
        stack<int> stk; 
        for (int i = 0; i < str.length(); ++i) {
            stk.push(str[i] - '0');
        }
        return stk; 
    }
    
};