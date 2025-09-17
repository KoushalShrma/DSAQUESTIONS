#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 36. Permutations - Array (Medium)
class Solution36_Medium {
public:
    // Brute Force - Generate all with swapping O(n!) time, O(n!) space
    vector<vector<int>> permute_bruteforce(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current = nums;
        
        // Heap's algorithm simulation
        generatePermutations(current, 0, result);
        return result;
    }
    
    void generatePermutations(vector<int>& nums, int start, vector<vector<int>>& result) {
        if(start == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        for(int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);
            generatePermutations(nums, start + 1, result);
            swap(nums[start], nums[i]); // backtrack
        }
    }
    
    // Better - Using used array O(n!) time, O(n!) space
    vector<vector<int>> permute_better(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        
        backtrack(nums, current, used, result);
        return result;
    }
    
    void backtrack(vector<int>& nums, vector<int>& current, 
                   vector<bool>& used, vector<vector<int>>& result) {
        if(current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for(int i = 0; i < nums.size(); i++) {
            if(!used[i]) {
                used[i] = true;
                current.push_back(nums[i]);
                
                backtrack(nums, current, used, result);
                
                current.pop_back();
                used[i] = false;
            }
        }
    }
    
    // Optimal - In-place swapping O(n!) time, O(n) space
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        backtrackSwap(nums, 0, result);
        return result;
    }
    
    void backtrackSwap(vector<int>& nums, int first, vector<vector<int>>& result) {
        if(first == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        for(int i = first; i < nums.size(); i++) {
            swap(nums[first], nums[i]);
            backtrackSwap(nums, first + 1, result);
            swap(nums[first], nums[i]); // backtrack
        }
    }
};

// 37. Combination Sum - Array (Medium)
class Solution37_Medium {
public:
    // Brute Force - Generate all combinations O(2^(target/min)) time
    vector<vector<int>> combinationSum_bruteforce(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        
        generateCombinations(candidates, target, 0, current, result);
        return result;
    }
    
    void generateCombinations(vector<int>& candidates, int remaining, int start,
                             vector<int>& current, vector<vector<int>>& result) {
        if(remaining == 0) {
            result.push_back(current);
            return;
        }
        
        if(remaining < 0 || start >= candidates.size()) return;
        
        // include current candidate (can use multiple times)
        current.push_back(candidates[start]);
        generateCombinations(candidates, remaining - candidates[start], start, current, result);
        current.pop_back();
        
        // exclude current candidate
        generateCombinations(candidates, remaining, start + 1, current, result);
    }
    
    // Better - Optimized backtracking O(2^(target/min)) time
    vector<vector<int>> combinationSum_better(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        
        sort(candidates.begin(), candidates.end()); // for early termination
        backtrack(candidates, target, 0, current, result);
        return result;
    }
    
    void backtrack(vector<int>& candidates, int remaining, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        if(remaining == 0) {
            result.push_back(current);
            return;
        }
        
        for(int i = start; i < candidates.size(); i++) {
            if(candidates[i] > remaining) break; // early termination
            
            current.push_back(candidates[i]);
            backtrack(candidates, remaining - candidates[i], i, current, result);
            current.pop_back();
        }
    }
    
    // Optimal - Clean backtracking O(2^(target/min)) time, O(target/min) space
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> combination;
        
        function<void(int, int)> dfs = [&](int index, int remaining) {
            if(remaining == 0) {
                result.push_back(combination);
                return;
            }
            
            if(index >= candidates.size() || remaining < 0) return;
            
            // include current element
            combination.push_back(candidates[index]);
            dfs(index, remaining - candidates[index]); // can reuse same element
            combination.pop_back();
            
            // skip current element
            dfs(index + 1, remaining);
        };
        
        dfs(0, target);
        return result;
    }
};

// 38. Subsets - Array (Medium)
class Solution38_Medium {
public:
    // Brute Force - Generate all subsets iteratively O(2^n) time, O(2^n) space
    vector<vector<int>> subsets_bruteforce(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        // 0 se 2^n - 1 tak har number binary representation use karte hai
        for(int mask = 0; mask < (1 << n); mask++) {
            vector<int> subset;
            
            for(int i = 0; i < n; i++) {
                if(mask & (1 << i)) {
                    subset.push_back(nums[i]);
                }
            }
            
            result.push_back(subset);
        }
        
        return result;
    }
    
    // Better - Recursive approach O(2^n) time, O(2^n) space
    vector<vector<int>> subsets_better(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        
        generateSubsets(nums, 0, current, result);
        return result;
    }
    
    void generateSubsets(vector<int>& nums, int index, vector<int>& current,
                        vector<vector<int>>& result) {
        if(index == nums.size()) {
            result.push_back(current);
            return;
        }
        
        // exclude current element
        generateSubsets(nums, index + 1, current, result);
        
        // include current element
        current.push_back(nums[index]);
        generateSubsets(nums, index + 1, current, result);
        current.pop_back();
    }
    
    // Optimal - Iterative building O(2^n) time, O(2^n) space
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result = {{}};
        
