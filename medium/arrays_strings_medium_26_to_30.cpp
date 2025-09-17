#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stack>
using namespace std;

// 26. Kth Largest Element in an Array - Array (Medium)
class Solution26_Medium {
public:
    // Brute Force - Sort and return O(nlogn) time, O(1) space
    int findKthLargest_bruteforce(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), greater<int>());
        return nums[k-1];
    }
    
    // Better - Min heap approach O(nlogk) time, O(k) space
    int findKthLargest_better(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        for(int num : nums) {
            minHeap.push(num);
            
            // heap size ko k mein maintain karte hai
            if(minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        return minHeap.top();
    }
    
    // Optimal - QuickSelect algorithm O(n) average, O(n²) worst time, O(1) space
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
    }
    
private:
    int quickSelect(vector<int>& nums, int left, int right, int k) {
        if(left == right) return nums[left];
        
        // random pivot choose karte hai
        int pivotIndex = left + rand() % (right - left + 1);
        int finalPosition = partition(nums, left, right, pivotIndex);
        
        if(finalPosition == k) {
            return nums[finalPosition];
        } else if(finalPosition < k) {
            return quickSelect(nums, finalPosition + 1, right, k);
        } else {
            return quickSelect(nums, left, finalPosition - 1, k);
        }
    }
    
    int partition(vector<int>& nums, int left, int right, int pivotIndex) {
        int pivotValue = nums[pivotIndex];
        
        // pivot ko end mein move karte hai
        swap(nums[pivotIndex], nums[right]);
        
        int storeIndex = left;
        for(int i = left; i < right; i++) {
            if(nums[i] < pivotValue) {
                swap(nums[i], nums[storeIndex]);
                storeIndex++;
            }
        }
        
        // pivot ko final position pe move karte hai
        swap(nums[storeIndex], nums[right]);
        return storeIndex;
    }
};

// 27. Top K Frequent Elements - Array (Medium)
class Solution27_Medium {
public:
    // Brute Force - Count and sort O(nlogn) time, O(n) space
    vector<int> topKFrequent_bruteforce(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        
        // frequency count karte hai
        for(int num : nums) {
            count[num]++;
        }
        
        // pairs banate hai aur sort karte hai
        vector<pair<int, int>> freqPairs;
        for(auto& p : count) {
            freqPairs.push_back({p.second, p.first}); // {frequency, element}
        }
        
        sort(freqPairs.begin(), freqPairs.end(), greater<pair<int, int>>());
        
        vector<int> result;
        for(int i = 0; i < k; i++) {
            result.push_back(freqPairs[i].second);
        }
        
        return result;
    }
    
    // Better - Min heap approach O(nlogk) time, O(n) space
    vector<int> topKFrequent_better(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for(int num : nums) {
            count[num]++;
        }
        
        // min heap maintain karte hai size k ka
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        for(auto& p : count) {
            minHeap.push({p.second, p.first});
            
            if(minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        vector<int> result;
        while(!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
    
    // Optimal - Bucket sort O(n) time, O(n) space
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for(int num : nums) {
            count[num]++;
        }
        
        // bucket banate hai frequency ke liye
        vector<vector<int>> buckets(nums.size() + 1);
        
        for(auto& p : count) {
            buckets[p.second].push_back(p.first);
        }
        
        vector<int> result;
        
        // highest frequency se start karte hai
        for(int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
            for(int num : buckets[i]) {
                result.push_back(num);
                if(result.size() == k) break;
            }
        }
        
        return result;
    }
};

// 28. Find Peak Element - Array (Medium)
class Solution28_Medium {
public:
    // Brute Force - Linear search O(n) time, O(1) space
    int findPeakElement_bruteforce(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 0; i < n; i++) {
            bool isPeak = true;
            
            // left neighbor check karte hai
            if(i > 0 && nums[i] <= nums[i-1]) {
                isPeak = false;
            }
            
            // right neighbor check karte hai
            if(i < n-1 && nums[i] <= nums[i+1]) {
                isPeak = false;
            }
            
            if(isPeak) return i;
        }
        
        return 0; // should not reach here
    }
    
    // Better - Linear scan with optimization O(n) time, O(1) space
    int findPeakElement_better(vector<int>& nums) {
        int n = nums.size();
        
        // edge cases
        if(n == 1) return 0;
        if(nums[0] > nums[1]) return 0;
        if(nums[n-1] > nums[n-2]) return n-1;
        
        // middle elements check karte hai
        for(int i = 1; i < n-1; i++) {
            if(nums[i] > nums[i-1] && nums[i] > nums[i+1]) {
                return i;
            }
        }
        
        return 0;
    }
    
    // Optimal - Binary search O(logn) time, O(1) space
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while(left < right) {
            int mid = left + (right - left) / 2;
            
            if(nums[mid] > nums[mid + 1]) {
                // peak left side mein hai (ya mid hi peak hai)
                right = mid;
            } else {
                // peak right side mein hai
                left = mid + 1;
            }
        }
        
        return left;
    }
};

// 29. Sort Colors - Array (Medium)
class Solution29_Medium {
public:
    // Brute Force - Count and reconstruct O(n) time, O(1) space
    void sortColors_bruteforce(vector<int>& nums) {
        int count0 = 0, count1 = 0, count2 = 0;
        
        // har color ka count karte hai
        for(int num : nums) {
            if(num == 0) count0++;
            else if(num == 1) count1++;
            else count2++;
        }
        
        // array reconstruct karte hai
        int index = 0;
        
        // 0s fill karte hai
        for(int i = 0; i < count0; i++) {
            nums[index++] = 0;
        }
        
        // 1s fill karte hai
        for(int i = 0; i < count1; i++) {
            nums[index++] = 1;
        }
        
        // 2s fill karte hai
        for(int i = 0; i < count2; i++) {
            nums[index++] = 2;
        }
    }
    
