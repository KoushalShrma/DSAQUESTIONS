#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

// 1. 3Sum - Array (Medium)
class Solution1_Medium {
public:
    // Brute Force - Check all triplets O(n³) time, O(1) space
    vector<vector<int>> threeSum_bruteforce(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        // har possible triplet check karte hai
        for(int i = 0; i < n - 2; i++) {
            for(int j = i + 1; j < n - 1; j++) {
                for(int k = j + 1; k < n; k++) {
                    if(nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> triplet = {nums[i], nums[j], nums[k]};
                        sort(triplet.begin(), triplet.end());
                        
                        // duplicate check karte hai
                        bool duplicate = false;
                        for(auto& existing : result) {
                            if(existing == triplet) {
                                duplicate = true;
                                break;
                            }
                        }
                        
                        if(!duplicate) {
                            result.push_back(triplet);
                        }
                    }
                }
            }
        }
        
        return result;
    }
    
    // Better - Two pointers with hash set O(n²) time, O(n) space
    vector<vector<int>> threeSum_better(vector<int>& nums) {
        set<vector<int>> resultSet;
        int n = nums.size();
        
        for(int i = 0; i < n - 2; i++) {
            unordered_set<int> seen;
            
            for(int j = i + 1; j < n; j++) {
                int complement = 0 - nums[i] - nums[j];
                
                if(seen.find(complement) != seen.end()) {
                    vector<int> triplet = {nums[i], nums[j], complement};
                    sort(triplet.begin(), triplet.end());
                    resultSet.insert(triplet);
                }
                
                seen.insert(nums[j]);
            }
        }
        
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
    
    // Optimal - Sort and two pointers O(n²) time, O(1) space
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        for(int i = 0; i < n - 2; i++) {
            // duplicate elements skip karte hai
            if(i > 0 && nums[i] == nums[i-1]) continue;
            
            int left = i + 1, right = n - 1;
            
            while(left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if(sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // duplicate elements skip karte hai
                    while(left < right && nums[left] == nums[left + 1]) left++;
                    while(left < right && nums[right] == nums[right - 1]) right--;
                    
                    left++;
                    right--;
                }
                else if(sum < 0) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

// 2. Container With Most Water - Array (Medium)
class Solution2_Medium {
public:
    // Brute Force - Check all pairs O(n²) time, O(1) space
    int maxArea_bruteforce(vector<int>& height) {
        int maxWater = 0;
        int n = height.size();
        
        // har pair of lines check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int width = j - i;
                int minHeight = min(height[i], height[j]);
                int area = width * minHeight;
                maxWater = max(maxWater, area);
            }
        }
        
        return maxWater;
    }
    
    // Better - Optimized brute force O(n²) time, O(1) space
    int maxArea_better(vector<int>& height) {
        int maxWater = 0;
        int n = height.size();
        
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                // agar current height se better area possible nahi hai to skip
                int maxPossibleArea = height[i] * (n - 1 - i);
                if(maxPossibleArea <= maxWater) break;
                
                int area = (j - i) * min(height[i], height[j]);
                maxWater = max(maxWater, area);
            }
        }
        
        return maxWater;
    }
    
    // Optimal - Two pointers O(n) time, O(1) space
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;
        
        while(left < right) {
            int width = right - left;
            int minHeight = min(height[left], height[right]);
            int area = width * minHeight;
            maxWater = max(maxWater, area);
            
            // choti height wale pointer ko move karte hai
            if(height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxWater;
    }
};

// 3. Longest Substring Without Repeating Characters - String (Medium)
class Solution3_Medium {
public:
    // Brute Force - Check all substrings O(n³) time, O(min(m,n)) space
    int lengthOfLongestSubstring_bruteforce(string s) {
        int maxLength = 0;
        int n = s.length();
        
        // har possible substring check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                unordered_set<char> chars;
                bool hasRepeating = false;
                
                // i se j tak ka substring check karte hai
                for(int k = i; k <= j; k++) {
                    if(chars.find(s[k]) != chars.end()) {
                        hasRepeating = true;
                        break;
                    }
                    chars.insert(s[k]);
                }
                
                if(!hasRepeating) {
                    maxLength = max(maxLength, j - i + 1);
                }
            }
        }
        