        for(int num : nums) {
            int size = result.size();
            
            // existing subsets mein current element add karte hai
            for(int i = 0; i < size; i++) {
                vector<int> newSubset = result[i];
                newSubset.push_back(num);
                result.push_back(newSubset);
            }
        }
        
        return result;
    }
};

// 39. Word Search - String/Array (Medium)
class Solution39_Medium {
public:
    // Brute Force - Try from every cell O(m*n*4^L) time where L is word length
    bool exist_bruteforce(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        
        // har cell se search start karte hai
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(dfsSearch(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool dfsSearch(vector<vector<char>>& board, string& word, int i, int j, int index) {
        if(index == word.length()) return true;
        
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
           board[i][j] != word[index]) {
            return false;
        }
        
        char temp = board[i][j];
        board[i][j] = '#'; // mark as visited
        
        bool found = dfsSearch(board, word, i+1, j, index+1) ||
                     dfsSearch(board, word, i-1, j, index+1) ||
                     dfsSearch(board, word, i, j+1, index+1) ||
                     dfsSearch(board, word, i, j-1, index+1);
        
        board[i][j] = temp; // backtrack
        return found;
    }
    
    // Better - With visited array O(m*n*4^L) time, O(m*n) space
    bool exist_better(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(dfs(board, word, i, j, 0, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int index,
             vector<vector<bool>>& visited) {
        if(index == word.length()) return true;
        
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
           visited[i][j] || board[i][j] != word[index]) {
            return false;
        }
        
        visited[i][j] = true;
        
        bool found = dfs(board, word, i+1, j, index+1, visited) ||
                     dfs(board, word, i-1, j, index+1, visited) ||
                     dfs(board, word, i, j+1, index+1, visited) ||
                     dfs(board, word, i, j-1, index+1, visited);
        
        visited[i][j] = false; // backtrack
        return found;
    }
    
    // Optimal - In-place marking O(m*n*4^L) time, O(L) space
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == word[0] && backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    vector<vector<int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    
    bool backtrack(vector<vector<char>>& board, string& word, int row, int col, int index) {
        if(index == word.length()) return true;
        
        if(row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
           board[row][col] != word[index]) {
            return false;
        }
        
        char temp = board[row][col];
        board[row][col] = '#'; // mark as visited
        
        for(auto& dir : directions) {
            if(backtrack(board, word, row + dir[0], col + dir[1], index + 1)) {
                board[row][col] = temp; // restore
                return true;
            }
        }
        
        board[row][col] = temp; // restore
        return false;
    }
};

// 40. 4Sum - Array (Medium)
class Solution40_Medium {
public:
    // Brute Force - Check all quadruplets O(n⁴) time, O(1) space
    vector<vector<int>> fourSum_bruteforce(vector<int>& nums, int target) {
        set<vector<int>> resultSet;
        int n = nums.size();
        
        for(int i = 0; i < n - 3; i++) {
            for(int j = i + 1; j < n - 2; j++) {
                for(int k = j + 1; k < n - 1; k++) {
                    for(int l = k + 1; l < n; l++) {
                        if((long long)nums[i] + nums[j] + nums[k] + nums[l] == target) {
                            vector<int> quad = {nums[i], nums[j], nums[k], nums[l]};
                            sort(quad.begin(), quad.end());
                            resultSet.insert(quad);
                        }
                    }
                }
            }
        }
        
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
    
    // Better - Hash set for two sum O(n³) time, O(n) space
    vector<vector<int>> fourSum_better(vector<int>& nums, int target) {
        set<vector<int>> resultSet;
        int n = nums.size();
        
        for(int i = 0; i < n - 2; i++) {
            for(int j = i + 1; j < n - 1; j++) {
                unordered_set<long long> seen;
                
                for(int k = j + 1; k < n; k++) {
                    long long complement = (long long)target - nums[i] - nums[j] - nums[k];
                    
                    if(seen.find(complement) != seen.end()) {
                        vector<int> quad = {nums[i], nums[j], (int)complement, nums[k]};
                        sort(quad.begin(), quad.end());
                        resultSet.insert(quad);
                    }
                    
                    seen.insert(nums[k]);
                }
            }
        }
        
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
    
    // Optimal - Two pointers O(n³) time, O(1) space
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        for(int i = 0; i < n - 3; i++) {
            // duplicate skip karte hai
            if(i > 0 && nums[i] == nums[i-1]) continue;
            
            for(int j = i + 1; j < n - 2; j++) {
                // duplicate skip karte hai
                if(j > i + 1 && nums[j] == nums[j-1]) continue;
                
                int left = j + 1, right = n - 1;
                
                while(left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    
                    if(sum == target) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        
                        // duplicate skip karte hai
                        while(left < right && nums[left] == nums[left + 1]) left++;
                        while(left < right && nums[right] == nums[right - 1]) right--;
                        
                        left++;
                        right--;
                    }
                    else if(sum < target) {
                        left++;
                    }
                    else {
                        right--;
                    }
                }
            }
        }
        
        return result;
    }
};