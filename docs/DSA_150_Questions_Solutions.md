# DSA 150 Questions with Complete Solutions

## Table of Contents
- [Easy Questions (77)](#easy-questions-77)
  - [Arrays (10)](#arrays-easy)
  - [Strings (5)](#strings-easy)
  - [LinkedList (5)](#linkedlist-easy)
  - [Stack & Queue (4)](#stack-queue-easy)
  - [Set & Map (5)](#set-map-easy)
  - [Miscellaneous (48)](#miscellaneous-easy)
- [Medium Questions (55) - Arrays & Strings Only](#medium-questions-55)
- [Hard Questions (22) - Arrays & Strings Only](#hard-questions-22)

---

## Easy Questions (77)

### Arrays (Easy)

#### 1. Two Sum
**LeetCode Problem: #1**
```cpp
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

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
    vector<int> twoSum_optimal(vector<int>& nums, int target) {
        unordered_map<int, int> mp;
        
        for(int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            // agar complement pehle se present hai to answer mil gaya
            if(mp.find(complement) != mp.end()) {
                return {mp[complement], i};
            }
            mp[nums[i]] = i; // current element ko map mein daal dete hai
        }
        return {};
    }
};
```

---
