#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;

// 46. Merge Sorted Array - Array
class Solution46 {
public:
    // Brute Force - Extra space O((m+n)log(m+n)) time, O(m+n) space
    void merge_bruteforce(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> result;
        
        // dono arrays ke valid elements copy karte hai
        for(int i = 0; i < m; i++) {
            result.push_back(nums1[i]);
        }
        
        for(int i = 0; i < n; i++) {
            result.push_back(nums2[i]);
        }
        
        // sort karte hai
        sort(result.begin(), result.end());
        
        // nums1 mein copy karte hai
        for(int i = 0; i < result.size(); i++) {
            nums1[i] = result[i];
        }
    }
    
    // Better - Two pointers from beginning O(m+n) time, O(m) space
    void merge_better(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums1Copy(nums1.begin(), nums1.begin() + m);
        
        int i = 0, j = 0, k = 0;
        
        // merge karte hai
        while(i < m && j < n) {
            if(nums1Copy[i] <= nums2[j]) {
                nums1[k] = nums1Copy[i];
                i++;
            } else {
                nums1[k] = nums2[j];
                j++;
            }
            k++;
        }
        
        // remaining elements
        while(i < m) {
            nums1[k] = nums1Copy[i];
            i++;
            k++;
        }
        
        while(j < n) {
            nums1[k] = nums2[j];
            j++;
            k++;
        }
    }
    
    // Optimal - Two pointers from end O(m+n) time, O(1) space
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1; // nums1 ka last valid element
        int j = n - 1; // nums2 ka last element
        int k = m + n - 1; // nums1 ka last position
        
        // end se start karte hai (bade elements pehle place karte hai)
        while(i >= 0 && j >= 0) {
            if(nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }
        
        // agar nums2 ke elements remaining hai
        while(j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
        
        // nums1 ke elements already in place hai
    }
};

// 47. Pascal's Triangle - Array
class Solution47 {
public:
    // Brute Force - Calculate each element using combination formula O(n³) time
    vector<vector<int>> generate_bruteforce(int numRows) {
        vector<vector<int>> result;
        
        for(int i = 0; i < numRows; i++) {
            vector<int> row;
            
            for(int j = 0; j <= i; j++) {
                // C(i, j) calculate karte hai
                int value = 1;
                for(int k = 0; k < j; k++) {
                    value = value * (i - k) / (k + 1);
                }
                row.push_back(value);
            }
            
            result.push_back(row);
        }
        
        return result;
    }
    
    // Better - Build using addition property O(n²) time, O(n²) space
    vector<vector<int>> generate_better(int numRows) {
        vector<vector<int>> result;
        
        for(int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1); // initialize with 1s
            
            // middle elements calculate karte hai
            for(int j = 1; j < i; j++) {
                row[j] = result[i-1][j-1] + result[i-1][j];
            }
            
            result.push_back(row);
        }
        
        return result;
    }
    
    // Optimal - Space optimized O(n²) time, O(1) extra space
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        
        for(int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1);
            
            // row ke middle elements ko previous row se calculate karte hai
            for(int j = 1; j < i; j++) {
                row[j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
            
            triangle.push_back(row);
        }
        
        return triangle;
    }
};

// 48. Best Time to Buy and Sell Stock II - Array
class Solution48 {
public:
    // Brute Force - Try all possible transactions O(2^n) time
    int maxProfit_bruteforce(vector<int>& prices) {
        return helper(prices, 0, false);
    }
    
    int helper(vector<int>& prices, int index, bool holding) {
        if(index >= prices.size()) return 0;
        
        int doNothing = helper(prices, index + 1, holding);
        
        if(holding) {
            // sell kar sakte hai
            int sell = prices[index] + helper(prices, index + 1, false);
            return max(doNothing, sell);
        } else {
            // buy kar sakte hai
            int buy = -prices[index] + helper(prices, index + 1, true);
            return max(doNothing, buy);
        }
    }
    
    // Better - Dynamic Programming O(n) time, O(n) space
    int maxProfit_better(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        
        vector<vector<int>> dp(n, vector<int>(2, 0));
        // dp[i][0] = profit without stock on day i
        // dp[i][1] = profit with stock on day i
        
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        
        for(int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]); // sell
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]); // buy
        }
        
        return dp[n-1][0];
    }
    
    // Optimal - Greedy approach O(n) time, O(1) space
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        
        // har consecutive pair mein profit hai to add karte hai
        for(int i = 1; i < prices.size(); i++) {
            if(prices[i] > prices[i-1]) {
                profit += prices[i] - prices[i-1];
            }
        }
        
        return profit;
    }
};

// 49. Valid Palindrome II - String
class Solution49 {
public:
    // Brute Force - Try removing each character O(n²) time, O(n) space
    bool validPalindrome_bruteforce(string s) {
        // pehle check karte hai ki already palindrome hai
        if(isPalindrome(s)) return true;
        
        // har character remove karke check karte hai
        for(int i = 0; i < s.length(); i++) {
            string modified = s.substr(0, i) + s.substr(i + 1);
            if(isPalindrome(modified)) return true;
        }
        
        return false;
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
    
    // Better - Skip mismatched character O(n) time, O(1) space
    bool validPalindrome_better(string s) {
        return canBePalindrome(s, 0, s.length() - 1, false);
    }
    
    bool canBePalindrome(string& s, int left, int right, bool deleted) {
        while(left < right) {
            if(s[left] == s[right]) {
                left++;
                right--;
            } else {
                if(deleted) return false; // already deleted one character
                
                // left character delete karne ki try karte hai
                // ya right character delete karne ki try karte hai
                return canBePalindrome(s, left + 1, right, true) ||
                       canBePalindrome(s, left, right - 1, true);
            }
        }
        return true;
    }
    
    // Optimal - Two pointers with one chance O(n) time, O(1) space
    bool validPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        
        while(left < right) {
            if(s[left] != s[right]) {
                // ek character skip karne ki chance hai
                return isPalindromeRange(s, left + 1, right) || 
                       isPalindromeRange(s, left, right - 1);
            }
            left++;
            right--;
        }
        
        return true; // already palindrome
    }
    
private:
    bool isPalindromeRange(string& s, int left, int right) {
        while(left < right) {
            if(s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

// 50. Excel Sheet Column Number - Math
class Solution50 {
public:
    // Brute Force - Character by character O(n) time, O(1) space
    int titleToNumber_bruteforce(string columnTitle) {
        int result = 0;
        
        // har character ko process karte hai
        for(char c : columnTitle) {
            int digitValue = c - 'A' + 1; // A=1, B=2, ..., Z=26
            result = result * 26 + digitValue;
        }
        
        return result;
    }
    
    // Better - Right to left processing O(n) time, O(1) space
    int titleToNumber_better(string columnTitle) {
        int result = 0;
        int power = 1;
        
        // right se left process karte hai
        for(int i = columnTitle.length() - 1; i >= 0; i--) {
            int digitValue = columnTitle[i] - 'A' + 1;
            result += digitValue * power;
            power *= 26;
        }
        
        return result;
    }
    
    // Optimal - Left to right with base conversion O(n) time, O(1) space
    int titleToNumber(string columnTitle) {
        int result = 0;
        
        // left se right process karte hai (base 26 conversion)
        for(char c : columnTitle) {
            result = result * 26 + (c - 'A' + 1);
        }
        
        return result;
    }
};