    // Better - Two pass approach O(n) time, O(1) space
    void sortColors_better(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        // first pass: move all 0s to left
        for(int i = 0; i <= right; i++) {
            while(nums[i] == 0 && i > left) {
                swap(nums[i], nums[left]);
                left++;
            }
            if(nums[i] == 0) left = i + 1;
        }
        
        // second pass: move all 2s to right
        for(int i = right; i >= left; i--) {
            while(nums[i] == 2 && i < right) {
                swap(nums[i], nums[right]);
                right--;
            }
            if(nums[i] == 2) right = i - 1;
        }
    }
    
    // Optimal - Dutch National Flag algorithm O(n) time, O(1) space
    void sortColors(vector<int>& nums) {
        int left = 0; // boundary for 0s
        int right = nums.size() - 1; // boundary for 2s
        int current = 0;
        
        while(current <= right) {
            if(nums[current] == 0) {
                swap(nums[current], nums[left]);
                left++;
                current++;
            }
            else if(nums[current] == 2) {
                swap(nums[current], nums[right]);
                right--;
                // current ko increment nahi karte kyunki swapped element check karna hai
            }
            else {
                current++; // nums[current] == 1
            }
        }
    }
};

// 30. Set Matrix Zeroes - Array (Medium)
class Solution30_Medium {
public:
    // Brute Force - Mark rows and columns O(m*n*(m+n)) time, O(1) space
    void setZeroes_bruteforce(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        
        // har zero element ke liye row aur column mark karte hai
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == 0) {
                    // row mark karte hai (except zeros)
                    for(int k = 0; k < n; k++) {
                        if(matrix[i][k] != 0) {
                            matrix[i][k] = INT_MIN; // temporary marker
                        }
                    }
                    
                    // column mark karte hai (except zeros)
                    for(int k = 0; k < m; k++) {
                        if(matrix[k][j] != 0) {
                            matrix[k][j] = INT_MIN; // temporary marker
                        }
                    }
                }
            }
        }
        
        // markers ko zero banate hai
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == INT_MIN) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    
    // Better - Extra space for marking O(m*n) time, O(m+n) space
    void setZeroes_better(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<bool> rowZero(m, false);
        vector<bool> colZero(n, false);
        
        // zero positions mark karte hai
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] == 0) {
                    rowZero[i] = true;
                    colZero[j] = true;
                }
            }
        }
        
        // marked rows ko zero karte hai
        for(int i = 0; i < m; i++) {
            if(rowZero[i]) {
                for(int j = 0; j < n; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // marked columns ko zero karte hai
        for(int j = 0; j < n; j++) {
            if(colZero[j]) {
                for(int i = 0; i < m; i++) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    
    // Optimal - Use first row and column as markers O(m*n) time, O(1) space
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool firstRowZero = false, firstColZero = false;
        
        // check if first row has zero
        for(int j = 0; j < n; j++) {
            if(matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }
        
        // check if first column has zero
        for(int i = 0; i < m; i++) {
            if(matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }
        
        // use first row and column as markers
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                if(matrix[i][j] == 0) {
                    matrix[i][0] = 0; // mark row
                    matrix[0][j] = 0; // mark column
                }
            }
        }
        
        // set zeros based on markers (except first row and column)
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // handle first row
        if(firstRowZero) {
            for(int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
        
        // handle first column
        if(firstColZero) {
            for(int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};