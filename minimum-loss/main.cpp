#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumLoss' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts LONG_INTEGER_ARRAY price as parameter.
 */

int minimumLoss(vector<long> price) {
    /**
     * the trick of this problem is that, if we sort the price, the answer
     * must be the delta of two neighboring elements in the (sorted) price. 
     * 
     * But how to know which two neighboring elements to use? We can
     * - compute all the deltas that satisify the requirement of years of buying and     
     *   selling 
     * - return the minimum delta
     */
    long long minLoss{static_cast<long long>(2e16)};
    
    unordered_map<long long, int> mapPriIdx; 
    for (int i = 0; i < price.size(); ++i) {
        mapPriIdx.insert(make_pair(price[i], i));
    }
    
    sort(price.begin(), price.end(), less<int>());
    
    for (int i = 1; i < price.size(); ++i) {
        
        long long priceBuying = price[i];
        long long priceSelling = price[i - 1];
        
        int yearBuying{mapPriIdx[priceBuying]};
        int yearSelling{mapPriIdx[priceSelling]};
        
        if (yearSelling > yearBuying) {
            minLoss = min(minLoss, priceBuying - priceSelling);
        }
        
    }
    
    return minLoss; 
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string price_temp_temp;
    getline(cin, price_temp_temp);

    vector<string> price_temp = split(rtrim(price_temp_temp));

    vector<long> price(n);

    for (int i = 0; i < n; i++) {
        long price_item = stol(price_temp[i]);

        price[i] = price_item;
    }

    int result = minimumLoss(price);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
