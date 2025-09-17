#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

// 16. Maximum Rectangle - Array (Hard)
class Solution16_Hard {
public:
    // Brute Force - Check all possible rectangles O(m²*n²) time, O(1) space
    int maximalRectangle_bruteforce(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        int maxArea = 0;
        
        // har cell ko top-left corner maan kar rectangles check karte hai
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == '1') {
                    // har possible bottom-right corner try karte hai
                    for(int k = i; k < m; k++) {
                        for(int l = j; l < n; l++) {
                            // check if valid rectangle
                            bool isValid = true;
                            for(int r = i; r <= k && isValid; r++) {
                                for(int c = j; c <= l && isValid; c++) {
                                    if(matrix[r][c] == '0') {
                                        isValid = false;
                                    }
                                }
                            }
                            
                            if(isValid) {
                                int area = (k - i + 1) * (l - j + 1);
                                maxArea = max(maxArea, area);
                            }
                        }
                    }
                }
            }
        }
        
        return maxArea;
    }
    
    // Better - For each row, find max rectangle in histogram O(m*n²) time
    int maximalRectangle_better(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;
        
        for(int i = 0; i < m; i++) {
            // update heights array
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == '1') {
                    heights[j]++;
                } else {
                    heights[j] = 0;
                }
            }
            
            // find max rectangle in current histogram
            maxArea = max(maxArea, largestRectangleInHistogram(heights));
        }
        
        return maxArea;
    }
    
    int largestRectangleInHistogram(vector<int>& heights) {
        int maxArea = 0;
        int n = heights.size();
        
        for(int i = 0; i < n; i++) {
            int left = i, right = i;
            
            // expand left
            while(left >= 0 && heights[left] >= heights[i]) {
                left--;
            }
            
            // expand right
            while(right < n && heights[right] >= heights[i]) {
                right++;
            }
            
            int width = right - left - 1;
            maxArea = max(maxArea, heights[i] * width);
        }
        
        return maxArea;
    }
    
    // Optimal - Stack-based histogram solution O(m*n) time, O(n) space
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;
        
        for(int i = 0; i < m; i++) {
            // update heights
            for(int j = 0; j < n; j++) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            
            // find max rectangle using stack
            maxArea = max(maxArea, maxRectangleInHistogram(heights));
        }
        
        return maxArea;
    }
    
    int maxRectangleInHistogram(vector<int>& heights) {
        stack<int> stk;
        int maxArea = 0;
        
        for(int i = 0; i <= heights.size(); i++) {
            int currentHeight = (i == heights.size()) ? 0 : heights[i];
            
            while(!stk.empty() && heights[stk.top()] > currentHeight) {
                int h = heights[stk.top()];
                stk.pop();
                
                int width = stk.empty() ? i : (i - stk.top() - 1);
                maxArea = max(maxArea, h * width);
            }
            
            stk.push(i);
        }
        
        return maxArea;
    }
};

// 17. Longest Substring with At Most K Distinct Characters - String (Hard)
class Solution17_Hard {
public:
    // Brute Force - Check all substrings O(n³) time, O(k) space
    int lengthOfLongestSubstringKDistinct_bruteforce(string s, int k) {
        int maxLength = 0;
        
        for(int i = 0; i < s.length(); i++) {
            for(int j = i; j < s.length(); j++) {
                unordered_set<char> distinctChars;
                
                // count distinct characters in current substring
                for(int l = i; l <= j; l++) {
                    distinctChars.insert(s[l]);
                }
                
                if(distinctChars.size() <= k) {
                    maxLength = max(maxLength, j - i + 1);
                }
            }
        }
        
        return maxLength;
    }
    
    // Better - Sliding window with set O(n²) time, O(k) space
    int lengthOfLongestSubstringKDistinct_better(string s, int k) {
        if(k == 0) return 0;
        
        int maxLength = 0;
        
        for(int i = 0; i < s.length(); i++) {
            unordered_map<char, int> charCount;
            
            for(int j = i; j < s.length(); j++) {
                charCount[s[j]]++;
                
                if(charCount.size() <= k) {
                    maxLength = max(maxLength, j - i + 1);
                } else {
                    break; // too many distinct characters
                }
            }
        }
        
        return maxLength;
    }
    
