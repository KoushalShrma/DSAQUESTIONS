#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

// 6. Minimum Window Substring - String (Hard)
class Solution6_Hard {
public:
    // Brute Force - Check all substrings O(n³) time, O(m) space
    string minWindow_bruteforce(string s, string t) {
        if(s.length() < t.length()) return "";
        
        unordered_map<char, int> tCount;
        for(char c : t) {
            tCount[c]++;
        }
        
        string result = "";
        int minLen = INT_MAX;
        
        // har possible substring check karte hai
        for(int i = 0; i < s.length(); i++) {
            for(int j = i; j < s.length(); j++) {
                unordered_map<char, int> windowCount;
                
                // current window ka count
                for(int k = i; k <= j; k++) {
                    windowCount[s[k]]++;
                }
                
                // check if valid window
                bool isValid = true;
                for(auto& pair : tCount) {
                    if(windowCount[pair.first] < pair.second) {
                        isValid = false;
                        break;
                    }
                }
                
                if(isValid && j - i + 1 < minLen) {
                    minLen = j - i + 1;
                    result = s.substr(i, minLen);
                }
            }
        }
        
        return result;
    }
    
    // Better - Sliding window O(n) time, O(m+n) space
    string minWindow_better(string s, string t) {
        if(s.empty() || t.empty()) return "";
        
        unordered_map<char, int> tCount;
        for(char c : t) {
            tCount[c]++;
        }
        
        int required = tCount.size();
        int left = 0, right = 0;
        int formed = 0;
        
        unordered_map<char, int> windowCounts;
        
        int minLen = INT_MAX;
        int minLeft = 0;
        
        while(right < s.length()) {
            // expand window
            char c = s[right];
            windowCounts[c]++;
            
            if(tCount.count(c) && windowCounts[c] == tCount[c]) {
                formed++;
            }
            
            // contract window
            while(left <= right && formed == required) {
                if(right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                char leftChar = s[left];
                windowCounts[leftChar]--;
                
                if(tCount.count(leftChar) && windowCounts[leftChar] < tCount[leftChar]) {
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }
        
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
    
    // Optimal - Optimized sliding window O(n) time, O(m) space
    string minWindow(string s, string t) {
        if(s.empty() || t.empty() || s.length() < t.length()) return "";
        
        vector<int> tCount(128, 0);
        int required = 0;
        
        for(char c : t) {
            if(tCount[c] == 0) required++;
            tCount[c]++;
        }
        
        int left = 0, right = 0;
        int formed = 0;
        int minLen = INT_MAX;
        int minStart = 0;
        
        vector<int> windowCounts(128, 0);
        
        while(right < s.length()) {
            char c = s[right];
            windowCounts[c]++;
            
            if(tCount[c] > 0 && windowCounts[c] == tCount[c]) {
                formed++;
            }
            
            while(formed == required) {
                if(right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }
                
                char leftChar = s[left];
                windowCounts[leftChar]--;
                
                if(tCount[leftChar] > 0 && windowCounts[leftChar] < tCount[leftChar]) {
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }
        
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};

// 7. Regular Expression Matching - String (Hard)
class Solution7_Hard {
public:
    // Brute Force - Recursive approach O(2^(n+m)) time, O(n+m) space
    bool isMatch_bruteforce(string s, string p) {
        return matchHelper(s, p, 0, 0);
    }
    
    bool matchHelper(string s, string p, int i, int j) {
        // pattern khatam ho gaya
        if(j >= p.length()) {
            return i >= s.length();
        }
        
        // check if current character matches
        bool currentMatch = (i < s.length()) && 
                           (p[j] == s[i] || p[j] == '.');
        
        // agar next character '*' hai
        if(j + 1 < p.length() && p[j + 1] == '*') {
            // '*' ko zero times use karte hai ya ek baar use karte hai
            return matchHelper(s, p, i, j + 2) || 
                   (currentMatch && matchHelper(s, p, i + 1, j));
        } else {
            // simple character match
            return currentMatch && matchHelper(s, p, i + 1, j + 1);
        }
    }
    
    // Better - Memoization O(n*m) time, O(n*m) space
    bool isMatch_better(string s, string p) {
        vector<vector<int>> memo(s.length() + 1, vector<int>(p.length() + 1, -1));
        return dpHelper(s, p, 0, 0, memo);
    }
    
    bool dpHelper(string s, string p, int i, int j, vector<vector<int>>& memo) {
        if(memo[i][j] != -1) {
            return memo[i][j];
        }
        
        bool result;
        
        if(j >= p.length()) {
            result = (i >= s.length());
        } else {
            bool currentMatch = (i < s.length()) && 
                               (p[j] == s[i] || p[j] == '.');
            
            if(j + 1 < p.length() && p[j + 1] == '*') {
                result = dpHelper(s, p, i, j + 2, memo) || 
                        (currentMatch && dpHelper(s, p, i + 1, j, memo));
            } else {
                result = currentMatch && dpHelper(s, p, i + 1, j + 1, memo);
            }
        }
        
        memo[i][j] = result;
        return result;
    }
    
    // Optimal - Bottom-up DP O(n*m) time, O(n*m) space
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[m][n] = true; // empty string matches empty pattern
        
        // pattern ending with '*' can match empty string
        for(int j = n - 1; j >= 0; j--) {
            if(j + 1 < n && p[j + 1] == '*') {
                dp[m][j] = dp[m][j + 2];
            }
        }
        
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                bool currentMatch = (p[j] == s[i] || p[j] == '.');
                
                if(j + 1 < n && p[j + 1] == '*') {
                    dp[i][j] = dp[i][j + 2] || (currentMatch && dp[i + 1][j]);
                } else {
                    dp[i][j] = currentMatch && dp[i + 1][j + 1];
                }
            }
        }
        
        return dp[0][0];
    }
};

// 8. Merge k Sorted Arrays - Array (Hard)
class Solution8_Hard {
public:
    // Brute Force - Merge one by one O(n*k²) time, O(1) space
    vector<int> mergeKArrays_bruteforce(vector<vector<int>>& arrays) {
        if(arrays.empty()) return {};
        
        vector<int> result = arrays[0];
        
        // har array ko result ke saath merge karte hai
        for(int i = 1; i < arrays.size(); i++) {
            result = mergeTwoArrays(result, arrays[i]);
        }
        
        return result;
    }
    
    vector<int> mergeTwoArrays(vector<int>& arr1, vector<int>& arr2) {
        vector<int> merged;
        int i = 0, j = 0;
        
        while(i < arr1.size() && j < arr2.size()) {
            if(arr1[i] <= arr2[j]) {
                merged.push_back(arr1[i++]);
            } else {
                merged.push_back(arr2[j++]);
            }
        }
        
        while(i < arr1.size()) merged.push_back(arr1[i++]);
        while(j < arr2.size()) merged.push_back(arr2[j++]);
        
        return merged;
    }
    
    // Better - Divide and conquer O(n*k*logk) time, O(logk) space
    vector<int> mergeKArrays_better(vector<vector<int>>& arrays) {
        if(arrays.empty()) return {};
        
        return divideAndMerge(arrays, 0, arrays.size() - 1);
    }
    
    vector<int> divideAndMerge(vector<vector<int>>& arrays, int start, int end) {
        if(start == end) {
            return arrays[start];
        }
        
        if(start + 1 == end) {
            return mergeTwoArrays(arrays[start], arrays[end]);
        }
        
        int mid = start + (end - start) / 2;
        vector<int> left = divideAndMerge(arrays, start, mid);
        vector<int> right = divideAndMerge(arrays, mid + 1, end);
        
        return mergeTwoArrays(left, right);
    }
    
    // Optimal - Min heap approach O(n*k*logk) time, O(k) space
    vector<int> mergeKArrays(vector<vector<int>>& arrays) {
        vector<int> result;
        
        // min heap: {value, array_index, element_index}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;
        
        // har array ka first element heap mein add karte hai
        for(int i = 0; i < arrays.size(); i++) {
            if(!arrays[i].empty()) {
                minHeap.push({arrays[i][0], i, 0});
            }
        }
        
        while(!minHeap.empty()) {
            auto top = minHeap.top();
            minHeap.pop();
            
            int val = top[0];
            int arrayIdx = top[1];
            int elemIdx = top[2];
            
            result.push_back(val);
            
            // agar same array mein aur elements hai
            if(elemIdx + 1 < arrays[arrayIdx].size()) {
                minHeap.push({arrays[arrayIdx][elemIdx + 1], arrayIdx, elemIdx + 1});
            }
        }
        
        return result;
    }
};

// 9. Edit Distance - String (Hard)
class Solution9_Hard {
public:
    // Brute Force - Recursive approach O(3^max(m,n)) time, O(max(m,n)) space
    int minDistance_bruteforce(string word1, string word2) {
        return editHelper(word1, word2, 0, 0);
    }
    
    int editHelper(string word1, string word2, int i, int j) {
        // base cases
        if(i == word1.length()) {
            return word2.length() - j; // insert remaining characters
        }
        
        if(j == word2.length()) {
            return word1.length() - i; // delete remaining characters
        }
        
        // agar characters same hai
        if(word1[i] == word2[j]) {
            return editHelper(word1, word2, i + 1, j + 1);
        }
        
        // three operations try karte hai
        int insert = 1 + editHelper(word1, word2, i, j + 1);
        int delete_op = 1 + editHelper(word1, word2, i + 1, j);
        int replace = 1 + editHelper(word1, word2, i + 1, j + 1);
        
        return min({insert, delete_op, replace});
    }
    
    // Better - Memoization O(m*n) time, O(m*n) space
    int minDistance_better(string word1, string word2) {
        vector<vector<int>> memo(word1.length(), vector<int>(word2.length(), -1));
        return dpHelper(word1, word2, 0, 0, memo);
    }
    
    int dpHelper(string word1, string word2, int i, int j, vector<vector<int>>& memo) {
        if(i == word1.length()) {
            return word2.length() - j;
        }
        
        if(j == word2.length()) {
            return word1.length() - i;
        }
        
        if(memo[i][j] != -1) {
            return memo[i][j];
        }
        
        if(word1[i] == word2[j]) {
            memo[i][j] = dpHelper(word1, word2, i + 1, j + 1, memo);
        } else {
            int insert = 1 + dpHelper(word1, word2, i, j + 1, memo);
            int delete_op = 1 + dpHelper(word1, word2, i + 1, j, memo);
            int replace = 1 + dpHelper(word1, word2, i + 1, j + 1, memo);
            
            memo[i][j] = min({insert, delete_op, replace});
        }
        
        return memo[i][j];
    }
    
    // Optimal - Bottom-up DP O(m*n) time, O(m*n) space
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        // base cases
        for(int i = 0; i <= m; i++) {
            dp[i][0] = i; // delete all characters from word1
        }
        
        for(int j = 0; j <= n; j++) {
            dp[0][j] = j; // insert all characters to match word2
        }
        
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1]; // no operation needed
                } else {
                    dp[i][j] = 1 + min({
                        dp[i-1][j],     // delete
                        dp[i][j-1],     // insert
                        dp[i-1][j-1]    // replace
                    });
                }
            }
        }
        