        return maxLength;
    }
    
    // Better - Sliding window with set O(2n) time, O(min(m,n)) space
    int lengthOfLongestSubstring_better(string s) {
        unordered_set<char> chars;
        int maxLength = 0;
        int left = 0;
        
        for(int right = 0; right < s.length(); right++) {
            // agar duplicate character mila to left pointer move karte hai
            while(chars.find(s[right]) != chars.end()) {
                chars.erase(s[left]);
                left++;
            }
            
            chars.insert(s[right]);
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
    
    // Optimal - Sliding window with map O(n) time, O(min(m,n)) space
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charMap; // character -> last seen index
        int maxLength = 0;
        int left = 0;
        
        for(int right = 0; right < s.length(); right++) {
            if(charMap.find(s[right]) != charMap.end()) {
                // left pointer ko duplicate character ke aage move karte hai
                left = max(left, charMap[s[right]] + 1);
            }
            
            charMap[s[right]] = right;
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

// 4. Group Anagrams - String (Medium)
class Solution4_Medium {
public:
    // Brute Force - Compare every pair O(n²*m*logm) time where m is avg string length
    vector<vector<string>> groupAnagrams_bruteforce(vector<string>& strs) {
        vector<vector<string>> result;
        vector<bool> used(strs.size(), false);
        
        for(int i = 0; i < strs.size(); i++) {
            if(used[i]) continue;
            
            vector<string> group;
            group.push_back(strs[i]);
            used[i] = true;
            
            // baaki strings se match find karte hai
            for(int j = i + 1; j < strs.size(); j++) {
                if(used[j]) continue;
                
                // check if anagram
                string s1 = strs[i], s2 = strs[j];
                sort(s1.begin(), s1.end());
                sort(s2.begin(), s2.end());
                
                if(s1 == s2) {
                    group.push_back(strs[j]);
                    used[j] = true;
                }
            }
            
            result.push_back(group);
        }
        
        return result;
    }
    
    // Better - Sort each string and group O(n*m*logm) time, O(n*m) space
    vector<vector<string>> groupAnagrams_better(vector<string>& strs) {
        map<string, vector<string>> groups;
        
        for(string str : strs) {
            string sorted = str;
            sort(sorted.begin(), sorted.end());
            groups[sorted].push_back(str);
        }
        
        vector<vector<string>> result;
        for(auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
    // Optimal - Character count as key O(n*m) time, O(n*m) space
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for(string str : strs) {
            // character frequency count karte hai
            vector<int> count(26, 0);
            for(char c : str) {
                count[c - 'a']++;
            }
            
            // count array ko string mein convert karte hai
            string key = "";
            for(int i = 0; i < 26; i++) {
                key += to_string(count[i]) + "#";
            }
            
            groups[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for(auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
};

// 5. Longest Palindromic Substring - String (Medium)
class Solution5_Medium {
public:
    // Brute Force - Check all substrings O(n³) time, O(1) space
    string longestPalindrome_bruteforce(string s) {
        int maxLength = 0;
        string result = "";
        
        // har possible substring check karte hai
        for(int i = 0; i < s.length(); i++) {
            for(int j = i; j < s.length(); j++) {
                string substr = s.substr(i, j - i + 1);
                
                // palindrome check karte hai
                bool isPalin = true;
                int left = 0, right = substr.length() - 1;
                
                while(left < right) {
                    if(substr[left] != substr[right]) {
                        isPalin = false;
                        break;
                    }
                    left++;
                    right--;
                }
                
                if(isPalin && substr.length() > maxLength) {
                    maxLength = substr.length();
                    result = substr;
                }
            }
        }
        
        return result;
    }
    
    // Better - Expand around centers O(n²) time, O(1) space
    string longestPalindrome_better(string s) {
        if(s.empty()) return "";
        
        int start = 0, maxLength = 1;
        
        for(int i = 0; i < s.length(); i++) {
            // odd length palindrome (center = i)
            int len1 = expandAroundCenter(s, i, i);
            
            // even length palindrome (center between i and i+1)
            int len2 = expandAroundCenter(s, i, i + 1);
            
            int len = max(len1, len2);
            
            if(len > maxLength) {
                maxLength = len;
                start = i - (len - 1) / 2;
            }
        }
        
        return s.substr(start, maxLength);
    }
    
    int expandAroundCenter(string s, int left, int right) {
        while(left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
    
    // Optimal - Manacher's algorithm O(n) time, O(n) space
    string longestPalindrome(string s) {
        if(s.empty()) return "";
        
        // preprocessing: add '#' between characters
        string processed = "#";
        for(char c : s) {
            processed += c;
            processed += "#";
        }
        
        int n = processed.length();
        vector<int> P(n, 0); // palindrome radius array
        int center = 0, right = 0;
        int maxLen = 0, centerIndex = 0;
        
        for(int i = 0; i < n; i++) {
            int mirror = 2 * center - i;
            
            if(i < right) {
                P[i] = min(right - i, P[mirror]);
            }
            
            // expand palindrome centered at i
            while(i + P[i] + 1 < n && i - P[i] - 1 >= 0 && 
                  processed[i + P[i] + 1] == processed[i - P[i] - 1]) {
                P[i]++;
            }
            
            // update center and right boundary
            if(i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
            
            // update maximum palindrome
            if(P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        
        // extract the longest palindrome
        int start = (centerIndex - maxLen) / 2;
        return s.substr(start, maxLen);
    }
};