    // Optimal - Sliding window with hash map O(n) time, O(k) space
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if(k == 0 || s.empty()) return 0;
        
        unordered_map<char, int> charCount;
        int left = 0, maxLength = 0;
        
        for(int right = 0; right < s.length(); right++) {
            charCount[s[right]]++;
            
            // agar distinct characters k se zyada ho gaye
            while(charCount.size() > k) {
                charCount[s[left]]--;
                if(charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

// 18. Substring with Concatenation of All Words - String (Hard)
class Solution18_Hard {
public:
    // Brute Force - Check every position O(n*m*l) time where l is word length
    vector<int> findSubstring_bruteforce(string s, vector<string>& words) {
        vector<int> result;
        if(s.empty() || words.empty()) return result;
        
        int wordLen = words[0].length();
        int totalLen = words.size() * wordLen;
        
        if(s.length() < totalLen) return result;
        
        unordered_map<string, int> wordCount;
        for(string word : words) {
            wordCount[word]++;
        }
        
        // har position se check karte hai
        for(int i = 0; i <= s.length() - totalLen; i++) {
            unordered_map<string, int> seen;
            int j = 0;
            
            // har word check karte hai
            while(j < words.size()) {
                string word = s.substr(i + j * wordLen, wordLen);
                
                if(wordCount.find(word) == wordCount.end()) {
                    break; // word not in dictionary
                }
                
                seen[word]++;
                
                if(seen[word] > wordCount[word]) {
                    break; // too many occurrences
                }
                
                j++;
            }
            
            if(j == words.size()) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Better - Sliding window with optimization O(n*l) time
    vector<int> findSubstring_better(string s, vector<string>& words) {
        vector<int> result;
        if(s.empty() || words.empty()) return result;
        
        int wordLen = words[0].length();
        int wordsCount = words.size();
        int totalLen = wordsCount * wordLen;
        
        if(s.length() < totalLen) return result;
        
        unordered_map<string, int> wordCount;
        for(string word : words) {
            wordCount[word]++;
        }
        
        // har possible starting offset ke liye sliding window
        for(int offset = 0; offset < wordLen; offset++) {
            unordered_map<string, int> windowCount;
            int left = offset;
            int validWords = 0;
            
            for(int right = offset; right <= s.length() - wordLen; right += wordLen) {
                string word = s.substr(right, wordLen);
                
                if(wordCount.find(word) != wordCount.end()) {
                    windowCount[word]++;
                    
                    if(windowCount[word] <= wordCount[word]) {
                        validWords++;
                    }
                    
                    // agar window size exceed ho gaya
                    while(validWords == wordsCount || 
                          (windowCount[word] > wordCount[word])) {
                        
                        if(validWords == wordsCount && 
                           right - left + wordLen == totalLen) {
                            result.push_back(left);
                        }
                        
                        string leftWord = s.substr(left, wordLen);
                        windowCount[leftWord]--;
                        
                        if(windowCount[leftWord] < wordCount[leftWord]) {
                            validWords--;
                        }
                        
                        left += wordLen;
                    }
                } else {
                    // reset window
                    windowCount.clear();
                    validWords = 0;
                    left = right + wordLen;
                }
            }
        }
        
        return result;
    }
    
    // Optimal - Efficient sliding window O(n*l) time, O(m*l) space
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if(s.empty() || words.empty()) return result;
        
        int wordLen = words[0].length();
        int wordsCount = words.size();
        int totalLen = wordsCount * wordLen;
        
        if(s.length() < totalLen) return result;
        
        unordered_map<string, int> targetCount;
        for(const string& word : words) {
            targetCount[word]++;
        }
        
        for(int i = 0; i < wordLen; i++) {
            unordered_map<string, int> windowCount;
            int left = i, validWords = 0;
            
            for(int right = i; right <= (int)s.length() - wordLen; right += wordLen) {
                string rightWord = s.substr(right, wordLen);
                
                if(targetCount.count(rightWord)) {
                    windowCount[rightWord]++;
                    
                    if(windowCount[rightWord] <= targetCount[rightWord]) {
                        validWords++;
                    }
                    
                    while(windowCount[rightWord] > targetCount[rightWord]) {
                        string leftWord = s.substr(left, wordLen);
                        windowCount[leftWord]--;
                        
                        if(windowCount[leftWord] < targetCount[leftWord]) {
                            validWords--;
                        }
                        
                        left += wordLen;
                    }
                    
                    if(validWords == wordsCount) {
                        result.push_back(left);
                    }
                } else {
                    windowCount.clear();
                    validWords = 0;
                    left = right + wordLen;
                }
            }
        }
        
        return result;
    }
};

// 19. Text Justification - String (Hard)
class Solution19_Hard {
public:
    // Brute Force - Process line by line O(n) time, O(1) space
    vector<string> fullJustify_bruteforce(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        
        while(i < words.size()) {
            vector<string> currentLine;
            int currentLength = 0;
            
            // current line mein words add karte hai
            while(i < words.size()) {
                int newLength = currentLength + words[i].length();
                if(!currentLine.empty()) newLength++; // space ke liye
                
                if(newLength <= maxWidth) {
                    currentLine.push_back(words[i]);
                    currentLength += words[i].length();
                    if(!currentLine.empty() && currentLine.size() > 1) {
                        currentLength++; // space ke liye
                    }
                    i++;
                } else {
                    break;
                }
            }
            
            // line justify karte hai
            string justifiedLine = justifyLine(currentLine, maxWidth, i == words.size());
            result.push_back(justifiedLine);
        }
        
        return result;
    }
    
    string justifyLine(vector<string>& words, int maxWidth, bool isLastLine) {
        if(words.size() == 1 || isLastLine) {
            // left justify karte hai
            string line = "";
            for(int i = 0; i < words.size(); i++) {
                if(i > 0) line += " ";
                line += words[i];
            }
            
            // remaining spaces add karte hai
            while(line.length() < maxWidth) {
                line += " ";
            }
            
            return line;
        }
        
        // calculate total spaces needed
        int totalChars = 0;
        for(string word : words) {
            totalChars += word.length();
        }
        
        int totalSpaces = maxWidth - totalChars;
        int gaps = words.size() - 1;
        int spacesPerGap = totalSpaces / gaps;
        int extraSpaces = totalSpaces % gaps;
        
        string line = "";
        for(int i = 0; i < words.size(); i++) {
            line += words[i];
            
            if(i < gaps) {
                // regular spaces
                for(int j = 0; j < spacesPerGap; j++) {
                    line += " ";
                }
                
                // extra space (left gaps get priority)
                if(i < extraSpaces) {
                    line += " ";
                }
            }
        }
        
        return line;
    }
    
    // Better - Optimized line building O(n) time, O(1) space
    vector<string> fullJustify_better(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        
        while(i < words.size()) {
            int j = i;
            int length = 0;
            
            // current line ke liye words select karte hai
            while(j < words.size() && length + words[j].length() + (j - i) <= maxWidth) {
                length += words[j].length();
                j++;
            }
            
            string line = "";
            int gaps = j - i - 1;
            
            // last line ya single word
            if(j == words.size() || gaps == 0) {
                for(int k = i; k < j; k++) {
                    line += words[k];
                    if(k < j - 1) line += " ";
                }
                
                // remaining spaces
                while(line.length() < maxWidth) {
                    line += " ";
                }
            } else {
                // full justification
                int spaces = maxWidth - length;
                int spaceBetween = spaces / gaps;
                int extraSpaces = spaces % gaps;
                
                for(int k = i; k < j; k++) {
                    line += words[k];
                    
                    if(k < j - 1) {
                        for(int s = 0; s < spaceBetween; s++) {
                            line += " ";
                        }
                        
                        if(k - i < extraSpaces) {
                            line += " ";
                        }
                    }
                }
            }
            
            result.push_back(line);
            i = j;
        }
        
        return result;
    }
    
    // Optimal - Clean implementation O(n) time, O(1) space
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        
        while(i < words.size()) {
            vector<string> line;
            int totalLen = 0;
            
            // pack words into current line
            while(i < words.size() && 
                  totalLen + words[i].length() + line.size() <= maxWidth) {
                line.push_back(words[i]);
                totalLen += words[i].length();
                i++;
            }
            
            result.push_back(formatLine(line, totalLen, maxWidth, i == words.size()));
        }
        
        return result;
    }
    
    string formatLine(vector<string>& words, int totalLen, int maxWidth, bool isLast) {
        if(words.size() == 1 || isLast) {
            // left justify
            string line = words[0];
            for(int i = 1; i < words.size(); i++) {
                line += " " + words[i];
            }
            return line + string(maxWidth - line.length(), ' ');
        }
        
        // full justify
        int totalSpaces = maxWidth - totalLen;
        int gaps = words.size() - 1;
        int spacePerGap = totalSpaces / gaps;
        int extraSpaces = totalSpaces % gaps;
        
        string line = words[0];
        for(int i = 1; i < words.size(); i++) {
            line += string(spacePerGap + (i <= extraSpaces ? 1 : 0), ' ') + words[i];
        }
        
        return line;
    }
};

// 20. First Missing Positive - Array (Hard)
class Solution20_Hard {
public:
    // Brute Force - Check each positive number O(n²) time, O(1) space
    int firstMissingPositive_bruteforce(vector<int>& nums) {
        int n = nums.size();
        
        // 1 se n+1 tak har number check karte hai
        for(int i = 1; i <= n + 1; i++) {
            bool found = false;
            
            for(int j = 0; j < n; j++) {
                if(nums[j] == i) {
                    found = true;
                    break;
                }
            }
            
            if(!found) return i;
        }
        
        return n + 1;
    }
    
    // Better - Using extra space O(n) time, O(n) space
    int firstMissingPositive_better(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        
        for(int i = 1; i <= nums.size() + 1; i++) {
            if(numSet.find(i) == numSet.end()) {
                return i;
            }
        }
        
        return nums.size() + 1;
    }
    
    // Optimal - Cyclic sort / Index mapping O(n) time, O(1) space
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // step 1: handle negatives and large numbers
        for(int i = 0; i < n; i++) {
            if(nums[i] <= 0 || nums[i] > n) {
                nums[i] = n + 1; // invalid marker
            }
        }
        
        // step 2: mark presence using sign
        for(int i = 0; i < n; i++) {
            int num = abs(nums[i]);
            
            if(num <= n) {
                // mark nums[num-1] as negative (present)
                if(nums[num - 1] > 0) {
                    nums[num - 1] = -nums[num - 1];
                }
            }
        }
        
        // step 3: find first positive index
        for(int i = 0; i < n; i++) {
            if(nums[i] > 0) {
                return i + 1; // missing positive number
            }
        }
        
        return n + 1; // all numbers 1 to n are present
    }
};

// 21. Longest Increasing Path in a Matrix - Array (Hard)
class Solution21_Hard {
public:
    // Brute Force - DFS from each cell O(2^(m*n)) time, O(m*n) space
    int longestIncreasingPath_bruteforce(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        int maxPath = 1;
        
        // har cell se DFS start karte hai
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                maxPath = max(maxPath, dfs(matrix, i, j, -1));
            }
        }
        
        return maxPath;
    }
    
    int dfs(vector<vector<int>>& matrix, int i, int j, int prevVal) {
        int m = matrix.size(), n = matrix[0].size();
        
        if(i < 0 || i >= m || j < 0 || j >= n || matrix[i][j] <= prevVal) {
            return 0;
        }
        
        int maxLen = 1;
        int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        for(auto& dir : directions) {
            int newI = i + dir[0];
            int newJ = j + dir[1];
            maxLen = max(maxLen, 1 + dfs(matrix, newI, newJ, matrix[i][j]));
        }
        
        return maxLen;
    }
    
    // Better - DFS with memoization O(m*n) time, O(m*n) space
    int longestIncreasingPath_better(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo(m, vector<int>(n, -1));
        int maxPath = 1;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                maxPath = max(maxPath, dfsMemo(matrix, i, j, memo));
            }
        }
        
