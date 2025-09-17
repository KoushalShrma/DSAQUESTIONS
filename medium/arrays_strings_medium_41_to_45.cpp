#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stack>
using namespace std;

// 41. Validate Binary Search Tree - Array (Medium)
class Solution41_Medium {
public:
    // Brute Force - Inorder traversal and check O(n) time, O(n) space
    bool isValidBST_bruteforce(vector<int>& tree) {
        if(tree.empty()) return true;
        
        vector<int> inorder;
        inorderTraversal(tree, 0, inorder);
        
        // inorder traversal mein strictly increasing hona chahiye
        for(int i = 1; i < inorder.size(); i++) {
            if(inorder[i] <= inorder[i-1]) {
                return false;
            }
        }
        
        return true;
    }
    
    void inorderTraversal(vector<int>& tree, int index, vector<int>& inorder) {
        if(index >= tree.size() || tree[index] == INT_MIN) return; // INT_MIN represents null
        
        inorderTraversal(tree, 2*index + 1, inorder); // left
        inorder.push_back(tree[index]);
        inorderTraversal(tree, 2*index + 2, inorder); // right
    }
    
    // Better - Range validation O(n) time, O(h) space
    bool isValidBST_better(vector<int>& tree) {
        return validate(tree, 0, LLONG_MIN, LLONG_MAX);
    }
    
    bool validate(vector<int>& tree, int index, long long minVal, long long maxVal) {
        if(index >= tree.size() || tree[index] == INT_MIN) return true;
        
        if(tree[index] <= minVal || tree[index] >= maxVal) {
            return false;
        }
        
        return validate(tree, 2*index + 1, minVal, tree[index]) && // left subtree
               validate(tree, 2*index + 2, tree[index], maxVal);   // right subtree
    }
    
    // Optimal - Inorder with single pass O(n) time, O(h) space
    bool isValidBST(vector<int>& tree) {
        long long prev = LLONG_MIN;
        return inorderCheck(tree, 0, prev);
    }
    
    bool inorderCheck(vector<int>& tree, int index, long long& prev) {
        if(index >= tree.size() || tree[index] == INT_MIN) return true;
        
        // left subtree check
        if(!inorderCheck(tree, 2*index + 1, prev)) return false;
        
        // current node check
        if(tree[index] <= prev) return false;
        prev = tree[index];
        
        // right subtree check
        return inorderCheck(tree, 2*index + 2, prev);
    }
};

// 42. Construct Binary Tree from Preorder and Inorder - Array (Medium)
class Solution42_Medium {
public:
    // Brute Force - Find root in inorder for each call O(n²) time, O(n) space
    vector<int> buildTree_bruteforce(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return {};
        
        // calculate tree size
        int maxSize = 1;
        for(int i = 1; i < preorder.size(); i++) {
            maxSize = maxSize * 2 + 1; // approximate size
        }
        maxSize = min(maxSize, (int)preorder.size() * 4); // reasonable upper bound
        
        vector<int> tree(maxSize, INT_MIN);
        int preIndex = 0;
        
        buildHelper(preorder, inorder, 0, inorder.size() - 1, preIndex, tree, 0);
        
        // trim tree to actual size
        while(!tree.empty() && tree.back() == INT_MIN) {
            tree.pop_back();
        }
        
        return tree;
    }
    
    void buildHelper(vector<int>& preorder, vector<int>& inorder, 
                     int inStart, int inEnd, int& preIndex, 
                     vector<int>& tree, int treeIndex) {
        if(inStart > inEnd || preIndex >= preorder.size() || treeIndex >= tree.size()) return;
        
        int rootVal = preorder[preIndex++];
        tree[treeIndex] = rootVal;
        
        // find root in inorder
        int rootIndex = -1;
        for(int i = inStart; i <= inEnd; i++) {
            if(inorder[i] == rootVal) {
                rootIndex = i;
                break;
            }
        }
        
        if(rootIndex == -1) return;
        
        // build left subtree
        buildHelper(preorder, inorder, inStart, rootIndex - 1, preIndex, tree, 2*treeIndex + 1);
        
        // build right subtree
        buildHelper(preorder, inorder, rootIndex + 1, inEnd, preIndex, tree, 2*treeIndex + 2);
    }
    
