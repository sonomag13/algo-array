// LeetCode 1299. Replace Elements with Greatest Element on Right Side
// Easy

#include <vector>

using namespace std; 

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        
        vector<int> result; 
        
        int size = arr.size();         
        int maxVal = arr[size - 1];  
        
        result.push_back(-1); 
        
        // traverse from the second last to the left
        for (int i = size - 2; i >= 0; --i) {
            result.insert(result.begin(), maxVal); 
            maxVal = max(maxVal, arr[i]);
        }
        
        return result; 
        
    }
};