#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <climits>
using namespace std;

// 6. 3Sum Closest - Array (Medium)
class Solution6_Medium {
public:
    // Brute Force - Check all triplets O(n³) time, O(1) space
    int threeSumClosest_bruteforce(vector<int>& nums, int target) {
        int closestSum = nums[0] + nums[1] + nums[2];
        int minDiff = abs(closestSum - target);
        
        // har possible triplet check karte hai
        for(int i = 0; i < nums.size() - 2; i++) {
            for(int j = i + 1; j < nums.size() - 1; j++) {
                for(int k = j + 1; k < nums.size(); k++) {
                    int currentSum = nums[i] + nums[j] + nums[k];
                    int currentDiff = abs(currentSum - target);
                    
                    if(currentDiff < minDiff) {
                        minDiff = currentDiff;
                        closestSum = currentSum;
                    }
                }
            }
        }
        
        return closestSum;
    }
    
    // Better - Sort and pruning O(n³) time, O(1) space
    int threeSumClosest_better(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closestSum = nums[0] + nums[1] + nums[2];
        int minDiff = abs(closestSum - target);
        
        for(int i = 0; i < nums.size() - 2; i++) {
            for(int j = i + 1; j < nums.size() - 1; j++) {
                for(int k = j + 1; k < nums.size(); k++) {
                    int currentSum = nums[i] + nums[j] + nums[k];
                    
                    if(currentSum == target) {
                        return target; // exact match mila
                    }
                    
                    int currentDiff = abs(currentSum - target);
                    if(currentDiff < minDiff) {
                        minDiff = currentDiff;
                        closestSum = currentSum;
                    }
                    
                    // agar sum target se bada hai aur array sorted hai
                    if(currentSum > target) break;
                }
            }
        }
        
        return closestSum;
    }
    
    // Optimal - Sort and two pointers O(n²) time, O(1) space
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closestSum = nums[0] + nums[1] + nums[2];
        
        for(int i = 0; i < nums.size() - 2; i++) {
            int left = i + 1, right = nums.size() - 1;
            
            while(left < right) {
                int currentSum = nums[i] + nums[left] + nums[right];
                
                if(currentSum == target) {
                    return target;
                }
                
                // agar current sum target ke closest hai
                if(abs(currentSum - target) < abs(closestSum - target)) {
                    closestSum = currentSum;
                }
                
                if(currentSum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return closestSum;
    }
};

// 7. Letter Combinations of a Phone Number - String (Medium)
class Solution7_Medium {
public:
    // Brute Force - Generate all combinations iteratively O(4^n) time, O(4^n) space
    vector<string> letterCombinations_bruteforce(string digits) {
        if(digits.empty()) return {};
        
        vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result = {""};
        
        // har digit ke liye combinations expand karte hai
        for(char digit : digits) {
            vector<string> temp;
            string letters = phone[digit - '0'];
            
            for(string combo : result) {
                for(char letter : letters) {
                    temp.push_back(combo + letter);
                }
            }
            
            result = temp;
        }
        
        return result;
    }
    
    // Better - Recursive backtracking O(4^n) time, O(4^n) space
    vector<string> letterCombinations_better(string digits) {
        if(digits.empty()) return {};
        
        vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result;
        string current = "";
        
        backtrack(digits, 0, current, phone, result);
        return result;
    }
    
    void backtrack(string digits, int index, string current, 
                   vector<string>& phone, vector<string>& result) {
        if(index == digits.length()) {
            result.push_back(current);
            return;
        }
        
        string letters = phone[digits[index] - '0'];
        for(char letter : letters) {
            backtrack(digits, index + 1, current + letter, phone, result);
        }
    }
    
    // Optimal - Iterative with queue O(4^n) time, O(4^n) space
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        
        vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result = {""};
        
        for(char digit : digits) {
            vector<string> nextLevel;
            string letters = phone[digit - '0'];
            
            for(string combination : result) {
                for(char letter : letters) {
                    nextLevel.push_back(combination + letter);
                }
            }
            
            result = move(nextLevel);
        }
        
        return result;
    }
};

// 8. Remove Nth Node From End of List - Array (treating as medium array problem)
class Solution8_Medium {
public:
    // Brute Force - Find all subarrays of length n-1 O(n²) time, O(n) space
    vector<int> removeNthFromEnd_bruteforce(vector<int>& nums, int n) {
        // This simulates removing nth element from end in array
        if(n > nums.size()) return nums;
        
        int indexToRemove = nums.size() - n;
        vector<int> result;
        
        for(int i = 0; i < nums.size(); i++) {
            if(i != indexToRemove) {
                result.push_back(nums[i]);
            }
        }
        
        return result;
    }
    
    // Better - Calculate index and create new array O(n) time, O(n) space
    vector<int> removeNthFromEnd_better(vector<int>& nums, int n) {
        int size = nums.size();
        if(n > size) return nums;
        
        int removeIndex = size - n;
        vector<int> result;
        
        for(int i = 0; i < size; i++) {
            if(i != removeIndex) {
                result.push_back(nums[i]);
            }
        }
        
        return result;
    }
    