    // Better - Use hash map for inorder indices O(n) time, O(n) space
    vector<int> buildTree_better(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return {};
        
        unordered_map<int, int> inorderMap;
        for(int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        vector<int> tree(preorder.size() * 4, INT_MIN);
        int preIndex = 0;
        
        buildOptimal(preorder, inorder, 0, inorder.size() - 1, 
                    preIndex, tree, 0, inorderMap);
        
        // trim tree
        while(!tree.empty() && tree.back() == INT_MIN) {
            tree.pop_back();
        }
        
        return tree;
    }
    
    void buildOptimal(vector<int>& preorder, vector<int>& inorder,
                     int inStart, int inEnd, int& preIndex,
                     vector<int>& tree, int treeIndex,
                     unordered_map<int, int>& inorderMap) {
        if(inStart > inEnd || preIndex >= preorder.size() || treeIndex >= tree.size()) return;
        
        int rootVal = preorder[preIndex++];
        tree[treeIndex] = rootVal;
        
        int rootIndex = inorderMap[rootVal];
        
        // build left subtree
        buildOptimal(preorder, inorder, inStart, rootIndex - 1, 
                    preIndex, tree, 2*treeIndex + 1, inorderMap);
        
        // build right subtree
        buildOptimal(preorder, inorder, rootIndex + 1, inEnd, 
                    preIndex, tree, 2*treeIndex + 2, inorderMap);
    }
    
    // Optimal - Stack-based iterative approach O(n) time, O(n) space
    vector<int> buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return {};
        
        unordered_map<int, int> inMap;
        for(int i = 0; i < inorder.size(); i++) {
            inMap[inorder[i]] = i;
        }
        
        vector<int> tree(preorder.size() * 4, INT_MIN);
        int preIdx = 0;
        
        function<void(int, int, int)> build = [&](int inStart, int inEnd, int treeIdx) {
            if(inStart > inEnd || preIdx >= preorder.size() || treeIdx >= tree.size()) return;
            
            int rootVal = preorder[preIdx++];
            tree[treeIdx] = rootVal;
            
            int inIdx = inMap[rootVal];
            
            if(inStart <= inIdx - 1) {
                build(inStart, inIdx - 1, 2 * treeIdx + 1);
            }
            if(inIdx + 1 <= inEnd) {
                build(inIdx + 1, inEnd, 2 * treeIdx + 2);
            }
        };
        
        build(0, inorder.size() - 1, 0);
        
        // trim trailing INT_MIN values
        while(!tree.empty() && tree.back() == INT_MIN) {
            tree.pop_back();
        }
        
        return tree;
    }
};

// 43. Binary Tree Level Order Traversal - Array (Medium)
class Solution43_Medium {
public:
    // Brute Force - DFS with level tracking O(n) time, O(n) space
    vector<vector<int>> levelOrder_bruteforce(vector<int>& tree) {
        vector<vector<int>> result;
        if(tree.empty()) return result;
        
        dfs(tree, 0, 0, result);
        return result;
    }
    
    void dfs(vector<int>& tree, int index, int level, vector<vector<int>>& result) {
        if(index >= tree.size() || tree[index] == INT_MIN) return;
        
        // ensure result has enough levels
        if(level >= result.size()) {
            result.push_back(vector<int>());
        }
        
        result[level].push_back(tree[index]);
        
        // traverse children
        dfs(tree, 2*index + 1, level + 1, result);
        dfs(tree, 2*index + 2, level + 1, result);
    }
    
    // Better - BFS with queue simulation O(n) time, O(w) space
    vector<vector<int>> levelOrder_better(vector<int>& tree) {
        vector<vector<int>> result;
        if(tree.empty() || tree[0] == INT_MIN) return result;
        
        vector<int> currentLevel = {0}; // indices of current level
        
        while(!currentLevel.empty()) {
            vector<int> levelValues;
            vector<int> nextLevel;
            
            for(int index : currentLevel) {
                if(index < tree.size() && tree[index] != INT_MIN) {
                    levelValues.push_back(tree[index]);
                    
                    // add children to next level
                    int leftChild = 2 * index + 1;
                    int rightChild = 2 * index + 2;
                    
                    if(leftChild < tree.size()) nextLevel.push_back(leftChild);
                    if(rightChild < tree.size()) nextLevel.push_back(rightChild);
                }
            }
            
            if(!levelValues.empty()) {
                result.push_back(levelValues);
            }
            
            currentLevel = nextLevel;
        }
        
        return result;
    }
    
    // Optimal - Level-by-level processing O(n) time, O(w) space
    vector<vector<int>> levelOrder(vector<int>& tree) {
        vector<vector<int>> result;
        if(tree.empty() || tree[0] == INT_MIN) return result;
        
        queue<int> q; // queue of indices
        q.push(0);
        
        while(!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for(int i = 0; i < levelSize; i++) {
                int index = q.front();
                q.pop();
                
                if(index < tree.size() && tree[index] != INT_MIN) {
                    currentLevel.push_back(tree[index]);
                    
                    // add children
                    int left = 2 * index + 1;
                    int right = 2 * index + 2;
                    
                    if(left < tree.size()) q.push(left);
                    if(right < tree.size()) q.push(right);
                }
            }
            
            if(!currentLevel.empty()) {
                result.push_back(currentLevel);
            }
        }
        
        return result;
    }
};

