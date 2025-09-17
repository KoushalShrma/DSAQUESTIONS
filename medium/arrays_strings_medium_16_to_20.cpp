#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

// 16. Valid Parentheses (Advanced) - String (Medium)
class Solution16_Medium {
public:
    // Brute Force - Check all possible removals O(2^n) time, O(n) space
    vector<string> removeInvalidParentheses_bruteforce(string s) {
        unordered_set<string> visited;
        vector<string> result;
        int maxLength = 0;
        
        // BFS simulation with recursion
        removeHelper(s, 0, 0, 0, "", maxLength, result, visited);
        
        return result;
    }
    
    void removeHelper(string s, int index, int leftCount, int rightCount, 
                     string current, int& maxLength, vector<string>& result,
                     unordered_set<string>& visited) {
        if(index == s.length()) {
            if(leftCount == rightCount) {
                if(current.length() > maxLength) {
                    maxLength = current.length();
                    result.clear();
                    result.push_back(current);
                } else if(current.length() == maxLength && 
                         visited.find(current) == visited.end()) {
                    result.push_back(current);
                    visited.insert(current);
                }
            }
            return;
        }
        
        char c = s[index];
        
        // current character skip karte hai
        removeHelper(s, index + 1, leftCount, rightCount, current, 
                    maxLength, result, visited);
        
        // current character include karte hai
        if(c == '(') {
            removeHelper(s, index + 1, leftCount + 1, rightCount, 
                        current + c, maxLength, result, visited);
        } else if(c == ')') {
            if(leftCount > rightCount) {
                removeHelper(s, index + 1, leftCount, rightCount + 1, 
                            current + c, maxLength, result, visited);
            }
        } else {
            removeHelper(s, index + 1, leftCount, rightCount, 
                        current + c, maxLength, result, visited);
        }
    }
    
    // Better - BFS approach O(n*2^n) time, O(n*2^n) space
    vector<string> removeInvalidParentheses_better(string s) {
        queue<string> q;
        unordered_set<string> visited;
        vector<string> result;
        
        q.push(s);
        visited.insert(s);
        bool found = false;
        
        while(!q.empty() && !found) {
            int size = q.size();
            
            for(int i = 0; i < size; i++) {
                string current = q.front();
                q.pop();
                
                if(isValid(current)) {
                    result.push_back(current);
                    found = true;
                } else if(!found) {
                    // har character remove karne ki koshish karte hai
                    for(int j = 0; j < current.length(); j++) {
                        if(current[j] == '(' || current[j] == ')') {
                            string next = current.substr(0, j) + current.substr(j + 1);
                            
                            if(visited.find(next) == visited.end()) {
                                visited.insert(next);
                                q.push(next);
                            }
                        }
                    }
                }
            }
        }
        
        return result;
    }
    
    bool isValid(string s) {
        int count = 0;
        for(char c : s) {
            if(c == '(') count++;
            else if(c == ')') {
                count--;
                if(count < 0) return false;
            }
        }
        return count == 0;
    }
    
    // Optimal - DFS with pruning O(2^n) time but optimized, O(n) space
    vector<string> removeInvalidParentheses(string s) {
        int leftRem = 0, rightRem = 0;
        
        // kitne left aur right parentheses remove karne hai
        for(char c : s) {
            if(c == '(') {
                leftRem++;
            } else if(c == ')') {
                if(leftRem > 0) leftRem--;
                else rightRem++;
            }
        }
        
        unordered_set<string> result;
        dfs(s, 0, leftRem, rightRem, 0, 0, "", result);
        
        return vector<string>(result.begin(), result.end());
    }
    
