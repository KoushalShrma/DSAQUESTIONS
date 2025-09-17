#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

// 11. Longest Valid Parentheses - String (Hard)
class Solution11_Hard {
public:
    // Brute Force - Check all substrings O(n³) time, O(1) space
    int longestValidParentheses_bruteforce(string s) {
        int maxLen = 0;
        
        // har possible substring check karte hai
        for(int i = 0; i < s.length(); i++) {
            for(int j = i + 1; j < s.length(); j += 2) { // only even lengths
                if(isValid(s.substr(i, j - i + 1))) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }
        
        return maxLen;
    }
    
    bool isValid(string str) {
        int count = 0;
        for(char c : str) {
            if(c == '(') count++;
            else count--;
            if(count < 0) return false;
        }
        return count == 0;
    }
    
    // Better - Dynamic Programming O(n) time, O(n) space
    int longestValidParentheses_better(string s) {
        int n = s.length();
        if(n <= 1) return 0;
        
        vector<int> dp(n, 0); // dp[i] = length of valid parentheses ending at i
        int maxLen = 0;
        
        for(int i = 1; i < n; i++) {
            if(s[i] == ')') {
                if(s[i-1] == '(') {
                    // case: ...()
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                }
                else if(dp[i-1] > 0) {
                    // case: ...))
                    int matchIndex = i - dp[i-1] - 1;
                    if(matchIndex >= 0 && s[matchIndex] == '(') {
                        dp[i] = dp[i-1] + 2 + (matchIndex > 0 ? dp[matchIndex-1] : 0);
                    }
                }
                
                maxLen = max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
    
    // Optimal - Stack approach O(n) time, O(n) space
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1); // base for valid parentheses
        int maxLen = 0;
        
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                
                if(stk.empty()) {
                    stk.push(i); // new base
                } else {
                    maxLen = max(maxLen, i - stk.top());
                }
            }
        }
        
        return maxLen;
    }
};

// 12. Word Break II - String (Hard)
class Solution12_Hard {
public:
    // Brute Force - Generate all possible breaks O(2^n) time, O(2^n) space
    vector<string> wordBreak_bruteforce(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<string> result;
        vector<string> current;
        
        backtrack(s, 0, dict, current, result);
        return result;
    }
    
    void backtrack(string s, int start, unordered_set<string>& dict,
                   vector<string>& current, vector<string>& result) {
        if(start == s.length()) {
            string sentence = "";
            for(int i = 0; i < current.size(); i++) {
                if(i > 0) sentence += " ";
                sentence += current[i];
            }
            result.push_back(sentence);
            return;
        }
        
        for(int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            if(dict.count(word)) {
                current.push_back(word);
                backtrack(s, end, dict, current, result);
                current.pop_back();
            }
        }
    }
    
    // Better - Memoization with DFS O(n³) time, O(n³) space
    vector<string> wordBreak_better(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo;
        return dfs(s, 0, dict, memo);
    }
    
    vector<string> dfs(string s, int start, unordered_set<string>& dict,
                      unordered_map<int, vector<string>>& memo) {
        if(memo.count(start)) {
            return memo[start];
        }
        
        if(start == s.length()) {
            return {""};
        }
        
        vector<string> result;
        
        for(int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            
            if(dict.count(word)) {
                vector<string> suffixes = dfs(s, end, dict, memo);
                
                for(string suffix : suffixes) {
                    string sentence = word;
                    if(!suffix.empty()) {
                        sentence += " " + suffix;
                    }
                    result.push_back(sentence);
                }
            }
        }
        
        memo[start] = result;
        return result;
    }
    
    // Optimal - DP + Backtracking O(n³) time, O(n²) space
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        
        // dp[i] = true if s[0:i] can be broken
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < i; j++) {
                if(dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        if(!dp[n]) return {}; // cannot be broken
        
        vector<string> result;
        vector<string> path;
        
        function<void(int)> backtrack = [&](int start) {
            if(start == n) {
                string sentence = "";
                for(int i = 0; i < path.size(); i++) {
                    if(i > 0) sentence += " ";
                    sentence += path[i];
                }
                result.push_back(sentence);
                return;
            }
            
            for(int end = start + 1; end <= n; end++) {
                string word = s.substr(start, end - start);
                if(dict.count(word) && dp[end]) {
                    path.push_back(word);
                    backtrack(end);
                    path.pop_back();
                }
            }
        };
        
        backtrack(0);
        return result;
    }
};

