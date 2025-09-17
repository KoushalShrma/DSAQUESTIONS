#include <vector>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

// 41. Maximum Depth of Binary Tree - Tree (using array representation)
class Solution41 {
public:
    // Note: LeetCode uses TreeNode structure, but showing array approach for simplicity
    
    // Brute Force - Level by level O(n) time, O(w) space where w is width
    int maxDepth_bruteforce(vector<int>& tree) {
        if(tree.empty() || tree[0] == -1) return 0; // -1 represents null
        
        int depth = 0;
        int level = 0;
        int nodesInLevel = 1;
        int index = 0;
        
        while(index < tree.size()) {
            depth++;
            int nextLevelNodes = 0;
            
            // current level ke sab nodes check karte hai
            for(int i = 0; i < nodesInLevel && index < tree.size(); i++) {
                if(tree[index] != -1) {
                    // left child
                    if(2 * index + 1 < tree.size() && tree[2 * index + 1] != -1) {
                        nextLevelNodes++;
                    }
                    // right child  
                    if(2 * index + 2 < tree.size() && tree[2 * index + 2] != -1) {
                        nextLevelNodes++;
                    }
                }
                index++;
            }
            
            if(nextLevelNodes == 0) break;
            nodesInLevel = nextLevelNodes;
        }
        
        return depth;
    }
    
    // Better - Recursive approach O(n) time, O(h) space
    int maxDepth_better(vector<int>& tree) {
        return helper(tree, 0);
    }
    
    int helper(vector<int>& tree, int index) {
        if(index >= tree.size() || tree[index] == -1) return 0;
        
        int leftDepth = helper(tree, 2 * index + 1);
        int rightDepth = helper(tree, 2 * index + 2);
        
        return 1 + max(leftDepth, rightDepth);
    }
    
    // Optimal - Iterative with queue simulation O(n) time, O(w) space
    int maxDepth(vector<int>& tree) {
        if(tree.empty() || tree[0] == -1) return 0;
        
        vector<int> currentLevel = {0}; // indices of current level
        int depth = 0;
        
        while(!currentLevel.empty()) {
            depth++;
            vector<int> nextLevel;
            
            for(int index : currentLevel) {
                // left child add karte hai
                int leftChild = 2 * index + 1;
                if(leftChild < tree.size() && tree[leftChild] != -1) {
                    nextLevel.push_back(leftChild);
                }
                
                // right child add karte hai
                int rightChild = 2 * index + 2;
                if(rightChild < tree.size() && tree[rightChild] != -1) {
                    nextLevel.push_back(rightChild);
                }
            }
            
            currentLevel = nextLevel;
        }
        
        return depth;
    }
};

// 42. Same Tree - Tree
class Solution42 {
public:
    // Brute Force - Convert to arrays and compare O(n) time, O(n) space
    bool isSameTree_bruteforce(vector<int>& p, vector<int>& q) {
        // arrays ko same length banate hai
        int maxSize = max(p.size(), q.size());
        
        while(p.size() < maxSize) p.push_back(-1);
        while(q.size() < maxSize) q.push_back(-1);
        
        // element by element compare karte hai
        for(int i = 0; i < maxSize; i++) {
            if(p[i] != q[i]) return false;
        }
        
        return true;
    }
    
    // Better - Recursive comparison O(n) time, O(h) space
    bool isSameTree_better(vector<int>& p, vector<int>& q) {
        return compare(p, q, 0, 0);
    }
    
    bool compare(vector<int>& p, vector<int>& q, int i, int j) {
        // dono indices out of bounds
        if(i >= p.size() && j >= q.size()) return true;
        
        // ek out of bounds, dusra nahi
        if(i >= p.size() || j >= q.size()) return false;
        
        // dono null nodes
        if(p[i] == -1 && q[j] == -1) return true;
        
        // ek null, dusra nahi
        if(p[i] == -1 || q[j] == -1) return false;
        
        // values different hai
        if(p[i] != q[j]) return false;
        
        // recursively children check karte hai
        return compare(p, q, 2*i + 1, 2*j + 1) && 
               compare(p, q, 2*i + 2, 2*j + 2);
    }
    