    void dfs(string s, int index, int leftRem, int rightRem, 
             int leftCount, int rightCount, string path, 
             unordered_set<string>& result) {
        if(index == s.length()) {
            if(leftRem == 0 && rightRem == 0 && leftCount == rightCount) {
                result.insert(path);
            }
            return;
        }
        
        char c = s[index];
        
        // remove current character
        if((c == '(' && leftRem > 0) || (c == ')' && rightRem > 0)) {
            dfs(s, index + 1, 
                leftRem - (c == '(' ? 1 : 0),
                rightRem - (c == ')' ? 1 : 0),
                leftCount, rightCount, path, result);
        }
        
        // keep current character
        if(c == '(') {
            dfs(s, index + 1, leftRem, rightRem, leftCount + 1, rightCount, 
                path + c, result);
        } else if(c == ')' && leftCount > rightCount) {
            dfs(s, index + 1, leftRem, rightRem, leftCount, rightCount + 1, 
                path + c, result);
        } else if(c != '(' && c != ')') {
            dfs(s, index + 1, leftRem, rightRem, leftCount, rightCount, 
                path + c, result);
        }
    }
};

// 17. Decode Ways - String (Medium)
class Solution17_Medium {
public:
    // Brute Force - Try all combinations O(2^n) time, O(n) space
    int numDecodings_bruteforce(string s) {
        return decodeHelper(s, 0);
    }
    
    int decodeHelper(string s, int index) {
        if(index == s.length()) return 1;
        if(s[index] == '0') return 0;
        
        int ways = 0;
        
        // single digit decode karte hai
        ways += decodeHelper(s, index + 1);
        
        // two digits decode karte hai (agar valid hai)
        if(index + 1 < s.length()) {
            int twoDigit = (s[index] - '0') * 10 + (s[index + 1] - '0');
            if(twoDigit <= 26) {
                ways += decodeHelper(s, index + 2);
            }
        }
        
        return ways;
    }
    
    // Better - Memoization O(n) time, O(n) space
    int numDecodings_better(string s) {
        vector<int> memo(s.length(), -1);
        return decodeMemo(s, 0, memo);
    }
    
    int decodeMemo(string s, int index, vector<int>& memo) {
        if(index == s.length()) return 1;
        if(s[index] == '0') return 0;
        if(memo[index] != -1) return memo[index];
        
        int ways = 0;
        
        // single digit
        ways += decodeMemo(s, index + 1, memo);
        
        // two digits
        if(index + 1 < s.length()) {
            int twoDigit = (s[index] - '0') * 10 + (s[index + 1] - '0');
            if(twoDigit <= 26) {
                ways += decodeMemo(s, index + 2, memo);
            }
        }
        
        memo[index] = ways;
        return ways;
    }
    
    // Optimal - Dynamic Programming O(n) time, O(1) space
    int numDecodings(string s) {
        if(s.empty() || s[0] == '0') return 0;
        
        int n = s.length();
        int prev2 = 1; // dp[i-2]
        int prev1 = 1; // dp[i-1]
        
        for(int i = 1; i < n; i++) {
            int current = 0;
            
            // single digit decode
            if(s[i] != '0') {
                current += prev1;
            }
            
            // two digits decode
            int twoDigit = (s[i-1] - '0') * 10 + (s[i] - '0');
            if(twoDigit >= 10 && twoDigit <= 26) {
                current += prev2;
            }
            
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};

// 18. Word Break - String (Medium)
class Solution18_Medium {
public:
    // Brute Force - Try all possible breaks O(2^n) time, O(n) space
    bool wordBreak_bruteforce(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return canBreak(s, 0, dict);
    }
    
    bool canBreak(string s, int start, unordered_set<string>& dict) {
        if(start == s.length()) return true;
        
        // har possible substring try karte hai
        for(int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            
            if(dict.find(word) != dict.end() && canBreak(s, end, dict)) {
                return true;
            }
        }
        
        return false;
    }
    
    // Better - Memoization O(n²) time, O(n) space
    bool wordBreak_better(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<int> memo(s.length(), -1);
        return canBreakMemo(s, 0, dict, memo);
    }
    
    bool canBreakMemo(string s, int start, unordered_set<string>& dict, 
                     vector<int>& memo) {
        if(start == s.length()) return true;
        if(memo[start] != -1) return memo[start];
        
        for(int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            
            if(dict.find(word) != dict.end() && 
               canBreakMemo(s, end, dict, memo)) {
                memo[start] = 1;
                return true;
            }
        }
        
        memo[start] = 0;
        return false;
    }
    
    // Optimal - Dynamic Programming O(n²) time, O(n) space
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true; // empty string can always be broken
        
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < i; j++) {
                if(dp[j]) {
                    string word = s.substr(j, i - j);
                    if(dict.find(word) != dict.end()) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[n];
    }
};

// 19. Palindromic Substrings - String (Medium)
class Solution19_Medium {
public:
    // Brute Force - Check all substrings O(n³) time, O(1) space
    int countSubstrings_bruteforce(string s) {
        int count = 0;
        int n = s.length();
        
        // har possible substring check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                if(isPalindrome(s, i, j)) {
                    count++;
                }
            }
        }
        
