#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <climits>
using namespace std;

// 51. Majority Element - Array
class Solution51 {
public:
    // Brute Force - Count each element O(n²) time, O(1) space
    int majorityElement_bruteforce(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 0; i < n; i++) {
            int count = 0;
            
            // current element ka count karte hai
            for(int j = 0; j < n; j++) {
                if(nums[j] == nums[i]) {
                    count++;
                }
            }
            
            // agar majority element hai
            if(count > n / 2) {
                return nums[i];
            }
        }
        
        return -1;
    }
    
    // Better - Sorting O(nlogn) time, O(1) space
    int majorityElement_better(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // sorted array mein middle element majority hoga
        return nums[nums.size() / 2];
    }
    
    // Optimal - Boyer-Moore Voting Algorithm O(n) time, O(1) space
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0];
        int count = 1;
        
        // majority candidate find karte hai
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] == candidate) {
                count++;
            } else {
                count--;
                if(count == 0) {
                    candidate = nums[i];
                    count = 1;
                }
            }
        }
        
        return candidate; // problem guarantee karta hai majority exists
    }
};

// 52. Excel Sheet Column Title - Math
class Solution52 {
public:
    // Brute Force - Repeated division O(log26(n)) time, O(log26(n)) space
    string convertToTitle_bruteforce(int columnNumber) {
        string result = "";
        
        while(columnNumber > 0) {
            columnNumber--; // 1-indexed to 0-indexed
            char c = 'A' + (columnNumber % 26);
            result = c + result;
            columnNumber /= 26;
        }
        
        return result;
    }
    
    // Better - Build string and reverse O(log26(n)) time, O(log26(n)) space
    string convertToTitle_better(int columnNumber) {
        string result = "";
        
        while(columnNumber > 0) {
            columnNumber--; // important: 1-indexed adjustment
            result += ('A' + columnNumber % 26);
            columnNumber /= 26;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
    
    // Optimal - Direct string building O(log26(n)) time, O(1) extra space
    string convertToTitle(int columnNumber) {
        string result = "";
        
        while(columnNumber > 0) {
            columnNumber--; // convert to 0-indexed
            result = char('A' + columnNumber % 26) + result;
            columnNumber /= 26;
        }
        
        return result;
    }
};

// 53. Factorial Trailing Zeroes - Math
class Solution53 {
public:
    // Brute Force - Calculate factorial and count O(n) time, O(1) space (overflow issue)
    int trailingZeroes_bruteforce(int n) {
        // Note: This approach will overflow for large n
        long long factorial = 1;
        
        for(int i = 1; i <= n; i++) {
            factorial *= i;
        }
        
        int count = 0;
        while(factorial > 0 && factorial % 10 == 0) {
            count++;
            factorial /= 10;
        }
        
        return count;
    }
    
    // Better - Count factors of 2 and 5 O(n) time, O(1) space
    int trailingZeroes_better(int n) {
        int count2 = 0, count5 = 0;
        
        // 1 se n tak har number mein 2 aur 5 ke factors count karte hai
        for(int i = 1; i <= n; i++) {
            int num = i;
            
            // factors of 2
            while(num % 2 == 0) {
                count2++;
                num /= 2;
            }
            
            // factors of 5
            num = i;
            while(num % 5 == 0) {
                count5++;
                num /= 5;
            }
        }
        
        // trailing zeros = min(count of 2s, count of 5s)
        return min(count2, count5);
    }
    
    // Optimal - Count factors of 5 only O(logn) time, O(1) space
    int trailingZeroes(int n) {
        int count = 0;
        
        // factors of 5 count karte hai (2s humesha sufficient hote hai)
        for(int i = 5; i <= n; i *= 5) {
            count += n / i;
        }
        
        return count;
    }
};

// 54. Add Digits - Math
class Solution54 {
public:
    // Brute Force - Simulate the process O(logn) time, O(1) space
    int addDigits_bruteforce(int num) {
        while(num >= 10) {
            int sum = 0;
            
            // digits ka sum calculate karte hai
            while(num > 0) {
                sum += num % 10;
                num /= 10;
            }
            
            num = sum;
        }
        
        return num;
    }
    
    // Better - Recursive approach O(logn) time, O(logn) space
    int addDigits_better(int num) {
        if(num < 10) return num;
        
        int sum = 0;
        while(num > 0) {
            sum += num % 10;
            num /= 10;
        }
        
        return addDigits_better(sum);
    }
    
    // Optimal - Digital root formula O(1) time, O(1) space
    int addDigits(int num) {
        if(num == 0) return 0;
        
        // digital root formula: 1 + (num - 1) % 9
        return 1 + (num - 1) % 9;
    }
};

// 55. Ugly Number - Math
class Solution55 {
public:
    // Brute Force - Check all prime factors O(logn) time, O(1) space
    bool isUgly_bruteforce(int n) {
        if(n <= 0) return false;
        
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}; // enough primes
        
        // har prime factor check karte hai
        for(int i = 0; i < primes.size() && primes[i] <= n; i++) {
            while(n % primes[i] == 0) {
                if(primes[i] > 5) return false; // ugly number nahi hai
                n /= primes[i];
            }
        }
        
        return n == 1;
    }
    
    // Better - Factorize step by step O(logn) time, O(1) space
    bool isUgly_better(int n) {
        if(n <= 0) return false;
        
        // divide by all factors other than 2, 3, 5
        for(int i = 2; i * i <= n; i++) {
            if(i != 2 && i != 3 && i != 5) {
                while(n % i == 0) {
                    return false; // ugly factor mila
                }
            }
        }
        
        // 2, 3, 5 se divide karte hai
        while(n % 2 == 0) n /= 2;
        while(n % 3 == 0) n /= 3;
        while(n % 5 == 0) n /= 5;
        
        return n == 1;
    }
    
    // Optimal - Only check 2, 3, 5 O(logn) time, O(1) space
    bool isUgly(int n) {
        if(n <= 0) return false;
        
        // 2, 3, 5 ke sab factors remove karte hai
        while(n % 2 == 0) n /= 2;
        while(n % 3 == 0) n /= 3;
        while(n % 5 == 0) n /= 5;
        
        // agar sirf 1 bacha hai to ugly number hai
        return n == 1;
    }
};

// 56. Power of Two - Math
class Solution56 {
public:
    // Brute Force - Keep dividing by 2 O(logn) time, O(1) space
    bool isPowerOfTwo_bruteforce(int n) {
        if(n <= 0) return false;
        
        while(n > 1) {
            if(n % 2 != 0) return false; // odd number, can't be power of 2
            n /= 2;
        }
        
        return true;
    }
    