        return maxPath;
    }
    
    int dfsMemo(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& memo) {
        if(memo[i][j] != -1) return memo[i][j];
        
        int m = matrix.size(), n = matrix[0].size();
        int maxLen = 1;
        int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        for(auto& dir : directions) {
            int newI = i + dir[0];
            int newJ = j + dir[1];
            
            if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && 
               matrix[newI][newJ] > matrix[i][j]) {
                maxLen = max(maxLen, 1 + dfsMemo(matrix, newI, newJ, memo));
            }
        }
        
        memo[i][j] = maxLen;
        return maxLen;
    }
    
    // Optimal - Topological sort O(m*n) time, O(m*n) space
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> indegree(m, vector<int>(n, 0));
        vector<vector<int>> dp(m, vector<int>(n, 1));
        
        int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        // calculate indegree for each cell
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                for(auto& dir : directions) {
                    int newI = i + dir[0];
                    int newJ = j + dir[1];
                    
                    if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && 
                       matrix[newI][newJ] > matrix[i][j]) {
                        indegree[newI][newJ]++;
                    }
                }
            }
        }
        
        // BFS using queue (topological sort)
        queue<pair<int, int>> q;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(indegree[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        int maxLength = 1;
        
        while(!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            
            for(auto& dir : directions) {
                int newI = i + dir[0];
                int newJ = j + dir[1];
                
                if(newI >= 0 && newI < m && newJ >= 0 && newJ < n && 
                   matrix[newI][newJ] > matrix[i][j]) {
                    dp[newI][newJ] = max(dp[newI][newJ], dp[i][j] + 1);
                    maxLength = max(maxLength, dp[newI][newJ]);
                    
                    indegree[newI][newJ]--;
                    if(indegree[newI][newJ] == 0) {
                        q.push({newI, newJ});
                    }
                }
            }
        }
        
        return maxLength;
    }
};