        return count;
    }
    
    bool isPalindrome(string s, int left, int right) {
        while(left < right) {
            if(s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Better - Expand around centers O(n²) time, O(1) space
    int countSubstrings_better(string s) {
        int count = 0;
        int n = s.length();
        
        for(int i = 0; i < n; i++) {
            // odd length palindromes
            count += expandAroundCenter(s, i, i);
            
            // even length palindromes
            count += expandAroundCenter(s, i, i + 1);
        }
        
        return count;
    }
    
    int expandAroundCenter(string s, int left, int right) {
        int count = 0;
        
        while(left >= 0 && right < s.length() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        
        return count;
    }
    
    // Optimal - Manacher's algorithm adapted O(n) time, O(n) space
    int countSubstrings(string s) {
        // preprocessing for even length palindromes
        string processed = "#";
        for(char c : s) {
            processed += c;
            processed += "#";
        }
        
        int n = processed.length();
        vector<int> P(n, 0);
        int center = 0, right = 0;
        int totalCount = 0;
        
        for(int i = 0; i < n; i++) {
            int mirror = 2 * center - i;
            
            if(i < right) {
                P[i] = min(right - i, P[mirror]);
            }
            
            // expand palindrome
            while(i + P[i] + 1 < n && i - P[i] - 1 >= 0 && 
                  processed[i + P[i] + 1] == processed[i - P[i] - 1]) {
                P[i]++;
            }
            
            // update center and right
            if(i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
            
            // count palindromes centered at i
            totalCount += (P[i] + 1) / 2;
        }
        
        return totalCount;
    }
};

// 20. Longest Repeating Character Replacement - String (Medium)
class Solution20_Medium {
public:
    // Brute Force - Check all substrings O(n²) time, O(1) space
    int characterReplacement_bruteforce(string s, int k) {
        int maxLength = 0;
        int n = s.length();
        
        // har possible substring check karte hai
        for(int i = 0; i < n; i++) {
            vector<int> count(26, 0);
            int maxCount = 0;
            
            for(int j = i; j < n; j++) {
                count[s[j] - 'A']++;
                maxCount = max(maxCount, count[s[j] - 'A']);
                
                int windowLength = j - i + 1;
                int replacements = windowLength - maxCount;
                
                if(replacements <= k) {
                    maxLength = max(maxLength, windowLength);
                } else {
                    break; // aur extend nahi kar sakte
                }
            }
        }
        
        return maxLength;
    }
    
    // Better - Sliding window with character count O(n*26) time, O(1) space
    int characterReplacement_better(string s, int k) {
        int maxLength = 0;
        
        // har character ko dominant banane ki koshish karte hai
        for(char c = 'A'; c <= 'Z'; c++) {
            int left = 0, count = 0;
            
            for(int right = 0; right < s.length(); right++) {
                if(s[right] == c) count++;
                
                // agar replacements k se zyada hai
                while(right - left + 1 - count > k) {
                    if(s[left] == c) count--;
                    left++;
                }
                
                maxLength = max(maxLength, right - left + 1);
            }
        }
        
        return maxLength;
    }
    
    // Optimal - Sliding window with frequency map O(n) time, O(1) space
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int left = 0, maxCount = 0, maxLength = 0;
        
        for(int right = 0; right < s.length(); right++) {
            count[s[right] - 'A']++;
            maxCount = max(maxCount, count[s[right] - 'A']);
            
            // agar window invalid hai
            if(right - left + 1 - maxCount > k) {
                count[s[left] - 'A']--;
                left++;
            }
            
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};