    // Optimal - Two pointers O(n) time, O(1) space for in-place
    vector<int> removeNthFromEnd(vector<int>& nums, int n) {
        if(n > nums.size()) return nums;
        
        // two pointers approach simulation
        int first = 0, second = 0;
        
        // first pointer ko n steps aage move karte hai
        for(int i = 0; i < n; i++) {
            first++;
        }
        
        // agar first end pe pahuch gaya to first element remove karna hai
        if(first >= nums.size()) {
            return vector<int>(nums.begin() + 1, nums.end());
        }
        
        // dono pointers end tak move karte hai
        while(first < nums.size() - 1) {
            first++;
            second++;
        }
        
        // second pointer ke aage wala element remove karte hai
        vector<int> result;
        for(int i = 0; i < nums.size(); i++) {
            if(i != second + 1) {
                result.push_back(nums[i]);
            }
        }
        
        return result;
    }
};

// 9. Generate Parentheses - String (Medium)
class Solution9_Medium {
public:
    // Brute Force - Generate all possible strings and filter O(4^n * n) time
    vector<string> generateParenthesis_bruteforce(int n) {
        vector<string> result;
        generateAll("", 2 * n, result);
        
        // valid parentheses filter karte hai
        vector<string> valid;
        for(string s : result) {
            if(isValid(s)) {
                valid.push_back(s);
            }
        }
        
        return valid;
    }
    
    void generateAll(string current, int remaining, vector<string>& result) {
        if(remaining == 0) {
            result.push_back(current);
            return;
        }
        
        generateAll(current + "(", remaining - 1, result);
        generateAll(current + ")", remaining - 1, result);
    }
    
    bool isValid(string s) {
        int count = 0;
        for(char c : s) {
            if(c == '(') count++;
            else count--;
            if(count < 0) return false;
        }
        return count == 0;
    }
    
    // Better - Backtracking with constraints O(4^n / √n) time, O(4^n / √n) space
    vector<string> generateParenthesis_better(int n) {
        vector<string> result;
        backtrack("", 0, 0, n, result);
        return result;
    }
    
    void backtrack(string current, int open, int close, int max, vector<string>& result) {
        if(current.length() == max * 2) {
            result.push_back(current);
            return;
        }
        
        if(open < max) {
            backtrack(current + "(", open + 1, close, max, result);
        }
        
        if(close < open) {
            backtrack(current + ")", open, close + 1, max, result);
        }
    }
    
    // Optimal - Dynamic Programming approach O(4^n / √n) time, O(4^n / √n) space
    vector<string> generateParenthesis(int n) {
        if(n == 0) return {""};
        
        vector<string> result;
        
        // har i ke liye (i se pehle) + (n-1-i ke baad) combinations
        for(int i = 0; i < n; i++) {
            vector<string> left = generateParenthesis(i);
            vector<string> right = generateParenthesis(n - 1 - i);
            
            for(string l : left) {
                for(string r : right) {
                    result.push_back("(" + l + ")" + r);
                }
            }
        }
        
        return result;
    }
};

// 10. Merge Intervals - Array (Medium)
class Solution10_Medium {
public:
    // Brute Force - Check each interval with all others O(n²) time, O(n) space
    vector<vector<int>> merge_bruteforce(vector<vector<int>>& intervals) {
        if(intervals.empty()) return {};
        
        vector<vector<int>> result;
        vector<bool> merged(intervals.size(), false);
        
        for(int i = 0; i < intervals.size(); i++) {
            if(merged[i]) continue;
            
            vector<int> current = intervals[i];
            merged[i] = true;
            
            // current interval ko baaki sab se merge karte hai
            bool foundMerge = true;
            while(foundMerge) {
                foundMerge = false;
                
                for(int j = 0; j < intervals.size(); j++) {
                    if(merged[j]) continue;
                    
                    // overlapping check karte hai
                    if(current[1] >= intervals[j][0] && intervals[j][1] >= current[0]) {
                        current[0] = min(current[0], intervals[j][0]);
                        current[1] = max(current[1], intervals[j][1]);
                        merged[j] = true;
                        foundMerge = true;
                    }
                }
            }
            
            result.push_back(current);
        }
        
        return result;
    }
    
    // Better - Sort then merge O(nlogn) time, O(n) space
    vector<vector<int>> merge_better(vector<vector<int>>& intervals) {
        if(intervals.empty()) return {};
        
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result;
        
        for(auto interval : intervals) {
            // agar result empty hai ya current interval overlap nahi karta
            if(result.empty() || result.back()[1] < interval[0]) {
                result.push_back(interval);
            } else {
                // merge karte hai
                result.back()[1] = max(result.back()[1], interval[1]);
            }
        }
        
        return result;
    }
    
    // Optimal - Efficient sorting and merging O(nlogn) time, O(1) extra space
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty()) return {};
        
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });
        
        vector<vector<int>> merged;
        
        for(const auto& interval : intervals) {
            if(merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            } else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }
        
        return merged;
    }
};