        return dp[m][n];
    }
};

// 10. Wildcard Matching - String (Hard)
class Solution10_Hard {
public:
    // Brute Force - Recursive approach O(2^(n+m)) time, O(n+m) space
    bool isMatch_bruteforce(string s, string p) {
        return matchWildcard(s, p, 0, 0);
    }
    
    bool matchWildcard(string s, string p, int i, int j) {
        // pattern khatam ho gaya
        if(j >= p.length()) {
            return i >= s.length();
        }
        
        // string khatam ho gayi but pattern mein sirf '*' remaining hai
        if(i >= s.length()) {
            while(j < p.length() && p[j] == '*') j++;
            return j >= p.length();
        }
        
        if(p[j] == '*') {
            // '*' ko zero characters ya ek character match karte hai
            return matchWildcard(s, p, i, j + 1) ||  // zero characters
                   matchWildcard(s, p, i + 1, j);    // one character
        } else if(p[j] == '?' || p[j] == s[i]) {
            return matchWildcard(s, p, i + 1, j + 1);
        } else {
            return false;
        }
    }
    
    // Better - Memoization O(n*m) time, O(n*m) space
    bool isMatch_better(string s, string p) {
        vector<vector<int>> memo(s.length() + 1, vector<int>(p.length() + 1, -1));
        return dpWildcard(s, p, 0, 0, memo);
    }
    