// 13. Distinct Subsequences - String (Hard)
class Solution13_Hard {
public:
    // Brute Force - Recursive approach O(2^n) time, O(n) space
    int numDistinct_bruteforce(string s, string t) {
        return countSubsequences(s, t, 0, 0);
    }
    
    int countSubsequences(string s, string t, int i, int j) {
        // t completely matched
        if(j == t.length()) return 1;
        
        // s exhausted but t not matched
        if(i == s.length()) return 0;
        
        int count = 0;
        
        // always skip current character in s
        count += countSubsequences(s, t, i + 1, j);
        
        // if characters match, include current character
        if(s[i] == t[j]) {
            count += countSubsequences(s, t, i + 1, j + 1);
        }
        
        return count;
    }
    
    // Better - Memoization O(n*m) time, O(n*m) space
    int numDistinct_better(string s, string t) {
        vector<vector<long long>> memo(s.length(), vector<long long>(t.length(), -1));
        return dpHelper(s, t, 0, 0, memo);
    }
    
    long long dpHelper(string s, string t, int i, int j, vector<vector<long long>>& memo) {
        if(j == t.length()) return 1;
        if(i == s.length()) return 0;
        
        if(memo[i][j] != -1) return memo[i][j];
        
        long long result = dpHelper(s, t, i + 1, j, memo); // skip s[i]
        
        if(s[i] == t[j]) {
            result += dpHelper(s, t, i + 1, j + 1, memo); // match s[i] with t[j]
        }
        
        memo[i][j] = result;
        return result;
    }
    
    // Optimal - Bottom-up DP O(n*m) time, O(n*m) space
    int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
        
        // empty t can be formed by any s in 1 way
        for(int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }
        
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                // always skip current character in s
                dp[i][j] = dp[i-1][j];
                
                // if characters match, add ways by including current character
                if(s[i-1] == t[j-1]) {
                    dp[i][j] += dp[i-1][j-1];
                }
            }
        }
        
        return dp[m][n];
    }
};

// 14. Palindrome Partitioning II - String (Hard)
class Solution14_Hard {
public:
    // Brute Force - Try all partitions O(n*2^n) time, O(2^n) space
    int minCut_bruteforce(string s) {
        vector<vector<string>> allPartitions;
        vector<string> current;
        
        generateAllPartitions(s, 0, current, allPartitions);
        
        int minCuts = INT_MAX;
        for(auto& partition : allPartitions) {
            minCuts = min(minCuts, (int)partition.size() - 1);
        }
        
        return minCuts;
    }
    
    void generateAllPartitions(string s, int start, vector<string>& current,
                              vector<vector<string>>& allPartitions) {
        if(start == s.length()) {
            allPartitions.push_back(current);
            return;
        }
        
        for(int end = start; end < s.length(); end++) {
            string substring = s.substr(start, end - start + 1);
            if(isPalindrome(substring)) {
                current.push_back(substring);
                generateAllPartitions(s, end + 1, current, allPartitions);
                current.pop_back();
            }
        }
    }
    
