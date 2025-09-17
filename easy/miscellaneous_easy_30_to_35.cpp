#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

// 30. Missing Number - Array
class Solution30 {
public:
    // Brute Force - O(n²) time, O(1) space
    int missingNumber_bruteforce(vector<int>& nums) {
        int n = nums.size();
        
        // 0 se n tak har number check karte hai
        for(int i = 0; i <= n; i++) {
            bool found = false;
            for(int num : nums) {
                if(num == i) {
                    found = true;
                    break;
                }
            }
            if(!found) return i;
        }
        return -1;
    }
    
    // Better - Sorting O(nlogn) time, O(1) space
    int missingNumber_better(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // sorted array mein missing number find karte hai
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != i) {
                return i;
            }
        }
        
        return nums.size(); // last number missing hai
    }
    
    // Optimal - Math approach O(n) time, O(1) space
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int expectedSum = n * (n + 1) / 2; // 0+1+2+...+n ka sum
        int actualSum = 0;
        
        for(int num : nums) {
            actualSum += num;
        }
        
        return expectedSum - actualSum;
    }
};

// 31. Climbing Stairs - Dynamic Programming (Easy)
class Solution31 {
public:
    // Brute Force - Recursive O(2^n) time, O(n) space
    int climbStairs_bruteforce(int n) {
        if(n <= 1) return 1;
        return climbStairs_bruteforce(n-1) + climbStairs_bruteforce(n-2);
    }
    
    // Better - Memoization O(n) time, O(n) space
    int climbStairs_better(int n) {
        vector<int> memo(n + 1, -1);
        return helper(n, memo);
    }
    
    int helper(int n, vector<int>& memo) {
        if(n <= 1) return 1;
        if(memo[n] != -1) return memo[n];
        
        memo[n] = helper(n-1, memo) + helper(n-2, memo);
        return memo[n];
    }
    
