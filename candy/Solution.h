// 135 Candy

#include <vector>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        
        int n = ratings.size(); 

        if (n == 0) {
            return 0; 
        }

        vector<int> candies(n, 1);

        // Strategy: 
        // 1. sweep from left to right such that sure every pair of ratings[i] and ratings[i + 1] satisfy the conditions
        // 2. sweep from right to left such that sure every pair of ratings[i - 1] and ratings[i] satisfy the conditions
        // 
        // Specifically:
        // - during the first sweep, candies[i] is set based on candies[i - 1]. e.g.
        //              ratings = {3, 2, 1}
        //              candies = {1, 1, 1} after first sweep
        //   when setting candies[1], it reference only candies[0] and ratings[0], and has no idea of ratings[2] and candies[2]
        // 
        // - thereby in the second sweep, we reset candies[i] based on ratings[i + 1] and candies[i + 1]
        //              if ratings[i + 1] < ratings[i] no action is needed. 
        //              e.g. ratings = {1, 2, 3} and candies = {1, 2, 3}
        //              
        //              if ratings[i] < ratings[i + 1] we just incraese ratings[i] by 1, which is the minimum increment to satisfy
        //              the conditions
        //              e.g. ratings = {3, 2, 1}, candies = {1, 1, 1} after first sweep and candies = {3, 2, 1} after second sweep
        //              
        // ratings = {1, 2, 3} and candies[1] < candies[3] is ganrantteed in the first sweep; no need to adjust it in the second sweep
        // ratings = {3, 2, 1} and ratings[1] > ratings[2], candies[1] < candies[3] is NOT ganrantteed

        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1; // minimum increment to satisfy i and its left neighbor
            }
        }

        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                // candies[i] could be a local maximum
                // or it need to increase by 1
                candies[i] = max(candies[i], candies[i + 1] + 1); 
            }
        }

        int sum = accumulate(candies.begin(), candies.end(), 0);

        return sum; 
    }
};