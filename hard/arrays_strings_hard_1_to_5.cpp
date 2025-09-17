#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
using namespace std;

// 1. Median of Two Sorted Arrays - Array (Hard)
class Solution1_Hard {
public:
    // Brute Force - Merge and find median O(m+n) time, O(m+n) space
    double findMedianSortedArrays_bruteforce(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merged;
        int i = 0, j = 0;
        
        // merge karte hai
        while(i < nums1.size() && j < nums2.size()) {
            if(nums1[i] <= nums2[j]) {
                merged.push_back(nums1[i++]);
            } else {
                merged.push_back(nums2[j++]);
            }
        }
        
        // remaining elements
        while(i < nums1.size()) merged.push_back(nums1[i++]);
        while(j < nums2.size()) merged.push_back(nums2[j++]);
        
        int n = merged.size();
        if(n % 2 == 1) {
            return merged[n/2];
        } else {
            return (merged[n/2-1] + merged[n/2]) / 2.0;
        }
    }
    
    // Better - Two pointers without extra space O(m+n) time, O(1) space
    double findMedianSortedArrays_better(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int total = m + n;
        int half = total / 2;
        
        int i = 0, j = 0;
        int prev = 0, curr = 0;
        
        // median position tak traverse karte hai
        for(int k = 0; k <= half; k++) {
            prev = curr;
            
            if(i < m && (j >= n || nums1[i] <= nums2[j])) {
                curr = nums1[i++];
            } else {
                curr = nums2[j++];
            }
        }
        
        if(total % 2 == 1) {
            return curr;
        } else {
            return (prev + curr) / 2.0;
        }
    }
    
    // Optimal - Binary search O(log(min(m,n))) time, O(1) space
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // ensure nums1 is smaller array
        if(nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;
        
        while(left <= right) {
            int partX = (left + right) / 2;
            int partY = (m + n + 1) / 2 - partX;
            
            // edge cases handle karte hai
            int maxLeftX = (partX == 0) ? INT_MIN : nums1[partX - 1];
            int maxLeftY = (partY == 0) ? INT_MIN : nums2[partY - 1];
            
            int minRightX = (partX == m) ? INT_MAX : nums1[partX];
            int minRightY = (partY == n) ? INT_MAX : nums2[partY];
            
            if(maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // correct partition mila
                if((m + n) % 2 == 0) {
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                } else {
                    return max(maxLeftX, maxLeftY);
                }
            }
            else if(maxLeftX > minRightY) {
                right = partX - 1; // partX too big
            }
            else {
                left = partX + 1; // partX too small
            }
        }
        
        return 0.0;
    }
};

// 2. Trapping Rain Water - Array (Hard)
class Solution2_Hard {
public:
    // Brute Force - For each bar find water level O(n²) time, O(1) space
    int trap_bruteforce(vector<int>& height) {
        int n = height.size();
        int water = 0;
        
        // har position ke liye water level calculate karte hai
        for(int i = 0; i < n; i++) {
            int leftMax = 0, rightMax = 0;
            
            // left side ka maximum
            for(int j = 0; j <= i; j++) {
                leftMax = max(leftMax, height[j]);
            }
            
            // right side ka maximum
            for(int j = i; j < n; j++) {
                rightMax = max(rightMax, height[j]);
            }
            
            // water level = min of left and right max
            int waterLevel = min(leftMax, rightMax);
            if(waterLevel > height[i]) {
                water += waterLevel - height[i];
            }
        }
        
        return water;
    }
    
    // Better - Precompute left and right max O(n) time, O(n) space
    int trap_better(vector<int>& height) {
        int n = height.size();
        if(n <= 2) return 0;
        
        vector<int> leftMax(n), rightMax(n);
        
        // left max array build karte hai
        leftMax[0] = height[0];
        for(int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i-1], height[i]);
        }
        
        // right max array build karte hai
        rightMax[n-1] = height[n-1];
        for(int i = n-2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i+1], height[i]);
        }
        
        int water = 0;
        for(int i = 0; i < n; i++) {
            int waterLevel = min(leftMax[i], rightMax[i]);
            if(waterLevel > height[i]) {
                water += waterLevel - height[i];
            }
        }
        
        return water;
    }
    
    // Optimal - Two pointers O(n) time, O(1) space
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while(left < right) {
            if(height[left] < height[right]) {
                if(height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    water += leftMax - height[left];
                }
                left++;
            } else {
                if(height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    water += rightMax - height[right];
                }
                right--;
            }
        }
        
        return water;
    }
};

// 3. Sliding Window Maximum - Array (Hard)
class Solution3_Hard {
public:
    // Brute Force - Check maximum in each window O(n*k) time, O(1) space
    vector<int> maxSlidingWindow_bruteforce(vector<int>& nums, int k) {
        vector<int> result;
        
        for(int i = 0; i <= nums.size() - k; i++) {
            int maxVal = nums[i];
            
            // current window ka maximum find karte hai
            for(int j = i; j < i + k; j++) {
                maxVal = max(maxVal, nums[j]);
            }
            
            result.push_back(maxVal);
        }
        
        return result;
    }
    
    // Better - Using multiset O(n*logk) time, O(k) space
    vector<int> maxSlidingWindow_better(vector<int>& nums, int k) {
        vector<int> result;
        multiset<int> window;
        
        // first window process karte hai
        for(int i = 0; i < k; i++) {
            window.insert(nums[i]);
        }
        result.push_back(*window.rbegin());
        
        // sliding window
        for(int i = k; i < nums.size(); i++) {
            // old element remove karte hai
            window.erase(window.find(nums[i - k]));
            
            // new element add karte hai
            window.insert(nums[i]);
            
            result.push_back(*window.rbegin());
        }
        
        return result;
    }
    
