#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 31. Subarray Sum Equals K - Array (Medium)
class Solution31_Medium {
public:
    // Brute Force - Check all subarrays O(n³) time, O(1) space
    int subarraySum_bruteforce(vector<int>& nums, int k) {
        int count = 0;
        int n = nums.size();
        
        // har possible subarray check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                int sum = 0;
                
                // i se j tak ka sum calculate karte hai
                for(int l = i; l <= j; l++) {
                    sum += nums[l];
                }
                
                if(sum == k) count++;
            }
        }
        
        return count;
    }
    
    // Better - Optimize sum calculation O(n²) time, O(1) space
    int subarraySum_better(vector<int>& nums, int k) {
        int count = 0;
        int n = nums.size();
        
        for(int i = 0; i < n; i++) {
            int sum = 0;
            
            for(int j = i; j < n; j++) {
                sum += nums[j];
                
                if(sum == k) count++;
            }
        }
        
        return count;
    }
    
    // Optimal - Prefix sum with hash map O(n) time, O(n) space
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixCount;
        prefixCount[0] = 1; // empty subarray ka sum 0 hai
        
        int count = 0;
        int prefixSum = 0;
        
        for(int num : nums) {
            prefixSum += num;
            
            // agar (prefixSum - k) exist karta hai
            // matlab koi subarray hai jiska sum k hai
            if(prefixCount.find(prefixSum - k) != prefixCount.end()) {
                count += prefixCount[prefixSum - k];
            }
            
            prefixCount[prefixSum]++;
        }
        
        return count;
    }
};

// 32. Contiguous Array - Array (Medium)
class Solution32_Medium {
public:
    // Brute Force - Check all subarrays O(n²) time, O(1) space
    int findMaxLength_bruteforce(vector<int>& nums) {
        int maxLength = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            int zeros = 0, ones = 0;
            
            for(int j = i; j < nums.size(); j++) {
                if(nums[j] == 0) zeros++;
                else ones++;
                
                if(zeros == ones) {
                    maxLength = max(maxLength, j - i + 1);
                }
            }
        }
        
        return maxLength;
    }
    
    // Better - Convert to sum problem O(n²) time, O(1) space
    int findMaxLength_better(vector<int>& nums) {
        int maxLength = 0;
        
        // 0 ko -1 treat karte hai, 1 ko +1
        for(int i = 0; i < nums.size(); i++) {
            int sum = 0;
            
            for(int j = i; j < nums.size(); j++) {
                sum += (nums[j] == 0) ? -1 : 1;
                
                // agar sum 0 hai to equal 0s and 1s hai
                if(sum == 0) {
                    maxLength = max(maxLength, j - i + 1);
                }
            }
        }
        
        return maxLength;
    }
    
    // Optimal - Hash map with running sum O(n) time, O(n) space
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> sumIndexMap;
        sumIndexMap[0] = -1; // sum 0 at index -1
        
        int maxLength = 0;
        int runningSum = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            // 0 ko -1, 1 ko +1 treat karte hai
            runningSum += (nums[i] == 0) ? -1 : 1;
            
            if(sumIndexMap.find(runningSum) != sumIndexMap.end()) {
                // same sum pehle dekha hai
                maxLength = max(maxLength, i - sumIndexMap[runningSum]);
            } else {
                sumIndexMap[runningSum] = i;
            }
        }
        
        return maxLength;
    }
};

// 33. Longest Increasing Subsequence - Array (Medium)  
class Solution33_Medium {
public:
    // Brute Force - Try all subsequences O(2^n) time, O(n) space
    int lengthOfLIS_bruteforce(vector<int>& nums) {
        return lisHelper(nums, 0, INT_MIN);
    }
    
    int lisHelper(vector<int>& nums, int index, int prevValue) {
        if(index >= nums.size()) return 0;
        
        int exclude = lisHelper(nums, index + 1, prevValue);
        
        int include = 0;
        if(nums[index] > prevValue) {
            include = 1 + lisHelper(nums, index + 1, nums[index]);
        }
        
        return max(include, exclude);
    }
    