    // Better - Keep multiplying by 2 O(logn) time, O(1) space
    bool isPowerOfTwo_better(int n) {
        if(n <= 0) return false;
        
        long long power = 1;
        while(power < n) {
            power *= 2;
        }
        
        return power == n;
    }
    
    // Optimal - Bit manipulation O(1) time, O(1) space
    bool isPowerOfTwo(int n) {
        // power of 2 mein sirf ek bit set hoti hai
        // n & (n-1) == 0 for powers of 2
        return n > 0 && (n & (n - 1)) == 0;
    }
};

// 57. Power of Three - Math
class Solution57 {
public:
    // Brute Force - Keep dividing by 3 O(logn) time, O(1) space
    bool isPowerOfThree_bruteforce(int n) {
        if(n <= 0) return false;
        
        while(n > 1) {
            if(n % 3 != 0) return false;
            n /= 3;
        }
        
        return true;
    }
    
    // Better - Logarithm approach O(1) time, O(1) space (precision issues)
    bool isPowerOfThree_better(int n) {
        if(n <= 0) return false;
        
        // log3(n) should be integer
        double logResult = log10(n) / log10(3);
        return abs(logResult - round(logResult)) < 1e-10;
    }
    
    // Optimal - Maximum power of 3 in int range O(1) time, O(1) space
    bool isPowerOfThree(int n) {
        // 3^19 = 1162261467 is largest power of 3 in int range
        // agar n power of 3 hai to 3^19 % n == 0 hoga
        return n > 0 && 1162261467 % n == 0;
    }
};

// 58. Power of Four - Math
class Solution58 {
public:
    // Brute Force - Keep dividing by 4 O(logn) time, O(1) space
    bool isPowerOfFour_bruteforce(int n) {
        if(n <= 0) return false;
        
        while(n > 1) {
            if(n % 4 != 0) return false;
            n /= 4;
        }
        
        return true;
    }
    
    // Better - Check if power of 2 and odd positions O(1) time, O(1) space
    bool isPowerOfFour_better(int n) {
        if(n <= 0) return false;
        
        // power of 2 hona chahiye
        if((n & (n - 1)) != 0) return false;
        
        // bit odd positions (1, 3, 5, ...) mein honi chahiye
        // 0x55555555 = 01010101010101010101010101010101 in binary
        return (n & 0x55555555) != 0;
    }
    
    // Optimal - Mathematical property O(1) time, O(1) space
    bool isPowerOfFour(int n) {
        // power of 2 hona chahiye aur (n-1) % 3 == 0 hona chahiye
        return n > 0 && (n & (n - 1)) == 0 && (n - 1) % 3 == 0;
    }
};