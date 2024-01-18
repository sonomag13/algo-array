#include <iostream>
#include <vector>
using namespace std;

/*
 * Complete the 'gridlandMetro' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY track
 */

unsigned long gridlandMetro(int n, int m, int k, vector<vector<int>> track) {

    /**
     * The core of this this problem is LeetCode Merge Interval.
     *
     * The tracks may or may not overlap. We need to merge them to avoid over-counting the grid node occupied by train
     */

    // we need to cast int to unsigned long to void overflow. The problem is flawed in Hankerrank
    unsigned long total = static_cast<unsigned long>(m) * static_cast<unsigned long>(n);

    // first, let us put all the intervals in the save row together
    unordered_map<int, vector<pair<int, int>>> mapRowTrack;
    for (auto & curTrack : track) {

        int row = curTrack[0];
        int col1 = min(curTrack[1], curTrack[2]);
        int col2 = max(curTrack[1], curTrack[2]);

        if (mapRowTrack.find(row) != mapRowTrack.end()) {
            mapRowTrack[row].push_back(make_pair(col1, col2));

        }
        else {
            mapRowTrack.insert(make_pair(row, vector<pair<int, int>>{{col1, col2}}));
        }
    }

    auto cmp = [](const pair<int, int> & p1, const pair<int, int> & p2) {
        // comparator to sort vector

        return p1.first < p2.first;
    };

    // second, for tracks on the save page, we need to merge them. This is the classical merge interval problem
    for (auto & ele : mapRowTrack) {
        vector<pair<int, int>> intervals1 = ele.second;

        // sort based on the lower boundary of the interval
        sort(intervals1.begin(), intervals1.end(), cmp);

        vector<pair<int, int>> intervals2;  // for the merged interval
        intervals2.push_back(intervals1[0]);
        for (int i = 1; i < intervals1.size(); ++i) {
            auto prePair = intervals2.back();
            auto curPair = intervals1[i];
            if (curPair.first > prePair.second + 1) {
                intervals2.push_back(curPair);  // cannot merge
            }
            else {
                // can merge
                int n = intervals2.size();
                intervals2[n - 1].second = max(curPair.second, prePair.second);
            }
        }

        // at this point, all the intervals are merged, and it is safe now to subtract
        for (auto & interval : intervals2) {
            total -= interval.second - interval.first + 1;
        }

    }

    return total;
}


int main() {

    int m = 6;
    int n = 6;
    int k = 3;
    vector<vector<int>> track = {{1, 3, 2},
                                 {1, 1, 2},
                                 {1, 5, 6},
                                 {2, 1, 3},
                                 {2, 4, 6},
                                 {5, 2, 1},
                                 {5, 5, 6}};

    cout << "num of lamppost = " << gridlandMetro(n, m, k, track) << '\n';

    return 0;
}