// 44. Longest Consecutive Sequence - Array (Medium)
class Solution44_Medium {
public:
    // Brute Force - Check each number's sequence O(n³) time, O(1) space
    int longestConsecutive_bruteforce(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int maxLength = 1;
        
        for(int num : nums) {
            int currentLength = 1;
            int current = num;
            
            // check forward sequence
            while(find(nums.begin(), nums.end(), current + 1) != nums.end()) {
                current++;
                currentLength++;
            }
            
            maxLength = max(maxLength, currentLength);
        }
        
        return maxLength;
    }
    
    // Better - Sort and check consecutive O(nlogn) time, O(1) space
    int longestConsecutive_better(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        sort(nums.begin(), nums.end());
        
        int maxLength = 1;
        int currentLength = 1;
        
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] == nums[i-1]) {
                continue; // skip duplicates
            }
            else if(nums[i] == nums[i-1] + 1) {
                currentLength++;
            }
            else {
                maxLength = max(maxLength, currentLength);
                currentLength = 1;
            }
        }
        
        maxLength = max(maxLength, currentLength);
        return maxLength;
    }
    
    // Optimal - Hash set O(n) time, O(n) space
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLength = 1;
        
        for(int num : nums) {
            // agar num sequence ka start hai (num-1 exist nahi karta)
            if(numSet.find(num - 1) == numSet.end()) {
                int currentNum = num;
                int currentLength = 1;
                
                // forward direction mein sequence check karte hai
                while(numSet.find(currentNum + 1) != numSet.end()) {
                    currentNum++;
                    currentLength++;
                }
                
                maxLength = max(maxLength, currentLength);
            }
        }
        
        return maxLength;
    }
};

// 45. Palindrome Partitioning - String (Medium)
class Solution45_Medium {
public:
    // Brute Force - Generate all partitions and check O(n*2^n) time
    vector<vector<string>> partition_bruteforce(string s) {
        vector<vector<string>> result;
        vector<string> current;
        
        generatePartitions(s, 0, current, result);
        return result;
    }
    
    void generatePartitions(string s, int start, vector<string>& current, 
                           vector<vector<string>>& result) {
        if(start == s.length()) {
            result.push_back(current);
            return;
        }
        
        for(int end = start; end < s.length(); end++) {
            string substring = s.substr(start, end - start + 1);
            
            if(isPalindrome(substring)) {
                current.push_back(substring);
                generatePartitions(s, end + 1, current, result);
                current.pop_back();
            }
        }
    }
    
    bool isPalindrome(string str) {
        int left = 0, right = str.length() - 1;
        while(left < right) {
            if(str[left] != str[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Better - Precompute palindrome table O(n²) preprocessing, O(n*2^n) time
    vector<vector<string>> partition_better(string s) {
        int n = s.length();
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        
        // precompute palindrome table
        for(int i = 0; i < n; i++) {
            isPalin[i][i] = true; // single characters
        }
        
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if(s[i] == s[j]) {
                    if(len == 2) {
                        isPalin[i][j] = true;
                    } else {
                        isPalin[i][j] = isPalin[i+1][j-1];
                    }
                }
            }
        }
        
        vector<vector<string>> result;
        vector<string> current;
        
        backtrack(s, 0, current, result, isPalin);
        return result;
    }
    
    void backtrack(string s, int start, vector<string>& current,
                   vector<vector<string>>& result, vector<vector<bool>>& isPalin) {
        if(start == s.length()) {
            result.push_back(current);
            return;
        }
        
        for(int end = start; end < s.length(); end++) {
            if(isPalin[start][end]) {
                current.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, current, result, isPalin);
                current.pop_back();
            }
        }
    }
    
    // Optimal - Expand around centers with backtracking O(n*2^n) time, O(n²) space
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));
        
        // expand around centers to find palindromes
        for(int center = 0; center < n; center++) {
            // odd length palindromes
            int left = center, right = center;
            while(left >= 0 && right < n && s[left] == s[right]) {
                palindrome[left][right] = true;
                left--;
                right++;
            }
            
            // even length palindromes
            left = center;
            right = center + 1;
            while(left >= 0 && right < n && s[left] == s[right]) {
                palindrome[left][right] = true;
                left--;
                right++;
            }
        }
        
        vector<vector<string>> result;
        vector<string> path;
        
        function<void(int)> dfs = [&](int index) {
            if(index == n) {
                result.push_back(path);
                return;
            }
            
            for(int j = index; j < n; j++) {
                if(palindrome[index][j]) {
                    path.push_back(s.substr(index, j - index + 1));
                    dfs(j + 1);
                    path.pop_back();
                }
            }
        };
        
        dfs(0);
        return result;
    }
};