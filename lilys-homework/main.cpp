#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
/*
 * Complete the 'lilysHomework' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int calcNumSwap(vector<int> arr,
                const vector<int> & sorted_arr,
                unordered_map<int, int> mapValIdx) {
    /**
     * We already know the sorted array. Our job is to make the unsorted array to be sorted using swap.
     *
     * Let us compare the elements between the original array and sorted array for each position i.
     *
     * If they match, no swap
     *
     * If they do not match, a swap needs to happen.
     *
     * But what to swap?
     *
     * In mapValIdx, we can inquiry the index of the value that should be in position i with the value at i (this value
     * is provided by the sorted array). Therefore let us swap the value that is should be located in i and the value
     * that is actually located in i
     */

    int numSwaps = 0;

    for (int i = 0; i < sorted_arr.size() - 1; ++i) {

        int expectedVal = sorted_arr[i];
        int realVal = arr[i];

        if (expectedVal == realVal) {
            continue;
        }

        // this is the real position of the expected value
        int realIdxExpectedVal = mapValIdx[expectedVal];

        swap(arr[realIdxExpectedVal], arr[i]);

        mapValIdx[realVal] = realIdxExpectedVal;
        mapValIdx[expectedVal] = i;

        numSwaps++;
    }

    return numSwaps;
}

int lilysHomework(vector<int> arr) {

    unordered_map<int, int> mapValIdx;
    for (int i = 0; i < arr.size(); ++i) {
        mapValIdx.insert(make_pair(arr[i], i));
    }

    // we know we want to sort the array to minimize the sum of abs(delta)
    /**
     * minimum swaps could either result in ascending or decending order.
     * So that we need to check both
     */
    auto ascending = arr;
    sort(ascending.begin(), ascending.end(), greater<int>());
    int numSwapsAscd = calcNumSwap(arr, ascending, mapValIdx);

    auto decending = arr;
    sort(decending.begin(), decending.end(), less<int>());
    int numSwapsDecd = calcNumSwap(arr, decending, mapValIdx);

    return min(numSwapsAscd, numSwapsDecd);
}

int main() {

    vector<int> arr = {3, 4, 2, 5, 1};

    lilysHomework(arr);

    return 0;
}