// 22. Burst Balloons - Array (Hard)
class Solution22_Hard {
public:
    // Brute Force - Try all possible sequences O(n!) time, O(n) space
    int maxCoins_bruteforce(vector<int>& nums) {
        vector<int> balloons = nums;
        return backtrack(balloons);
    }
    
    int backtrack(vector<int>& balloons) {
        if(balloons.empty()) return 0;
        
        int maxCoins = 0;
        
        // har balloon burst karne ki koshish karte hai
        for(int i = 0; i < balloons.size(); i++) {
            int left = (i == 0) ? 1 : balloons[i-1];
            int right = (i == balloons.size() - 1) ? 1 : balloons[i+1];
            int coins = left * balloons[i] * right;
            
            // current balloon remove karte hai
            vector<int> remaining;
            for(int j = 0; j < balloons.size(); j++) {
                if(j != i) {
                    remaining.push_back(balloons[j]);
                }
            }
            
            maxCoins = max(maxCoins, coins + backtrack(remaining));
        }
        
        return maxCoins;
    }
    
    // Better - Memoization with range DP O(n³) time, O(n²) space
    int maxCoins_better(vector<int>& nums) {
        vector<int> balloons = {1};
        for(int num : nums) {
            balloons.push_back(num);
        }
        balloons.push_back(1);
        
        int n = balloons.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        
        return dp(balloons, 0, n - 1, memo);
    }
    
