#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <deque>
using namespace std;

// 21. Find All Anagrams in a String - String (Medium)
class Solution21_Medium {
public:
    // Brute Force - Check every substring O(n*m*log(m)) time where m is pattern length
    vector<int> findAnagrams_bruteforce(string s, string p) {
        vector<int> result;
        if(s.length() < p.length()) return result;
        
        sort(p.begin(), p.end());
        
        // har possible substring check karte hai
        for(int i = 0; i <= s.length() - p.length(); i++) {
            string window = s.substr(i, p.length());
            sort(window.begin(), window.end());
            
            if(window == p) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Better - Sliding window with frequency comparison O(n*m) time, O(1) space
    vector<int> findAnagrams_better(string s, string p) {
        vector<int> result;
        if(s.length() < p.length()) return result;
        
        vector<int> pCount(26, 0);
        for(char c : p) {
            pCount[c - 'a']++;
        }
        
        int windowSize = p.length();
        
        for(int i = 0; i <= s.length() - windowSize; i++) {
            vector<int> windowCount(26, 0);
            
            // current window ka frequency count karte hai
            for(int j = i; j < i + windowSize; j++) {
                windowCount[s[j] - 'a']++;
            }
            
            // frequency arrays compare karte hai
            if(windowCount == pCount) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Optimal - Sliding window with rolling frequency O(n) time, O(1) space
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if(s.length() < p.length()) return result;
        
        vector<int> pCount(26, 0);
        vector<int> windowCount(26, 0);
        
        // pattern ka frequency count karte hai
        for(char c : p) {
            pCount[c - 'a']++;
        }
        
        int windowSize = p.length();
        
        // first window process karte hai
        for(int i = 0; i < windowSize; i++) {
            windowCount[s[i] - 'a']++;
        }
        
        if(windowCount == pCount) {
            result.push_back(0);
        }
        
        // sliding window
        for(int i = windowSize; i < s.length(); i++) {
            // new character add karte hai
            windowCount[s[i] - 'a']++;
            
            // old character remove karte hai
            windowCount[s[i - windowSize] - 'a']--;
            
            if(windowCount == pCount) {
                result.push_back(i - windowSize + 1);
            }
        }
        
        return result;
    }
};

// 22. Minimum Window Substring - String (Medium)
class Solution22_Medium {
public:
    // Brute Force - Check all substrings O(n³) time, O(m) space
    string minWindow_bruteforce(string s, string t) {
        if(s.length() < t.length()) return "";
        
        unordered_map<char, int> tCount;
        for(char c : t) {
            tCount[c]++;
        }
        
        string minWindow = "";
        int minLength = INT_MAX;
        
        // har possible substring check karte hai
        for(int i = 0; i < s.length(); i++) {
            for(int j = i; j < s.length(); j++) {
                unordered_map<char, int> windowCount;
                
                // current window ka count karte hai
                for(int k = i; k <= j; k++) {
                    windowCount[s[k]]++;
                }
                
                // check if window contains all characters of t
                bool isValid = true;
                for(auto& pair : tCount) {
                    if(windowCount[pair.first] < pair.second) {
                        isValid = false;
                        break;
                    }
                }
                
                if(isValid && j - i + 1 < minLength) {
                    minLength = j - i + 1;
                    minWindow = s.substr(i, minLength);
                }
            }
        }
        
        return minWindow;
    }
    
    // Better - Two pointers with frequency map O(n) time, O(m) space
    string minWindow_better(string s, string t) {
        if(s.length() < t.length()) return "";
        
        unordered_map<char, int> tCount;
        for(char c : t) {
            tCount[c]++;
        }
        
        int required = tCount.size(); // unique characters in t
        int formed = 0; // characters with desired frequency in current window
        
        unordered_map<char, int> windowCount;
        int left = 0, right = 0;
        
        string minWindow = "";
        int minLength = INT_MAX;
        
        while(right < s.length()) {
            // expand window
            char c = s[right];
            windowCount[c]++;
            
            if(tCount.find(c) != tCount.end() && windowCount[c] == tCount[c]) {
                formed++;
            }
            
            // contract window
            while(left <= right && formed == required) {
                if(right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substr(left, minLength);
                }
                
                char leftChar = s[left];
                windowCount[leftChar]--;
                
                if(tCount.find(leftChar) != tCount.end() && 
                   windowCount[leftChar] < tCount[leftChar]) {
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }
        
        return minWindow;
    }
    
    // Optimal - Optimized sliding window O(n) time, O(m) space
    string minWindow(string s, string t) {
        if(s.empty() || t.empty() || s.length() < t.length()) return "";
        
        unordered_map<char, int> tMap;
        for(char c : t) {
            tMap[c]++;
        }
        
        int required = tMap.size();
        int left = 0, right = 0;
        int formed = 0;
        
        unordered_map<char, int> windowCounts;
        
        // result tuple (window length, left, right)
        int minLen = INT_MAX, minLeft = 0, minRight = 0;
        
        while(right < s.length()) {
            char c = s[right];
            windowCounts[c]++;
            
            if(tMap.count(c) && windowCounts[c] == tMap[c]) {
                formed++;
            }
            
            while(left <= right && formed == required) {
                if(right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                    minRight = right;
                }
                
                char leftChar = s[left];
                windowCounts[leftChar]--;
                if(tMap.count(leftChar) && windowCounts[leftChar] < tMap[leftChar]) {
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }
        
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};

// 23. Product of Array Except Self (Advanced) - Array (Medium)
class Solution23_Medium {
public:
    // Brute Force - Calculate product for each index O(n²) time, O(1) space
    vector<int> productExceptSelf_bruteforce(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        
        for(int i = 0; i < n; i++) {
            int product = 1;
            
            // i ke alawa sab elements ka product
            for(int j = 0; j < n; j++) {
                if(i != j) {
                    product *= nums[j];
                }
            }
            
            result[i] = product;
        }
        
        return result;
    }
    
    // Better - Division approach (handles one zero) O(n) time, O(1) space
    vector<int> productExceptSelf_better(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        
        long long totalProduct = 1;
        int zeroCount = 0;
        int zeroIndex = -1;
        
        // total product aur zero count karte hai
        for(int i = 0; i < n; i++) {
            if(nums[i] == 0) {
                zeroCount++;
                zeroIndex = i;
            } else {
                totalProduct *= nums[i];
            }
        }
        
        for(int i = 0; i < n; i++) {
            if(zeroCount > 1) {
                result[i] = 0; // multiple zeros
            } else if(zeroCount == 1) {
                result[i] = (i == zeroIndex) ? totalProduct : 0;
            } else {
                result[i] = totalProduct / nums[i];
            }
        }
        
        return result;
    }
    
    // Optimal - Left and right products O(n) time, O(1) space
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // left products calculate karte hai
        for(int i = 1; i < n; i++) {
            result[i] = result[i-1] * nums[i-1];
        }
        
        // right products multiply karte hai
        int rightProduct = 1;
        for(int i = n - 1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return result;
    }
};

// 24. Next Permutation - Array (Medium)
class Solution24_Medium {
public:
    // Brute Force - Generate all permutations O(n!) time, O(n!) space
    void nextPermutation_bruteforce(vector<int>& nums) {
        vector<vector<int>> allPerms;
        sort(nums.begin(), nums.end());
        
        // sab permutations generate karte hai
        do {
            allPerms.push_back(nums);
        } while(next_permutation(nums.begin(), nums.end()));
        
        // original array find karte hai
        for(int i = 0; i < allPerms.size(); i++) {
            if(allPerms[i] == nums) {
                if(i + 1 < allPerms.size()) {
                    nums = allPerms[i + 1];
                } else {
                    nums = allPerms[0]; // last permutation, wrap to first
                }
                break;
            }
        }
    }
    
    // Better - Two pass algorithm O(n) time, O(1) space
    void nextPermutation_better(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;
        
        // step 1: find rightmost character smaller than its next
        while(i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        
        if(i >= 0) {
            // step 2: find ceiling of nums[i] in right part
            int j = n - 1;
            while(nums[j] <= nums[i]) {
                j--;
            }
            
            // step 3: swap
            swap(nums[i], nums[j]);
        }
        
        // step 4: reverse the right part
        reverse(nums.begin() + i + 1, nums.end());
    }
    
    // Optimal - Single pass optimized O(n) time, O(1) space
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        
        // find the largest index i such that nums[i] < nums[i+1]
        int i = n - 2;
        while(i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        
        if(i >= 0) {
            // find the largest index j > i such that nums[i] < nums[j]
            int j = n - 1;
            while(nums[j] <= nums[i]) {
                j--;
            }
            
            swap(nums[i], nums[j]);
        }
        
        // reverse the suffix starting at i+1
        reverse(nums.begin() + i + 1, nums.end());
    }
};

// 25. Search in Rotated Sorted Array - Array (Medium)
class Solution25_Medium {
public:
    // Brute Force - Linear search O(n) time, O(1) space
    int search_bruteforce(vector<int>& nums, int target) {
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    // Better - Find rotation point then binary search O(logn) time, O(1) space
    int search_better(vector<int>& nums, int target) {
        int n = nums.size();
        
        // rotation point find karte hai
        int rotationPoint = 0;
        for(int i = 1; i < n; i++) {
            if(nums[i] < nums[i-1]) {
                rotationPoint = i;
                break;
            }
        }
        
        // decide which part to search
        if(target >= nums[rotationPoint] && target <= nums[n-1]) {
            // right part mein search karte hai
            return binarySearch(nums, rotationPoint, n - 1, target);
        } else {
            // left part mein search karte hai
            return binarySearch(nums, 0, rotationPoint - 1, target);
        }
    }
    
    int binarySearch(vector<int>& nums, int left, int right, int target) {
        while(left <= right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] == target) return mid;
            else if(nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
    
    // Optimal - Direct binary search O(logn) time, O(1) space
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] == target) return mid;
            
            // check which half is sorted
            if(nums[left] <= nums[mid]) {
                // left half is sorted
                if(target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // right half is sorted
                if(target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};