// LeetCode 1346. Check If N and Its Double Exist
// Easy

#include <algorithm>
#include <set>
#include <vector>

using namespace std; 

class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        
        // sort the array in the descending order, such that
        // the large value enters in the comp first
        auto comp = [] (const int& val1, const int& val2) {
            return abs(val1) > abs(val2); 
        };
        
        sort(arr.begin(), arr.end(), comp);
        
        set<int> visited; 
        
        for (auto val : arr) {            
            if (visited.find(val * 2) != visited.end()) {
                return true;
            }            
            visited.insert(val);
        }
        
        return false; 
        
    }
};