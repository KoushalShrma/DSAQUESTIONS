#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

// 59. Fizz Buzz - Array/String
class Solution59 {
public:
    // Brute Force - Check each number individually O(n) time, O(1) space
    vector<string> fizzBuzz_bruteforce(int n) {
        vector<string> result;
        
        for(int i = 1; i <= n; i++) {
            if(i % 3 == 0 && i % 5 == 0) {
                result.push_back("FizzBuzz");
            }
            else if(i % 3 == 0) {
                result.push_back("Fizz");
            }
            else if(i % 5 == 0) {
                result.push_back("Buzz");
            }
            else {
                result.push_back(to_string(i));
            }
        }
        
        return result;
    }
    
    // Better - String concatenation approach O(n) time, O(1) space
    vector<string> fizzBuzz_better(int n) {
        vector<string> result;
        
        for(int i = 1; i <= n; i++) {
            string str = "";
            
            if(i % 3 == 0) str += "Fizz";
            if(i % 5 == 0) str += "Buzz";
            
            if(str.empty()) {
                str = to_string(i);
            }
            
            result.push_back(str);
        }
        
        return result;
    }
    
    // Optimal - Avoid modulo with counters O(n) time, O(1) space
    vector<string> fizzBuzz(int n) {
        vector<string> result;
        
        for(int i = 1; i <= n; i++) {
            bool divisibleBy3 = (i % 3 == 0);
            bool divisibleBy5 = (i % 5 == 0);
            
            if(divisibleBy3 && divisibleBy5) {
                result.push_back("FizzBuzz");
            }
            else if(divisibleBy3) {
                result.push_back("Fizz");
            }
            else if(divisibleBy5) {
                result.push_back("Buzz");
            }
            else {
                result.push_back(to_string(i));
            }
        }
        
        return result;
    }
};

// 60. Reverse Bits - Bit Manipulation
class Solution60 {
public:
    // Brute Force - Extract each bit O(32) time, O(1) space
    uint32_t reverseBits_bruteforce(uint32_t n) {
        uint32_t result = 0;
        
        // har bit extract karte hai aur result mein add karte hai
        for(int i = 0; i < 32; i++) {
            uint32_t bit = (n >> i) & 1; // i-th bit extract karte hai
            result = result | (bit << (31 - i)); // (31-i) position pe set karte hai
        }
        
        return result;
    }
    
    // Better - Build result bit by bit O(32) time, O(1) space
    uint32_t reverseBits_better(uint32_t n) {
        uint32_t result = 0;
        
        for(int i = 0; i < 32; i++) {
            result = (result << 1) | (n & 1); // result ko left shift aur last bit add
            n >>= 1; // n ko right shift
        }
        
        return result;
    }
    
    // Optimal - Bit manipulation tricks O(logn) time, O(1) space
    uint32_t reverseBits(uint32_t n) {
        // Divide and conquer approach
        n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
        n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
        n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
        n = (n >> 16) | (n << 16);
        
        return n;
    }
};

// 61. Number of 1 Bits - Bit Manipulation
class Solution61 {
public:
    // Brute Force - Check each bit O(32) time, O(1) space
    int hammingWeight_bruteforce(uint32_t n) {
        int count = 0;
        
        // har bit check karte hai
        for(int i = 0; i < 32; i++) {
            if((n >> i) & 1) {
                count++;
            }
        }
        
        return count;
    }
    
    // Better - Keep shifting O(32) time, O(1) space
    int hammingWeight_better(uint32_t n) {
        int count = 0;
        
        while(n != 0) {
            if(n & 1) count++; // last bit check karte hai
            n >>= 1; // right shift
        }
        
        return count;
    }
    
    // Optimal - Brian Kernighan's algorithm O(number of 1s) time, O(1) space
    int hammingWeight(uint32_t n) {
        int count = 0;
        
        // n & (n-1) removes rightmost set bit
        while(n != 0) {
            n &= (n - 1); // rightmost 1 bit remove karte hai
            count++;
        }
        
        return count;
    }
};

// 62. House Robber - Dynamic Programming
class Solution62 {
public:
    // Brute Force - Try all possibilities O(2^n) time, O(n) space
    int rob_bruteforce(vector<int>& nums) {
        return robHelper(nums, 0);
    }
    
