#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 11. Rotate Image - Array (Medium)
class Solution11_Medium {
public:
    // Brute Force - Create new matrix O(n²) time, O(n²) space
    void rotate_bruteforce(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> rotated(n, vector<int>(n));
        
        // har element ko rotated position pe copy karte hai
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                rotated[j][n-1-i] = matrix[i][j];
            }
        }
        
        // original matrix mein copy back karte hai
        matrix = rotated;
    }
    
    // Better - Transpose then reverse O(n²) time, O(1) space
    void rotate_better(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // step 1: transpose matrix
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // step 2: reverse each row
        for(int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
    
    // Optimal - Four-way rotation O(n²) time, O(1) space
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // layer by layer rotate karte hai
        for(int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;
            
            // current layer ke elements rotate karte hai
            for(int i = first; i < last; i++) {
                int offset = i - first;
                
                // save top element
                int top = matrix[first][i];
                
                // left -> top
                matrix[first][i] = matrix[last-offset][first];
                
                // bottom -> left
                matrix[last-offset][first] = matrix[last][last-offset];
                
                // right -> bottom
                matrix[last][last-offset] = matrix[i][last];
                
                // top -> right
                matrix[i][last] = top;
            }
        }
    }
};

// 12. Spiral Matrix - Array (Medium)
class Solution12_Medium {
public:
    // Brute Force - Simulate with boundaries O(m*n) time, O(1) space
    vector<int> spiralOrder_bruteforce(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        
        vector<int> result;
        int m = matrix.size(), n = matrix[0].size();
        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        int direction = 0; // 0: right, 1: down, 2: left, 3: up
        
        while(top <= bottom && left <= right) {
            if(direction == 0) { // right
                for(int col = left; col <= right; col++) {
                    result.push_back(matrix[top][col]);
                }
                top++;
            }
            else if(direction == 1) { // down
                for(int row = top; row <= bottom; row++) {
                    result.push_back(matrix[row][right]);
                }
                right--;
            }
            else if(direction == 2) { // left
                for(int col = right; col >= left; col--) {
                    result.push_back(matrix[bottom][col]);
                }
                bottom--;
            }
            else { // up
                for(int row = bottom; row >= top; row--) {
                    result.push_back(matrix[row][left]);
                }
                left++;
            }
            
            direction = (direction + 1) % 4;
        }
        
        return result;
    }
    
    // Better - Layer by layer O(m*n) time, O(1) space
    vector<int> spiralOrder_better(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        
        vector<int> result;
        int m = matrix.size(), n = matrix[0].size();
        
        for(int layer = 0; layer < (min(m, n) + 1) / 2; layer++) {
            // top row
            for(int col = layer; col < n - layer; col++) {
                result.push_back(matrix[layer][col]);
            }
            
            // right column (excluding top corner)
            for(int row = layer + 1; row < m - layer; row++) {
                result.push_back(matrix[row][n - 1 - layer]);
            }
            
            // bottom row (excluding right corner, only if more than one row)
            if(m - 1 - layer > layer) {
                for(int col = n - 2 - layer; col >= layer; col--) {
                    result.push_back(matrix[m - 1 - layer][col]);
                }
            }
            
            // left column (excluding both corners, only if more than one column)
            if(n - 1 - layer > layer) {
                for(int row = m - 2 - layer; row > layer; row--) {
                    result.push_back(matrix[row][layer]);
                }
            }
        }
        
        return result;
    }
    
    // Optimal - Clean boundary approach O(m*n) time, O(1) space
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        
        vector<int> result;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        
        while(top <= bottom && left <= right) {
            // traverse right
            for(int col = left; col <= right; col++) {
                result.push_back(matrix[top][col]);
            }
            top++;
            
            // traverse down
            for(int row = top; row <= bottom; row++) {
                result.push_back(matrix[row][right]);
            }
            right--;
            
            // traverse left (if still valid row)
            if(top <= bottom) {
                for(int col = right; col >= left; col--) {
                    result.push_back(matrix[bottom][col]);
                }
                bottom--;
            }
            
            // traverse up (if still valid column)
            if(left <= right) {
                for(int row = bottom; row >= top; row--) {
                    result.push_back(matrix[row][left]);
                }
                left++;
            }
        }
        
        return result;
    }
};