    // Optimal - Space optimized DP O(n) time, O(1) space
    int climbStairs(int n) {
        if(n <= 1) return 1;
        
        int prev2 = 1; // ways to reach step 0
        int prev1 = 1; // ways to reach step 1
        
        for(int i = 2; i <= n; i++) {
            int current = prev1 + prev2; // Fibonacci pattern
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};

// 32. Palindrome Number - Math
class Solution32 {
public:
    // Brute Force - Convert to string O(logn) time, O(logn) space
    bool isPalindrome_bruteforce(int x) {
        if(x < 0) return false;
        
        string s = to_string(x);
        string reversed = s;
        reverse(reversed.begin(), reversed.end());
        
        return s == reversed;
    }
    
    // Better - Reverse entire number O(logn) time, O(1) space
    bool isPalindrome_better(int x) {
        if(x < 0) return false;
        
        long long original = x;
        long long reversed = 0;
        
        while(x > 0) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        
        return original == reversed;
    }
    
    // Optimal - Reverse half number O(logn) time, O(1) space
    bool isPalindrome(int x) {
        // negative numbers aur ending with 0 (except 0) not palindrome
        if(x < 0 || (x % 10 == 0 && x != 0)) return false;
        
        int reversedHalf = 0;
        
        // half reverse karte hai
        while(x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }
        
        // even digits: x == reversedHalf
        // odd digits: x == reversedHalf / 10
        return x == reversedHalf || x == reversedHalf / 10;
    }
};

// 33. Roman to Integer - String
class Solution33 {
public:
    // Brute Force - Check all subtractive cases O(n) time, O(1) space
    int romanToInt_bruteforce(string s) {
        int result = 0;
        int i = 0;
        
        while(i < s.length()) {
            // subtractive cases check karte hai
            if(i < s.length() - 1 && s[i] == 'I' && s[i+1] == 'V') {
                result += 4;
                i += 2;
            }
            else if(i < s.length() - 1 && s[i] == 'I' && s[i+1] == 'X') {
                result += 9;
                i += 2;
            }
            else if(i < s.length() - 1 && s[i] == 'X' && s[i+1] == 'L') {
                result += 40;
                i += 2;
            }
            else if(i < s.length() - 1 && s[i] == 'X' && s[i+1] == 'C') {
                result += 90;
                i += 2;
            }
            else if(i < s.length() - 1 && s[i] == 'C' && s[i+1] == 'D') {
                result += 400;
                i += 2;
            }
            else if(i < s.length() - 1 && s[i] == 'C' && s[i+1] == 'M') {
                result += 900;
                i += 2;
            }
            // single characters
            else if(s[i] == 'I') {
                result += 1;
                i++;
            }
            else if(s[i] == 'V') {
                result += 5;
                i++;
            }
            else if(s[i] == 'X') {
                result += 10;
                i++;
            }
            else if(s[i] == 'L') {
                result += 50;
                i++;
            }
            else if(s[i] == 'C') {
                result += 100;
                i++;
            }
            else if(s[i] == 'D') {
                result += 500;
                i++;
            }
            else if(s[i] == 'M') {
                result += 1000;
                i++;
            }
            else {
                i++;
            }
        }
        
        return result;
    }
    
    // Better - Using map O(n) time, O(1) space
    int romanToInt_better(string s) {
        unordered_map<char, int> romanMap = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };
        
        int result = 0;
        
        for(int i = 0; i < s.length(); i++) {
            // agar current value next value se choti hai to subtract karte hai
            if(i < s.length() - 1 && romanMap[s[i]] < romanMap[s[i+1]]) {
                result -= romanMap[s[i]];
            }
            else {
                result += romanMap[s[i]];
            }
        }
        
        return result;
    }
    
    // Optimal - Direct mapping O(n) time, O(1) space
    int romanToInt(string s) {
        int result = 0;
        
        for(int i = 0; i < s.length(); i++) {
            int current = getValue(s[i]);
            int next = (i + 1 < s.length()) ? getValue(s[i+1]) : 0;
            
            // agar current next se chota hai to subtract karte hai
            if(current < next) {
                result -= current;
            }
            else {
                result += current;
            }
        }
        
        return result;
    }
    
private:
    int getValue(char c) {
        switch(c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }
};

// 34. Sqrt(x) - Binary Search
class Solution34 {
public:
    // Brute Force - Linear search O(√n) time, O(1) space
    int mySqrt_bruteforce(int x) {
        if(x == 0) return 0;
        
        // 1 se x tak har number check karte hai
        for(long long i = 1; i <= x; i++) {
            if(i * i == x) return i;
            if(i * i > x) return i - 1;
        }
        
        return 0;
    }
    
    // Better - Newton's method O(logn) time, O(1) space
    int mySqrt_better(int x) {
        if(x < 2) return x;
        
        long long guess = x / 2;
        
        // Newton's method: next = (current + x/current) / 2
        while(guess * guess > x) {
            guess = (guess + x / guess) / 2;
        }
        
        return guess;
    }
    
    // Optimal - Binary Search O(logn) time, O(1) space  
    int mySqrt(int x) {
        if(x < 2) return x;
        
        long long left = 2, right = x / 2;
        
        while(left <= right) {
            long long mid = left + (right - left) / 2;
            long long square = mid * mid;
            
            if(square == x) return mid;
            else if(square < x) left = mid + 1;
            else right = mid - 1;
        }
        
        return right; // floor value
    }
};

// 35. Add Binary - String
class Solution35 {
public:
    // Brute Force - Convert to decimal and back O(n) time, O(1) space (for small numbers)
    string addBinary_bruteforce(string a, string b) {
        // Note: This approach fails for large binary strings
        long long num1 = 0, num2 = 0;
        
        // binary to decimal
        for(char c : a) {
            num1 = num1 * 2 + (c - '0');
        }
        for(char c : b) {
            num2 = num2 * 2 + (c - '0');
        }
        
        long long sum = num1 + num2;
        
        // decimal to binary
        if(sum == 0) return "0";
        
        string result = "";
        while(sum > 0) {
            result = char('0' + sum % 2) + result;
            sum /= 2;
        }
        
        return result;
    }
    
    // Better - Bit manipulation with carry O(max(n,m)) time, O(1) space
    string addBinary_better(string a, string b) {
        string result = "";
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        
        while(i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            
            if(i >= 0) {
                sum += a[i] - '0';
                i--;
            }
            
            if(j >= 0) {
                sum += b[j] - '0';
                j--;
            }
            
            result = char('0' + sum % 2) + result;
            carry = sum / 2;
        }
        
        return result;
    }
    
    // Optimal - In-place addition O(max(n,m)) time, O(1) space
    string addBinary(string a, string b) {
        string result = "";
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        
        while(i >= 0 || j >= 0 || carry) {
            int sum = carry;
            
            if(i >= 0) sum += a[i--] - '0';
            if(j >= 0) sum += b[j--] - '0';
            
            result = to_string(sum % 2) + result;
            carry = sum / 2;
        }
        
        return result;
    }
};