    bool dpWildcard(string s, string p, int i, int j, vector<vector<int>>& memo) {
        if(memo[i][j] != -1) {
            return memo[i][j];
        }
        
        bool result;
        
        if(j >= p.length()) {
            result = (i >= s.length());
        } else if(i >= s.length()) {
            result = true;
            for(int k = j; k < p.length(); k++) {
                if(p[k] != '*') {
                    result = false;
                    break;
                }
            }
        } else if(p[j] == '*') {
            result = dpWildcard(s, p, i, j + 1, memo) ||
                    dpWildcard(s, p, i + 1, j, memo);
        } else if(p[j] == '?' || p[j] == s[i]) {
            result = dpWildcard(s, p, i + 1, j + 1, memo);
        } else {
            result = false;
        }
        
        memo[i][j] = result;
        return result;
    }
    
    // Optimal - Bottom-up DP O(n*m) time, O(n*m) space
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true; // empty string matches empty pattern
        
        // handle patterns starting with '*'
        for(int j = 1; j <= n; j++) {
            if(p[j-1] == '*') {
                dp[0][j] = dp[0][j-1];
            }
        }
        
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(p[j-1] == '*') {
                    dp[i][j] = dp[i][j-1] || dp[i-1][j];
                } else if(p[j-1] == '?' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                // else dp[i][j] remains false
            }
        }
        
        return dp[m][n];
    }
};