// 13. Jump Game - Array (Medium)
class Solution13_Medium {
public:
    // Brute Force - Try all possible jumps O(2^n) time, O(n) space
    bool canJump_bruteforce(vector<int>& nums) {
        return canJumpFromIndex(nums, 0);
    }
    
    bool canJumpFromIndex(vector<int>& nums, int index) {
        if(index >= nums.size() - 1) return true;
        
        // current index se maximum jump
        int maxJump = nums[index];
        
        // har possible jump try karte hai
        for(int jump = 1; jump <= maxJump; jump++) {
            if(canJumpFromIndex(nums, index + jump)) {
                return true;
            }
        }
        
        return false;
    }
    
    // Better - Dynamic Programming O(n²) time, O(n) space
    bool canJump_better(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n, false);
        dp[n-1] = true; // last position always reachable
        
        // peeche se aage check karte hai
        for(int i = n - 2; i >= 0; i--) {
            int maxJump = min(i + nums[i], n - 1);
            
            // koi bhi reachable position se end tak ja sakte hai ya nahi
            for(int j = i + 1; j <= maxJump; j++) {
                if(dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[0];
    }
    
    // Optimal - Greedy approach O(n) time, O(1) space
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            // agar current position reachable nahi hai
            if(i > maxReach) return false;
            
            // maximum reachable position update karte hai
            maxReach = max(maxReach, i + nums[i]);
            
            // agar last index reach kar sakte hai
            if(maxReach >= nums.size() - 1) return true;
        }
        
        return maxReach >= nums.size() - 1;
    }
};

// 14. Unique Paths - Array (Medium)
class Solution14_Medium {
public:
    // Brute Force - Recursive approach O(2^(m+n)) time, O(m+n) space
    int uniquePaths_bruteforce(int m, int n) {
        return countPaths(0, 0, m, n);
    }
    
    int countPaths(int row, int col, int m, int n) {
        // boundary check
        if(row >= m || col >= n) return 0;
        
        // destination reached
        if(row == m - 1 && col == n - 1) return 1;
        
        // right aur down move karte hai
        return countPaths(row + 1, col, m, n) + countPaths(row, col + 1, m, n);
    }
    
    // Better - Dynamic Programming O(m*n) time, O(m*n) space
    int uniquePaths_better(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        
        // har cell ke liye paths calculate karte hai
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
    
    // Optimal - Math formula O(min(m,n)) time, O(1) space
    int uniquePaths(int m, int n) {
        // combination formula: C(m+n-2, m-1) ya C(m+n-2, n-1)
        int moves = m + n - 2;
        int choose = min(m - 1, n - 1);
        
        long long result = 1;
        
        // C(moves, choose) calculate karte hai
        for(int i = 0; i < choose; i++) {
            result = result * (moves - i) / (i + 1);
        }
        
        return result;
    }
};

// 15. Minimum Path Sum - Array (Medium)
class Solution15_Medium {
public:
    // Brute Force - Try all paths O(2^(m+n)) time, O(m+n) space
    int minPathSum_bruteforce(vector<vector<int>>& grid) {
        return findMinPath(grid, 0, 0);
    }
    
    int findMinPath(vector<vector<int>>& grid, int row, int col) {
        int m = grid.size(), n = grid[0].size();
        
        // boundary check
        if(row >= m || col >= n) return INT_MAX;
        
        // destination reached
        if(row == m - 1 && col == n - 1) return grid[row][col];
        
        // right aur down move karte hai
        int rightPath = findMinPath(grid, row, col + 1);
        int downPath = findMinPath(grid, row + 1, col);
        
        return grid[row][col] + min(rightPath, downPath);
    }
    
    // Better - Dynamic Programming O(m*n) time, O(m*n) space
    int minPathSum_better(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        
        // initialization
        dp[0][0] = grid[0][0];
        
        // first row
        for(int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        
        // first column
        for(int i = 1; i < m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        
        // fill rest of the table
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        return dp[m-1][n-1];
    }
    
    // Optimal - Space optimized O(m*n) time, O(n) space
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, grid[0][0]);
        
        // first row initialize karte hai
        for(int j = 1; j < n; j++) {
            dp[j] = dp[j-1] + grid[0][j];
        }
        
        // row by row process karte hai
        for(int i = 1; i < m; i++) {
            dp[0] += grid[i][0]; // first column
            
            for(int j = 1; j < n; j++) {
                dp[j] = grid[i][j] + min(dp[j], dp[j-1]);
            }
        }
        
        return dp[n-1];
    }
};