    // Better - Dynamic Programming O(n²) time, O(n) space
    int lengthOfLIS_better(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> dp(n, 1); // dp[i] = LIS ending at index i
        
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
    
    // Optimal - Binary search approach O(nlogn) time, O(n) space
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails; // tails[i] = smallest tail of increasing subsequence of length i+1
        
        for(int num : nums) {
            // binary search for position to insert/replace
            int left = 0, right = tails.size();
            
            while(left < right) {
                int mid = left + (right - left) / 2;
                
                if(tails[mid] < num) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            
            // agar position end mein hai to extend karte hai
            if(left == tails.size()) {
                tails.push_back(num);
            } else {
                tails[left] = num; // replace karte hai
            }
        }
        
        return tails.size();
    }
};

// 34. Coin Change - Array (Medium)
class Solution34_Medium {
public:
    // Brute Force - Try all combinations O(amount^coins) time, O(amount) space
    int coinChange_bruteforce(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        if(amount < 0) return -1;
        
        int minCoins = INT_MAX;
        
        // har coin try karte hai
        for(int coin : coins) {
            int subResult = coinChange_bruteforce(coins, amount - coin);
            
            if(subResult != -1) {
                minCoins = min(minCoins, subResult + 1);
            }
        }
        
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
    
    // Better - Memoization O(amount * coins) time, O(amount) space
    int coinChange_better(vector<int>& coins, int amount) {
        vector<int> memo(amount + 1, -2); // -2 means not computed
        return coinChangeHelper(coins, amount, memo);
    }
    
    int coinChangeHelper(vector<int>& coins, int amount, vector<int>& memo) {
        if(amount == 0) return 0;
        if(amount < 0) return -1;
        if(memo[amount] != -2) return memo[amount];
        
        int minCoins = INT_MAX;
        
        for(int coin : coins) {
            int subResult = coinChangeHelper(coins, amount - coin, memo);
            
            if(subResult != -1) {
                minCoins = min(minCoins, subResult + 1);
            }
        }
        
        memo[amount] = (minCoins == INT_MAX) ? -1 : minCoins;
        return memo[amount];
    }
    
    // Optimal - Bottom-up DP O(amount * coins) time, O(amount) space
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1); // initialize with impossible value
        dp[0] = 0;
        
        for(int i = 1; i <= amount; i++) {
            for(int coin : coins) {
                if(coin <= i) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

// 35. House Robber II - Array (Medium)
class Solution35_Medium {
public:
    // Brute Force - Try all combinations O(2^n) time, O(n) space
    int rob_bruteforce(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        if(nums.size() == 2) return max(nums[0], nums[1]);
        
        // case 1: include first house (exclude last)
        int case1 = robHelper(nums, 0, nums.size() - 2);
        
        // case 2: exclude first house (can include last)
        int case2 = robHelper(nums, 1, nums.size() - 1);
        
        return max(case1, case2);
    }
    
    int robHelper(vector<int>& nums, int start, int end) {
        if(start > end) return 0;
        if(start == end) return nums[start];
        
        // current house rob karte hai ya skip karte hai
        int rob = nums[start] + robHelper(nums, start + 2, end);
        int skip = robHelper(nums, start + 1, end);
        
        return max(rob, skip);
    }
    
    // Better - DP with two cases O(n) time, O(n) space
    int rob_better(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        if(nums.size() == 2) return max(nums[0], nums[1]);
        
        // case 1: rob houses 0 to n-2
        int case1 = robLinear(nums, 0, nums.size() - 2);
        
        // case 2: rob houses 1 to n-1
        int case2 = robLinear(nums, 1, nums.size() - 1);
        
        return max(case1, case2);
    }
    
    int robLinear(vector<int>& nums, int start, int end) {
        int n = end - start + 1;
        if(n == 1) return nums[start];
        
        vector<int> dp(n);
        dp[0] = nums[start];
        dp[1] = max(nums[start], nums[start + 1]);
        
        for(int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], dp[i-2] + nums[start + i]);
        }
        
        return dp[n-1];
    }
    
    // Optimal - Space optimized DP O(n) time, O(1) space
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        if(nums.size() == 2) return max(nums[0], nums[1]);
        
        // case 1: houses 0 to n-2
        int case1 = robOptimal(nums, 0, nums.size() - 2);
        
        // case 2: houses 1 to n-1
        int case2 = robOptimal(nums, 1, nums.size() - 1);
        
        return max(case1, case2);
    }
    
    int robOptimal(vector<int>& nums, int start, int end) {
        int prev2 = 0, prev1 = 0;
        
        for(int i = start; i <= end; i++) {
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};