    // Optimal - Level by level comparison O(n) time, O(w) space
    bool isSameTree(vector<int>& p, vector<int>& q) {
        vector<int> level1 = {0}; // indices in p
        vector<int> level2 = {0}; // indices in q
        
        while(!level1.empty() || !level2.empty()) {
            if(level1.size() != level2.size()) return false;
            
            vector<int> nextLevel1, nextLevel2;
            
            for(int i = 0; i < level1.size(); i++) {
                int idx1 = level1[i];
                int idx2 = level2[i];
                
                // current nodes ka value check karte hai
                int val1 = (idx1 < p.size()) ? p[idx1] : -1;
                int val2 = (idx2 < q.size()) ? q[idx2] : -1;
                
                if(val1 != val2) return false;
                
                if(val1 != -1) { // agar node null nahi hai
                    // children add karte hai
                    nextLevel1.push_back(2 * idx1 + 1);
                    nextLevel1.push_back(2 * idx1 + 2);
                    nextLevel2.push_back(2 * idx2 + 1);
                    nextLevel2.push_back(2 * idx2 + 2);
                }
            }
            
            level1 = nextLevel1;
            level2 = nextLevel2;
        }
        
        return true;
    }
};

// 43. Invert Binary Tree - Tree
class Solution43 {
public:
    // Brute Force - Create new tree O(n) time, O(n) space
    vector<int> invertTree_bruteforce(vector<int>& root) {
        if(root.empty()) return {};
        
        vector<int> inverted(root.size(), -1);
        
        // har node ke children swap karte hai
        for(int i = 0; i < root.size(); i++) {
            if(root[i] != -1) {
                inverted[i] = root[i];
                
                int leftChild = 2 * i + 1;
                int rightChild = 2 * i + 2;
                
                // children swap karte hai
                if(leftChild < root.size()) {
                    int newRightPos = 2 * i + 2;
                    if(newRightPos < inverted.size()) {
                        inverted[newRightPos] = (leftChild < root.size()) ? root[leftChild] : -1;
                    }
                }
                
                if(rightChild < root.size()) {
                    int newLeftPos = 2 * i + 1;
                    if(newLeftPos < inverted.size()) {
                        inverted[newLeftPos] = (rightChild < root.size()) ? root[rightChild] : -1;
                    }
                }
            }
        }
        
        return inverted;
    }
    
    // Better - Recursive inversion O(n) time, O(h) space
    vector<int> invertTree_better(vector<int>& root) {
        vector<int> result = root;
        invertHelper(result, 0);
        return result;
    }
    
    void invertHelper(vector<int>& tree, int index) {
        if(index >= tree.size() || tree[index] == -1) return;
        
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        // children exist karte hai
        if(leftChild < tree.size() && rightChild < tree.size()) {
            swap(tree[leftChild], tree[rightChild]);
        }
        
        // recursively children invert karte hai
        invertHelper(tree, leftChild);
        invertHelper(tree, rightChild);
    }
    
    // Optimal - Iterative level-by-level O(n) time, O(w) space
    vector<int> invertTree(vector<int>& root) {
        if(root.empty()) return {};
        
        vector<int> result = root;
        vector<int> currentLevel = {0};
        
        while(!currentLevel.empty()) {
            vector<int> nextLevel;
            
            for(int index : currentLevel) {
                if(index < result.size() && result[index] != -1) {
                    int leftChild = 2 * index + 1;
                    int rightChild = 2 * index + 2;
                    
                    // children swap karte hai
                    if(leftChild < result.size() && rightChild < result.size()) {
                        swap(result[leftChild], result[rightChild]);
                    }
                    
                    // next level mein add karte hai
                    if(leftChild < result.size()) nextLevel.push_back(leftChild);
                    if(rightChild < result.size()) nextLevel.push_back(rightChild);
                }
            }
            
            currentLevel = nextLevel;
        }
        
        return result;
    }
};

// 44. Symmetric Tree - Tree
class Solution44 {
public:
    // Brute Force - Create mirror and compare O(n) time, O(n) space
    bool isSymmetric_bruteforce(vector<int>& root) {
        if(root.empty()) return true;
        
        vector<int> mirrored = invertTree(root);
        
        // original aur mirrored compare karte hai
        return isSame(root, mirrored);
    }
    
    vector<int> invertTree(vector<int>& tree) {
        vector<int> result = tree;
        for(int i = 0; i < result.size(); i++) {
            if(result[i] != -1) {
                int leftChild = 2 * i + 1;
                int rightChild = 2 * i + 2;
                
                if(leftChild < result.size() && rightChild < result.size()) {
                    swap(result[leftChild], result[rightChild]);
                }
            }
        }
        return result;
    }
    
    bool isSame(vector<int>& tree1, vector<int>& tree2) {
        if(tree1.size() != tree2.size()) return false;
        
        for(int i = 0; i < tree1.size(); i++) {
            if(tree1[i] != tree2[i]) return false;
        }
        return true;
    }
    
    // Better - Check left and right subtrees O(n) time, O(h) space
    bool isSymmetric_better(vector<int>& root) {
        if(root.empty()) return true;
        
        return isMirror(root, 1, 2); // left subtree root, right subtree root
    }
    
