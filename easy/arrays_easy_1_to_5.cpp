#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

// 1. Two Sum - Array
class Solution {
public:
    // Brute Force - O(n²) time, O(1) space
    vector<int> twoSum_bruteforce(vector<int>& nums, int target) {
        int n = nums.size();
        // har element ke saath baaki sab elements check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {}; // not found
    }
    
    // Better - Sorting approach O(nlogn) time, O(n) space
    vector<int> twoSum_better(vector<int>& nums, int target) {
        vector<pair<int, int>> indexed_nums;
        // original indices ke saath values store karte hai
        for(int i = 0; i < nums.size(); i++) {
            indexed_nums.push_back({nums[i], i});
        }
        
        sort(indexed_nums.begin(), indexed_nums.end());
        
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            int sum = indexed_nums[left].first + indexed_nums[right].first;
            if(sum == target) {
                return {indexed_nums[left].second, indexed_nums[right].second};
            }
            else if(sum < target) {
                left++;
            }
            else {
                right--;
            }
        }
        return {};
    }
    
    // Optimal - Hash Map O(n) time, O(n) space
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap; // value -> index
        
        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            // agar complement pehle se exist karta hai
            if(numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            // current element ko map mein store karte hai
            numMap[nums[i]] = i;
        }
        return {};
    }
};

// 2. Best Time to Buy and Sell Stock - Array
class Solution2 {
public:
    // Brute Force - O(n²) time, O(1) space
    int maxProfit_bruteforce(vector<int>& prices) {
        int maxProfit = 0;
        int n = prices.size();
        
        // har din buy karne ki possibility check karte hai
        for(int i = 0; i < n; i++) {
            // us din ke baad har din sell karne ki possibility
            for(int j = i + 1; j < n; j++) {
                int profit = prices[j] - prices[i];
                maxProfit = max(maxProfit, profit);
            }
        }
        return maxProfit;
    }
    
    // Better - Track minimum so far O(n) time, O(1) space
    int maxProfit_better(vector<int>& prices) {
        if(prices.size() <= 1) return 0;
        
        int minPrice = prices[0];
        int maxProfit = 0;
        
        for(int i = 1; i < prices.size(); i++) {
            // current price pe sell karne ka profit calculate karte hai
            int currentProfit = prices[i] - minPrice;
            maxProfit = max(maxProfit, currentProfit);
            
            // minimum price update karte hai
            minPrice = min(minPrice, prices[i]);
        }
        return maxProfit;
    }
    
    // Optimal - Single pass O(n) time, O(1) space
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for(int price : prices) {
            // agar current price minimum hai to update karte hai
            if(price < minPrice) {
                minPrice = price;
            }
            // nahi to profit calculate karte hai
            else if(price - minPrice > maxProfit) {
                maxProfit = price - minPrice;
            }
        }
        return maxProfit;
    }
};

// 3. Contains Duplicate - Array
class Solution3 {
public:
    // Brute Force - O(n²) time, O(1) space
    bool containsDuplicate_bruteforce(vector<int>& nums) {
        int n = nums.size();
        // har element ko baaki sab se compare karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Better - Sorting O(nlogn) time, O(1) space
    bool containsDuplicate_better(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // sorted array mein adjacent elements check karte hai
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] == nums[i-1]) {
                return true;
            }
        }
        return false;
    }
    
    // Optimal - Hash Set O(n) time, O(n) space
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        
        for(int num : nums) {
            // agar element pehle se exist karta hai
            if(seen.find(num) != seen.end()) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
};

// 4. Maximum Subarray (Kadane's Algorithm) - Array
class Solution4 {
public:
    // Brute Force - O(n³) time, O(1) space
    int maxSubArray_bruteforce(vector<int>& nums) {
        int n = nums.size();
        int maxSum = INT_MIN;
        
        // har possible subarray check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                int currentSum = 0;
                // i se j tak ka sum calculate karte hai
                for(int k = i; k <= j; k++) {
                    currentSum += nums[k];
                }
                maxSum = max(maxSum, currentSum);
            }
        }
        return maxSum;
    }
    
    // Better - O(n²) time, O(1) space
    int maxSubArray_better(vector<int>& nums) {
        int n = nums.size();
        int maxSum = INT_MIN;
        
        for(int i = 0; i < n; i++) {
            int currentSum = 0;
            // i se start karte hue har subarray ka sum
            for(int j = i; j < n; j++) {
                currentSum += nums[j];
                maxSum = max(maxSum, currentSum);
            }
        }
        return maxSum;
    }
    
    // Optimal - Kadane's Algorithm O(n) time, O(1) space
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];
        
        for(int i = 1; i < nums.size(); i++) {
            // ya to current element se naya subarray start karte hai
            // ya phir existing mein add karte hai
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }
        return maxSum;
    }
};

// 5. Product of Array Except Self - Array
class Solution5 {
public:
    // Brute Force - O(n²) time, O(1) space (excluding output)
    vector<int> productExceptSelf_bruteforce(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        
        // har index ke liye baaki sab ka product calculate karte hai
        for(int i = 0; i < n; i++) {
            int product = 1;
            for(int j = 0; j < n; j++) {
                if(i != j) {
                    product *= nums[j];
                }
            }
            result[i] = product;
        }
        return result;
    }
    
    // Better - Using division O(n) time, O(1) space
    vector<int> productExceptSelf_better(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        
        // total product calculate karte hai
        int totalProduct = 1;
        int zeroCount = 0;
        
        for(int num : nums) {
            if(num == 0) {
                zeroCount++;
            } else {
                totalProduct *= num;
            }
        }
        
        for(int i = 0; i < n; i++) {
            if(zeroCount > 1) {
                result[i] = 0;
            }
            else if(zeroCount == 1) {
                result[i] = (nums[i] == 0) ? totalProduct : 0;
            }
            else {
                result[i] = totalProduct / nums[i];
            }
        }
        return result;
    }
    
    // Optimal - Left and Right products O(n) time, O(1) space
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // left products - result[i] contains product of all elements to left of i
        for(int i = 1; i < n; i++) {
            result[i] = result[i-1] * nums[i-1];
        }
        
        // right products - multiply with right side products
        int rightProduct = 1;
        for(int i = n-1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return result;
    }
};