    // Optimal - Deque (monotonic queue) O(n) time, O(k) space
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq; // stores indices in decreasing order of values
        
        for(int i = 0; i < nums.size(); i++) {
            // remove indices outside current window
            while(!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // remove smaller elements from back
            while(!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // agar window size k hogaya hai
            if(i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};

// 4. Largest Rectangle in Histogram - Array (Hard)
class Solution4_Hard {
public:
    // Brute Force - For each bar expand left and right O(n²) time, O(1) space
    int largestRectangleArea_bruteforce(vector<int>& heights) {
        int maxArea = 0;
        int n = heights.size();
        
        for(int i = 0; i < n; i++) {
            int left = i, right = i;
            
            // left side expand karte hai
            while(left >= 0 && heights[left] >= heights[i]) {
                left--;
            }
            
            // right side expand karte hai
            while(right < n && heights[right] >= heights[i]) {
                right++;
            }
            
            int width = right - left - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }
        
        return maxArea;
    }
    
    // Better - Divide and conquer O(nlogn) average, O(n²) worst time
    int largestRectangleArea_better(vector<int>& heights) {
        return divideConquer(heights, 0, heights.size() - 1);
    }
    
    int divideConquer(vector<int>& heights, int left, int right) {
        if(left > right) return 0;
        if(left == right) return heights[left];
        
        // minimum height ka index find karte hai
        int minIndex = left;
        for(int i = left + 1; i <= right; i++) {
            if(heights[i] < heights[minIndex]) {
                minIndex = i;
            }
        }
        
        // current rectangle area
        int currentArea = heights[minIndex] * (right - left + 1);
        
        // left aur right parts ka maximum area
        int leftArea = divideConquer(heights, left, minIndex - 1);
        int rightArea = divideConquer(heights, minIndex + 1, right);
        
        return max({currentArea, leftArea, rightArea});
    }
    
    // Optimal - Stack approach O(n) time, O(n) space
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk; // indices stack
        int maxArea = 0;
        
        for(int i = 0; i <= heights.size(); i++) {
            int currentHeight = (i == heights.size()) ? 0 : heights[i];
            
            while(!stk.empty() && heights[stk.top()] > currentHeight) {
                int h = heights[stk.top()];
                stk.pop();
                
                int width = stk.empty() ? i : (i - stk.top() - 1);
                maxArea = max(maxArea, h * width);
            }
            
            stk.push(i);
        }
        
        return maxArea;
    }
};

// 5. Word Ladder - String (Hard)
class Solution5_Hard {
public:
    // Brute Force - Generate all possible words and BFS O(M²×N) time
    int ladderLength_bruteforce(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if(wordSet.find(endWord) == wordSet.end()) return 0;
        
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        while(!q.empty()) {
            auto [currentWord, level] = q.front();
            q.pop();
            
            if(currentWord == endWord) return level;
            
            // har position pe har character try karte hai
            for(int i = 0; i < currentWord.length(); i++) {
                string original = currentWord;
                
                for(char c = 'a'; c <= 'z'; c++) {
                    if(c == currentWord[i]) continue;
                    
                    currentWord[i] = c;
                    
                    if(wordSet.find(currentWord) != wordSet.end()) {
                        if(currentWord == endWord) return level + 1;
                        
                        q.push({currentWord, level + 1});
                        wordSet.erase(currentWord); // avoid revisiting
                    }
                }
                
                currentWord = original;
            }
        }
        
        return 0;
    }
    
    // Better - Optimized BFS O(M²×N) time, O(M²×N) space
    int ladderLength_better(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if(wordSet.find(endWord) == wordSet.end()) return 0;
        
        queue<string> q;
        q.push(beginWord);
        
        unordered_set<string> visited;
        visited.insert(beginWord);
        
        int level = 1;
        
        while(!q.empty()) {
            int size = q.size();
            
            for(int i = 0; i < size; i++) {
                string currentWord = q.front();
                q.pop();
                
                if(currentWord == endWord) return level;
                
                // generate neighbors
                for(int j = 0; j < currentWord.length(); j++) {
                    char originalChar = currentWord[j];
                    
                    for(char c = 'a'; c <= 'z'; c++) {
                        if(c == originalChar) continue;
                        
                        currentWord[j] = c;
                        
                        if(wordSet.count(currentWord) && !visited.count(currentWord)) {
                            visited.insert(currentWord);
                            q.push(currentWord);
                        }
                    }
                    
                    currentWord[j] = originalChar;
                }
            }
            
            level++;
        }
        
        return 0;
    }
    
    // Optimal - Bidirectional BFS O(M²×N) time, O(M²×N) space
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if(wordSet.find(endWord) == wordSet.end()) return 0;
        
        unordered_set<string> beginSet = {beginWord};
        unordered_set<string> endSet = {endWord};
        unordered_set<string> visited;
        
        int level = 1;
        
        while(!beginSet.empty() && !endSet.empty()) {
            // smaller set se expand karte hai
            if(beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextLevel;
            
            for(string word : beginSet) {
                for(int i = 0; i < word.length(); i++) {
                    char originalChar = word[i];
                    
                    for(char c = 'a'; c <= 'z'; c++) {
                        if(c == originalChar) continue;
                        
                        word[i] = c;
                        
                        if(endSet.count(word)) {
                            return level + 1;
                        }
                        
                        if(wordSet.count(word) && !visited.count(word)) {
                            visited.insert(word);
                            nextLevel.insert(word);
                        }
                    }
                    
                    word[i] = originalChar;
                }
            }
            
            beginSet = nextLevel;
            level++;
        }
        
        return 0;
    }
};