    bool isPalindrome(string str) {
        int left = 0, right = str.length() - 1;
        while(left < right) {
            if(str[left] != str[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Better - DP with palindrome precomputation O(n²) time, O(n²) space
    int minCut_better(string s) {
        int n = s.length();
        
        // precompute palindrome table
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        
        for(int i = 0; i < n; i++) {
            isPalin[i][i] = true;
        }
        
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if(s[i] == s[j]) {
                    if(len == 2) {
                        isPalin[i][j] = true;
                    } else {
                        isPalin[i][j] = isPalin[i+1][j-1];
                    }
                }
            }
        }
        
        // dp[i] = minimum cuts needed for s[0:i]
        vector<int> dp(n, INT_MAX);
        
        for(int i = 0; i < n; i++) {
            if(isPalin[0][i]) {
                dp[i] = 0; // whole substring is palindrome
            } else {
                for(int j = 0; j < i; j++) {
                    if(isPalin[j+1][i]) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        
        return dp[n-1];
    }
    
    // Optimal - Optimized DP O(n²) time, O(n²) space
    int minCut(string s) {
        int n = s.length();
        vector<int> cuts(n);
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        
        // build palindrome table
        for(int i = 0; i < n; i++) {
            int minCut = i; // worst case: i cuts for i+1 characters
            
            for(int j = 0; j <= i; j++) {
                // check if s[j:i] is palindrome
                if(s[j] == s[i] && (i - j <= 1 || isPalin[j+1][i-1])) {
                    isPalin[j][i] = true;
                    
                    if(j == 0) {
                        minCut = 0; // s[0:i] is palindrome
                    } else {
                        minCut = min(minCut, cuts[j-1] + 1);
                    }
                }
            }
            
            cuts[i] = minCut;
        }
        
        return cuts[n-1];
    }
};

// 15. Scramble String - String (Hard)
class Solution15_Hard {
public:
    // Brute Force - Try all possible splits O(4^n) time, O(n) space
    bool isScramble_bruteforce(string s1, string s2) {
        if(s1.length() != s2.length()) return false;
        if(s1 == s2) return true;
        
        // character frequency check
        vector<int> count(26, 0);
        for(int i = 0; i < s1.length(); i++) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        
        for(int c : count) {
            if(c != 0) return false;
        }
        
        // try all possible splits
        for(int i = 1; i < s1.length(); i++) {
            // case 1: no swap
            if(isScramble_bruteforce(s1.substr(0, i), s2.substr(0, i)) &&
               isScramble_bruteforce(s1.substr(i), s2.substr(i))) {
                return true;
            }
            
            // case 2: swap
            if(isScramble_bruteforce(s1.substr(0, i), s2.substr(s2.length() - i)) &&
               isScramble_bruteforce(s1.substr(i), s2.substr(0, s2.length() - i))) {
                return true;
            }
        }
        
        return false;
    }
    
    // Better - Memoization O(n⁴) time, O(n³) space
    bool isScramble_better(string s1, string s2) {
        unordered_map<string, bool> memo;
        return helper(s1, s2, memo);
    }
    
    bool helper(string s1, string s2, unordered_map<string, bool>& memo) {
        if(s1.length() != s2.length()) return false;
        if(s1 == s2) return true;
        
        string key = s1 + "#" + s2;
        if(memo.count(key)) return memo[key];
        
        // character frequency check
        vector<int> count(26, 0);
        for(int i = 0; i < s1.length(); i++) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        
        for(int c : count) {
            if(c != 0) {
                memo[key] = false;
                return false;
            }
        }
        
        // try all splits
        for(int i = 1; i < s1.length(); i++) {
            if((helper(s1.substr(0, i), s2.substr(0, i), memo) &&
                helper(s1.substr(i), s2.substr(i), memo)) ||
               (helper(s1.substr(0, i), s2.substr(s2.length() - i), memo) &&
                helper(s1.substr(i), s2.substr(0, s2.length() - i), memo))) {
                memo[key] = true;
                return true;
            }
        }
        
        memo[key] = false;
        return false;
    }
    
    // Optimal - 3D DP O(n⁴) time, O(n³) space
    bool isScramble(string s1, string s2) {
        if(s1.length() != s2.length()) return false;
        if(s1 == s2) return true;
        
        int n = s1.length();
        // dp[len][i][j] = is s1[i:i+len] scramble of s2[j:j+len]
        vector<vector<vector<bool>>> dp(n + 1, 
            vector<vector<bool>>(n, vector<bool>(n, false)));
        
        // single characters
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dp[1][i][j] = (s1[i] == s2[j]);
            }
        }
        
        // fill for all lengths
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i <= n - len; i++) {
                for(int j = 0; j <= n - len; j++) {
                    for(int k = 1; k < len; k++) {
                        // no swap case
                        if(dp[k][i][j] && dp[len-k][i+k][j+k]) {
                            dp[len][i][j] = true;
                            break;
                        }
                        
                        // swap case
                        if(dp[k][i][j+len-k] && dp[len-k][i+k][j]) {
                            dp[len][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }
        
        return dp[n][0][0];
    }
};