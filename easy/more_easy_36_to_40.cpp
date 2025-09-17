#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <set>
using namespace std;

// 36. Length of Last Word - String
class Solution36 {
public:
    // Brute Force - Split into words O(n) time, O(n) space
    int lengthOfLastWord_bruteforce(string s) {
        vector<string> words;
        string word = "";
        
        // string ko words mein split karte hai
        for(char c : s) {
            if(c == ' ') {
                if(!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
            } else {
                word += c;
            }
        }
        if(!word.empty()) words.push_back(word);
        
        return words.empty() ? 0 : words.back().length();
    }
    
    // Better - Trim and find last space O(n) time, O(1) space
    int lengthOfLastWord_better(string s) {
        // trailing spaces remove karte hai
        int end = s.length() - 1;
        while(end >= 0 && s[end] == ' ') {
            end--;
        }
        
        if(end < 0) return 0;
        
        // last word ka length find karte hai
        int start = end;
        while(start >= 0 && s[start] != ' ') {
            start--;
        }
        
        return end - start;
    }
    
    // Optimal - Single pass from end O(n) time, O(1) space
    int lengthOfLastWord(string s) {
        int length = 0;
        int i = s.length() - 1;
        
        // trailing spaces skip karte hai
        while(i >= 0 && s[i] == ' ') {
            i--;
        }
        
        // last word ka length count karte hai
        while(i >= 0 && s[i] != ' ') {
            length++;
            i--;
        }
        
        return length;
    }
};

// 37. Search Insert Position - Binary Search
class Solution37 {
public:
    // Brute Force - Linear search O(n) time, O(1) space
    int searchInsert_bruteforce(vector<int>& nums, int target) {
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] >= target) {
                return i;
            }
        }
        return nums.size(); // end mein insert karna hai
    }
    
    // Better - Modified binary search O(logn) time, O(1) space
    int searchInsert_better(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int result = nums.size();
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] >= target) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
    // Optimal - Standard binary search O(logn) time, O(1) space
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] == target) {
                return mid;
            } else if(nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return left; // insertion position
    }
};

// 38. Remove Element - Array
class Solution38 {
public:
    // Brute Force - Create new array O(n) time, O(n) space
    int removeElement_bruteforce(vector<int>& nums, int val) {
        vector<int> result;
        
        // val ke alawa sab elements copy karte hai
        for(int num : nums) {
            if(num != val) {
                result.push_back(num);
            }
        }
        
        // original array mein copy karte hai
        for(int i = 0; i < result.size(); i++) {
            nums[i] = result[i];
        }
        
        return result.size();
    }
    
    // Better - Two pointers (stable order) O(n) time, O(1) space
    int removeElement_better(vector<int>& nums, int val) {
        int writeIndex = 0;
        
        for(int readIndex = 0; readIndex < nums.size(); readIndex++) {
            if(nums[readIndex] != val) {
                nums[writeIndex] = nums[readIndex];
                writeIndex++;
            }
        }
        
        return writeIndex;
    }
    
    // Optimal - Two pointers (swap from end) O(n) time, O(1) space
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        int right = nums.size() - 1;
        
        while(left <= right) {
            if(nums[left] == val) {
                // val element ko end se swap karte hai
                nums[left] = nums[right];
                right--;
            } else {
                left++;
            }
        }
        
        return left; // new length
    }
};

// 39. Implement strStr() / Find Needle in Haystack - String
class Solution39 {
public:
    // Brute Force - Check every position O(n*m) time, O(1) space
    int strStr_bruteforce(string haystack, string needle) {
        if(needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        
        if(m > n) return -1;
        
        // har position pe needle check karte hai
        for(int i = 0; i <= n - m; i++) {
            bool found = true;
            for(int j = 0; j < m; j++) {
                if(haystack[i + j] != needle[j]) {
                    found = false;
                    break;
                }
            }
            if(found) return i;
        }
        
        return -1;
    }
    
    // Better - Using substr O(n*m) time, O(m) space
    int strStr_better(string haystack, string needle) {
        if(needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        
        if(m > n) return -1;
        
        for(int i = 0; i <= n - m; i++) {
            if(haystack.substr(i, m) == needle) {
                return i;
            }
        }
        
        return -1;
    }
    
    // Optimal - KMP algorithm O(n+m) time, O(m) space
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        
        if(m > n) return -1;
        
        // LPS array build karte hai
        vector<int> lps(m, 0);
        buildLPS(needle, lps);
        
        int i = 0; // haystack pointer
        int j = 0; // needle pointer
        
        while(i < n) {
            if(haystack[i] == needle[j]) {
                i++;
                j++;
            }
            
            if(j == m) {
                return i - j; // match found
            }
            else if(i < n && haystack[i] != needle[j]) {
                if(j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        
        return -1;
    }
    
private:
    void buildLPS(string pattern, vector<int>& lps) {
        int len = 0; // length of previous longest prefix suffix
        int i = 1;
        
        while(i < pattern.length()) {
            if(pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if(len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
};

// 40. Count and Say - String
class Solution40 {
public:
    // Brute Force - Simulate process O(n * L) time where L is length
    string countAndSay_bruteforce(int n) {
        string result = "1";
        
        for(int i = 1; i < n; i++) {
            string nextResult = "";
            int count = 1;
            char currentChar = result[0];
            
            // current string process karte hai
            for(int j = 1; j < result.length(); j++) {
                if(result[j] == currentChar) {
                    count++;
                } else {
                    nextResult += to_string(count) + currentChar;
                    currentChar = result[j];
                    count = 1;
                }
            }
            
            // last group add karte hai
            nextResult += to_string(count) + currentChar;
            result = nextResult;
        }
        
        return result;
    }
    
    // Better - Two pointers approach O(n * L) time, O(L) space
    string countAndSay_better(int n) {
        string current = "1";
        
        for(int i = 1; i < n; i++) {
            string next = "";
            int left = 0;
            
            while(left < current.length()) {
                int right = left;
                // same characters count karte hai
                while(right < current.length() && current[right] == current[left]) {
                    right++;
                }
                
                int count = right - left;
                next += to_string(count) + current[left];
                left = right;
            }
            
            current = next;
        }
        
        return current;
    }
    
    // Optimal - Efficient string building O(n * L) time, O(1) extra space
    string countAndSay(int n) {
        string result = "1";
        
        for(int i = 1; i < n; i++) {
            result = getNext(result);
        }
        
        return result;
    }
    
private:
    string getNext(string s) {
        string next = "";
        int i = 0;
        
        while(i < s.length()) {
            char currentChar = s[i];
            int count = 1;
            
            // consecutive same characters count karte hai
            while(i + count < s.length() && s[i + count] == currentChar) {
                count++;
            }
            
            next += to_string(count) + currentChar;
            i += count;
        }
        
        return next;
    }
};