    int robHelper(vector<int>& nums, int index) {
        if(index >= nums.size()) return 0;
        
        // current house rob karte hai ya nahi
        int robCurrent = nums[index] + robHelper(nums, index + 2);
        int skipCurrent = robHelper(nums, index + 1);
        
        return max(robCurrent, skipCurrent);
    }
    
    // Better - Memoization O(n) time, O(n) space
    int rob_better(vector<int>& nums) {
        vector<int> memo(nums.size(), -1);
        return robMemo(nums, 0, memo);
    }
    
    int robMemo(vector<int>& nums, int index, vector<int>& memo) {
        if(index >= nums.size()) return 0;
        if(memo[index] != -1) return memo[index];
        
        int robCurrent = nums[index] + robMemo(nums, index + 2, memo);
        int skipCurrent = robMemo(nums, index + 1, memo);
        
        memo[index] = max(robCurrent, skipCurrent);
        return memo[index];
    }
    
    // Optimal - Space optimized DP O(n) time, O(1) space
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size() == 1) return nums[0];
        
        int prev2 = 0; // dp[i-2]
        int prev1 = nums[0]; // dp[i-1]
        
        for(int i = 1; i < nums.size(); i++) {
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};

// 63. Number Complement - Bit Manipulation
class Solution63 {
public:
    // Brute Force - Convert to binary string O(logn) time, O(logn) space
    int findComplement_bruteforce(int num) {
        string binary = "";
        int temp = num;
        
        // binary representation banate hai
        while(temp > 0) {
            binary = (temp % 2 ? "1" : "0") + binary;
            temp /= 2;
        }
        
        // complement banate hai
        for(char& c : binary) {
            c = (c == '0') ? '1' : '0';
        }
        
        // back to integer
        int result = 0;
        for(char c : binary) {
            result = result * 2 + (c - '0');
        }
        
        return result;
    }
    
    // Better - Bit by bit flip O(logn) time, O(1) space
    int findComplement_better(int num) {
        int result = 0;
        int bitPosition = 0;
        int temp = num;
        
        while(temp > 0) {
            int bit = temp & 1; // last bit
            int flippedBit = 1 - bit; // flip bit
            result |= (flippedBit << bitPosition); // set in result
            
            temp >>= 1;
            bitPosition++;
        }
        
        return result;
    }
    
    // Optimal - XOR with mask O(logn) time, O(1) space
    int findComplement(int num) {
        // mask banate hai jisme num ke saare bits set hai
        int mask = 0;
        int temp = num;
        
        while(temp > 0) {
            mask = (mask << 1) | 1;
            temp >>= 1;
        }
        
        // XOR with mask gives complement
        return num ^ mask;
    }
};

// 64. Perfect Number - Math
class Solution64 {
public:
    // Brute Force - Check all divisors O(n) time, O(1) space
    bool checkPerfectNumber_bruteforce(int num) {
        if(num <= 1) return false;
        
        int sum = 1; // 1 is always a proper divisor
        
        // 2 se num-1 tak sab divisors check karte hai
        for(int i = 2; i < num; i++) {
            if(num % i == 0) {
                sum += i;
            }
        }
        
        return sum == num;
    }
    
    // Better - Check only up to sqrt(n) O(√n) time, O(1) space
    bool checkPerfectNumber_better(int num) {
        if(num <= 1) return false;
        
        int sum = 1; // 1 is always included
        
        // sqrt(num) tak check karte hai
        for(int i = 2; i * i <= num; i++) {
            if(num % i == 0) {
                sum += i;
                
                // corresponding divisor add karte hai
                if(i != num / i) { // avoid adding same divisor twice
                    sum += num / i;
                }
            }
        }
        
        return sum == num;
    }
    
    // Optimal - Use known perfect numbers O(1) time, O(1) space
    bool checkPerfectNumber(int num) {
        // Known perfect numbers in int range: 6, 28, 496, 8128, 33550336
        return num == 6 || num == 28 || num == 496 || 
               num == 8128 || num == 33550336;
    }
};