    int dp(vector<int>& balloons, int left, int right, vector<vector<int>>& memo) {
        if(left + 1 >= right) return 0;
        if(memo[left][right] != -1) return memo[left][right];
        
        int maxCoins = 0;
        
        // left+1 se right-1 tak har balloon ko last burst karte hai
        for(int i = left + 1; i < right; i++) {
            int coins = balloons[left] * balloons[i] * balloons[right];
            coins += dp(balloons, left, i, memo);
            coins += dp(balloons, i, right, memo);
            
            maxCoins = max(maxCoins, coins);
        }
        
        memo[left][right] = maxCoins;
        return maxCoins;
    }
    
    // Optimal - Bottom-up DP O(n³) time, O(n²) space
    int maxCoins(vector<int>& nums) {
        vector<int> balloons = {1};
        for(int num : nums) {
            balloons.push_back(num);
        }
        balloons.push_back(1);
        
        int n = balloons.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // length 3 se start karte hai (at least 1 balloon between boundaries)
        for(int len = 3; len <= n; len++) {
            for(int left = 0; left <= n - len; left++) {
                int right = left + len - 1;
                
                // left+1 se right-1 tak har balloon ko last burst karte hai
                for(int k = left + 1; k < right; k++) {
                    int coins = balloons[left] * balloons[k] * balloons[right];
                    coins += dp[left][k] + dp[k][right];
                    
                    dp[left][right] = max(dp[left][right], coins);
                }
            }
        }
        
        return dp[0][n-1];
    }
};