    bool isMirror(vector<int>& tree, int left, int right) {
        // dono indices out of bounds
        if(left >= tree.size() && right >= tree.size()) return true;
        
        // ek out of bounds
        if(left >= tree.size() || right >= tree.size()) return false;
        
        // dono null
        if(tree[left] == -1 && tree[right] == -1) return true;
        
        // ek null
        if(tree[left] == -1 || tree[right] == -1) return false;
        
        // values same nahi hai
        if(tree[left] != tree[right]) return false;
        
        // cross comparison karte hai
        return isMirror(tree, 2*left + 1, 2*right + 2) && 
               isMirror(tree, 2*left + 2, 2*right + 1);
    }
    
    // Optimal - Level-by-level symmetric check O(n) time, O(w) space
    bool isSymmetric(vector<int>& root) {
        if(root.empty()) return true;
        
        vector<pair<int, int>> currentLevel = {{1, 2}}; // (left, right) indices
        
        while(!currentLevel.empty()) {
            vector<pair<int, int>> nextLevel;
            
            for(auto& pair : currentLevel) {
                int left = pair.first;
                int right = pair.second;
                
                int leftVal = (left < root.size()) ? root[left] : -1;
                int rightVal = (right < root.size()) ? root[right] : -1;
                
                if(leftVal != rightVal) return false;
                
                if(leftVal != -1) { // dono non-null hai
                    // cross pairs add karte hai
                    nextLevel.push_back({2*left + 1, 2*right + 2});
                    nextLevel.push_back({2*left + 2, 2*right + 1});
                }
            }
            
            currentLevel = nextLevel;
        }
        
        return true;
    }
};

// 45. Path Sum - Tree
class Solution45 {
public:
    // Brute Force - Check all paths O(n²) time, O(h) space
    bool hasPathSum_bruteforce(vector<int>& root, int targetSum) {
        if(root.empty() || root[0] == -1) return false;
        
        vector<vector<int>> allPaths;
        vector<int> currentPath;
        
        // sab paths find karte hai
        findAllPaths(root, 0, currentPath, allPaths);
        
        // har path ka sum check karte hai
        for(auto& path : allPaths) {
            int sum = 0;
            for(int val : path) {
                sum += val;
            }
            if(sum == targetSum) return true;
        }
        
        return false;
    }
    
    void findAllPaths(vector<int>& tree, int index, vector<int>& path, 
                      vector<vector<int>>& allPaths) {
        if(index >= tree.size() || tree[index] == -1) return;
        
        path.push_back(tree[index]);
        
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        // agar leaf node hai
        bool isLeaf = (leftChild >= tree.size() || tree[leftChild] == -1) &&
                      (rightChild >= tree.size() || tree[rightChild] == -1);
        
        if(isLeaf) {
            allPaths.push_back(path);
        } else {
            findAllPaths(tree, leftChild, path, allPaths);
            findAllPaths(tree, rightChild, path, allPaths);
        }
        
        path.pop_back();
    }
    
    // Better - DFS with early termination O(n) time, O(h) space
    bool hasPathSum_better(vector<int>& root, int targetSum) {
        if(root.empty() || root[0] == -1) return false;
        
        return dfs(root, 0, 0, targetSum);
    }
    
    bool dfs(vector<int>& tree, int index, int currentSum, int targetSum) {
        if(index >= tree.size() || tree[index] == -1) return false;
        
        currentSum += tree[index];
        
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        // leaf node check karte hai
        bool isLeaf = (leftChild >= tree.size() || tree[leftChild] == -1) &&
                      (rightChild >= tree.size() || tree[rightChild] == -1);
        
        if(isLeaf) {
            return currentSum == targetSum;
        }
        
        // children mein search karte hai
        return dfs(tree, leftChild, currentSum, targetSum) ||
               dfs(tree, rightChild, currentSum, targetSum);
    }
    
    // Optimal - DFS with remaining sum O(n) time, O(h) space
    bool hasPathSum(vector<int>& root, int targetSum) {
        if(root.empty() || root[0] == -1) return false;
        
        return hasPathSumHelper(root, 0, targetSum);
    }
    
    bool hasPathSumHelper(vector<int>& tree, int index, int remainingSum) {
        if(index >= tree.size() || tree[index] == -1) return false;
        
        remainingSum -= tree[index];
        
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        // leaf node hai
        if((leftChild >= tree.size() || tree[leftChild] == -1) &&
           (rightChild >= tree.size() || tree[rightChild] == -1)) {
            return remainingSum == 0;
        }
        
        // children check karte hai
        return hasPathSumHelper(tree, leftChild, remainingSum) ||
               hasPathSumHelper(tree, rightChild, remainingSum);
    }
};