#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 70. Find the Difference - String
class Solution70 {
public:
    // Brute Force - Character frequency count O(n) time, O(1) space
    char findTheDifference_bruteforce(string s, string t) {
        vector<int> countS(26, 0);
        vector<int> countT(26, 0);
        
        // s ke characters count karte hai
        for(char c : s) {
            countS[c - 'a']++;
        }
        
        // t ke characters count karte hai
        for(char c : t) {
            countT[c - 'a']++;
        }
        
        // difference find karte hai
        for(int i = 0; i < 26; i++) {
            if(countT[i] > countS[i]) {
                return 'a' + i;
            }
        }
        
        return ' '; // should not reach here
    }
    
    // Better - Single pass with map O(n) time, O(1) space
    char findTheDifference_better(string s, string t) {
        unordered_map<char, int> count;
        
        // s ke characters subtract karte hai
        for(char c : s) {
            count[c]--;
        }
        
        // t ke characters add karte hai
        for(char c : t) {
            count[c]++;
            if(count[c] > 0) {
                return c; // extra character mil gaya
            }
        }
        
        return ' ';
    }
    
    // Optimal - XOR approach O(n) time, O(1) space
    char findTheDifference(string s, string t) {
        char result = 0;
        
        // sab characters ka XOR karte hai
        for(char c : s) {
            result ^= c;
        }
        
        for(char c : t) {
            result ^= c;
        }
        
        // duplicate characters cancel ho jayenge, extra character bach jayega
        return result;
    }
};

// 71. Binary Watch - Bit Manipulation
class Solution71 {
public:
    // Brute Force - Check all possible times O(12*60) time, O(1) space
    vector<string> readBinaryWatch_bruteforce(int turnedOn) {
        vector<string> result;
        
        // har possible time check karte hai
        for(int hour = 0; hour < 12; hour++) {
            for(int minute = 0; minute < 60; minute++) {
                int totalBits = countBits(hour) + countBits(minute);
                
                if(totalBits == turnedOn) {
                    string time = to_string(hour) + ":";
                    if(minute < 10) time += "0";
                    time += to_string(minute);
                    result.push_back(time);
                }
            }
        }
        
        return result;
    }
    
    int countBits(int n) {
        int count = 0;
        while(n > 0) {
            count += n & 1;
            n >>= 1;
        }
        return count;
    }
    
    // Better - Optimize bit counting O(12*60) time, O(1) space
    vector<string> readBinaryWatch_better(int turnedOn) {
        vector<string> result;
        
        // precompute bit counts for optimization
        vector<int> hourBits(12), minuteBits(60);
        
        for(int i = 0; i < 12; i++) {
            hourBits[i] = __builtin_popcount(i);
        }
        
        for(int i = 0; i < 60; i++) {
            minuteBits[i] = __builtin_popcount(i);
        }
        
        for(int hour = 0; hour < 12; hour++) {
            for(int minute = 0; minute < 60; minute++) {
                if(hourBits[hour] + minuteBits[minute] == turnedOn) {
                    result.push_back(to_string(hour) + ":" + 
                                   (minute < 10 ? "0" : "") + to_string(minute));
                }
            }
        }
        
        return result;
    }
    
    // Optimal - Direct bit counting O(12*60) time, O(1) space
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;
        
        for(int hour = 0; hour < 12; hour++) {
            for(int minute = 0; minute < 60; minute++) {
                // builtin function use karte hai
                if(__builtin_popcount(hour) + __builtin_popcount(minute) == turnedOn) {
                    result.push_back(to_string(hour) + ":" + 
                                   (minute < 10 ? "0" : "") + to_string(minute));
                }
            }
        }
        
        return result;
    }
};

// 72. Sum of Left Leaves - Tree
class Solution72 {
public:
    // Brute Force - Array representation with explicit tracking
    int sumOfLeftLeaves_bruteforce(vector<int>& tree) {
        if(tree.empty()) return 0;
        
        int sum = 0;
        
        // har node check karte hai
        for(int i = 0; i < tree.size(); i++) {
            if(tree[i] == -1) continue; // null node
            
            int leftChild = 2 * i + 1;
            
            // agar left child exist karta hai
            if(leftChild < tree.size() && tree[leftChild] != -1) {
                // check if it's a leaf
                int leftLeftChild = 2 * leftChild + 1;
                int leftRightChild = 2 * leftChild + 2;
                
                bool isLeaf = (leftLeftChild >= tree.size() || tree[leftLeftChild] == -1) &&
                              (leftRightChild >= tree.size() || tree[leftRightChild] == -1);
                
                if(isLeaf) {
                    sum += tree[leftChild];
                }
            }
        }
        
        return sum;
    }
    
    // Better - DFS approach O(n) time, O(h) space
    int sumOfLeftLeaves_better(vector<int>& tree) {
        return dfsSum(tree, 0, false);
    }
    
    int dfsSum(vector<int>& tree, int index, bool isLeft) {
        if(index >= tree.size() || tree[index] == -1) return 0;
        
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        // check if current node is leaf
        bool isLeaf = (leftChild >= tree.size() || tree[leftChild] == -1) &&
                      (rightChild >= tree.size() || tree[rightChild] == -1);
        
        // agar left leaf hai to add karte hai
        if(isLeaf && isLeft) {
            return tree[index];
        }
        
        // children mein recursive call
        return dfsSum(tree, leftChild, true) + dfsSum(tree, rightChild, false);
    }
    
    // Optimal - Iterative level order O(n) time, O(w) space
    int sumOfLeftLeaves(vector<int>& tree) {
        if(tree.empty()) return 0;
        
        int sum = 0;
        vector<pair<int, bool>> queue; // {index, isLeftChild}
        queue.push_back({0, false});
        
        int front = 0;
        while(front < queue.size()) {
            int index = queue[front].first;
            bool isLeft = queue[front].second;
            front++;
            
            if(index >= tree.size() || tree[index] == -1) continue;
            
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            
            // check if leaf
            bool isLeaf = (leftChild >= tree.size() || tree[leftChild] == -1) &&
                          (rightChild >= tree.size() || tree[rightChild] == -1);
            
            if(isLeaf && isLeft) {
                sum += tree[index];
            }
            
            // children add karte hai
            if(leftChild < tree.size()) {
                queue.push_back({leftChild, true});
            }
            if(rightChild < tree.size()) {
                queue.push_back({rightChild, false});
            }
        }
        
        return sum;
    }
};

// 73. Find All Duplicates in an Array - Array
class Solution73 {
public:
    // Brute Force - Check each element O(n²) time, O(1) space
    vector<int> findDuplicates_bruteforce(vector<int>& nums) {
        vector<int> result;
        
        for(int i = 0; i < nums.size(); i++) {
            int count = 0;
            
            // current element ka count karte hai
            for(int j = 0; j < nums.size(); j++) {
                if(nums[j] == nums[i]) {
                    count++;
                }
            }
            
            // agar exactly 2 times appear karta hai aur pehle se result mein nahi hai
            if(count == 2) {
                bool alreadyExists = false;
                for(int x : result) {
                    if(x == nums[i]) {
                        alreadyExists = true;
                        break;
                    }
                }
                if(!alreadyExists) {
                    result.push_back(nums[i]);
                }
            }
        }
        
        return result;
    }
    
    // Better - Sorting approach O(nlogn) time, O(1) space
    vector<int> findDuplicates_better(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> result;
        
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] == nums[i-1]) {
                // duplicate mila, but avoid adding same duplicate multiple times
                if(result.empty() || result.back() != nums[i]) {
                    result.push_back(nums[i]);
                }
            }
        }
        
        return result;
    }
    
    // Optimal - Mark indices as negative O(n) time, O(1) space
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        
        for(int i = 0; i < nums.size(); i++) {
            int index = abs(nums[i]) - 1; // 1-indexed to 0-indexed
            
            // agar already negative hai to duplicate hai
            if(nums[index] < 0) {
                result.push_back(abs(nums[i]));
            } else {
                // mark as visited
                nums[index] = -nums[index];
            }
        }
        
        return result;
    }
};

// 74. Third Maximum Number - Array
class Solution74 {
public:
    // Brute Force - Sort and find O(nlogn) time, O(1) space
    int thirdMax_bruteforce(vector<int>& nums) {
        // duplicates remove karte hai
        sort(nums.begin(), nums.end());
        vector<int> unique;
        
        for(int i = 0; i < nums.size(); i++) {
            if(i == 0 || nums[i] != nums[i-1]) {
                unique.push_back(nums[i]);
            }
        }
        
        if(unique.size() < 3) {
            return unique.back(); // maximum return karte hai
        }
        
        return unique[unique.size() - 3]; // third maximum
    }
    
    // Better - Set for unique elements O(nlogn) time, O(n) space
    int thirdMax_better(vector<int>& nums) {
        set<int> uniqueNums(nums.begin(), nums.end());
        
        if(uniqueNums.size() < 3) {
            return *uniqueNums.rbegin(); // maximum
        }
        
        auto it = uniqueNums.rbegin();
        advance(it, 2); // third maximum
        return *it;
    }
    
    // Optimal - Track three maximum values O(n) time, O(1) space
    int thirdMax(vector<int>& nums) {
        long long first = LLONG_MIN;  // maximum
        long long second = LLONG_MIN; // second maximum
        long long third = LLONG_MIN;  // third maximum
        
        for(int num : nums) {
            if(num == first || num == second || num == third) {
                continue; // duplicate skip karte hai
            }
            
            if(num > first) {
                third = second;
                second = first;
                first = num;
            }
            else if(num > second) {
                third = second;
                second = num;
            }
            else if(num > third) {
                third = num;
            }
        }
        
        // agar third maximum exist nahi karta
        return (third == LLONG_MIN) ? (int)first : (int)third;
    }
};

// 75. Arranging Coins - Math
class Solution75 {
public:
    // Brute Force - Subtract coins row by row O(√n) time, O(1) space
    int arrangeCoins_bruteforce(int n) {
        int row = 1;
        
        while(n >= row) {
            n -= row;
            row++;
        }
        
        return row - 1; // last complete row
    }
    
    // Better - Use arithmetic series formula O(√n) time, O(1) space
    int arrangeCoins_better(int n) {
        int row = 1;
        long long total = 0;
        
        while(total + row <= n) {
            total += row;
            row++;
        }
        
        return row - 1;
    }
    
    // Optimal - Binary search O(logn) time, O(1) space
    int arrangeCoins(int n) {
        long long left = 1, right = n;
        
        while(left <= right) {
            long long mid = left + (right - left) / 2;
            long long coinsNeeded = mid * (mid + 1) / 2;
            
            if(coinsNeeded == n) {
                return mid;
            }
            else if(coinsNeeded < n) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        
        return right; // largest valid row
    }
};

// 76. Find All Numbers Disappeared in an Array (Different approach) - Array
class Solution76 {
public:
    // Brute Force - Check each number from 1 to n O(n²) time, O(1) space
    vector<int> findDisappearedNumbers_bruteforce(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();
        
        for(int i = 1; i <= n; i++) {
            bool found = false;
            
            for(int j = 0; j < n; j++) {
                if(nums[j] == i) {
                    found = true;
                    break;
                }
            }
            
            if(!found) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Better - Boolean array O(n) time, O(n) space
    vector<int> findDisappearedNumbers_better(vector<int>& nums) {
        int n = nums.size();
        vector<bool> present(n + 1, false);
        
        // mark present numbers
        for(int num : nums) {
            present[num] = true;
        }
        
        vector<int> result;
        for(int i = 1; i <= n; i++) {
            if(!present[i]) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    // Optimal - Cyclic sort approach O(n) time, O(1) space
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        
        // har number ko uski correct position pe place karte hai
        for(int i = 0; i < n; i++) {
            while(nums[i] != i + 1 && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        vector<int> result;
        for(int i = 0; i < n; i++) {
            if(nums[i] != i + 1) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
};

// 77. Assign Cookies - Greedy
class Solution77 {
public:
    // Brute Force - Try all combinations O(n*m) time, O(1) space
    int findContentChildren_bruteforce(vector<int>& g, vector<int>& s) {
        vector<bool> used(s.size(), false);
        int satisfied = 0;
        
        // har child ke liye best cookie find karte hai
        for(int i = 0; i < g.size(); i++) {
            int bestCookie = -1;
            
            for(int j = 0; j < s.size(); j++) {
                if(!used[j] && s[j] >= g[i]) {
                    if(bestCookie == -1 || s[j] < s[bestCookie]) {
                        bestCookie = j;
                    }
                }
            }
            
            if(bestCookie != -1) {
                used[bestCookie] = true;
                satisfied++;
            }
        }
        
        return satisfied;
    }
    
    // Better - Sort and linear scan O(nlogn + mlogm) time, O(1) space
    int findContentChildren_better(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int satisfied = 0;
        vector<bool> used(s.size(), false);
        
        for(int i = 0; i < g.size(); i++) {
            for(int j = 0; j < s.size(); j++) {
                if(!used[j] && s[j] >= g[i]) {
                    used[j] = true;
                    satisfied++;
                    break;
                }
            }
        }
        
        return satisfied;
    }
    
    // Optimal - Two pointers O(nlogn + mlogm) time, O(1) space
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int child = 0, cookie = 0;
        
        while(child < g.size() && cookie < s.size()) {
            // agar current cookie current child ko satisfy kar sakti hai
            if(s[cookie] >= g[child]) {
                child++; // child satisfied
            }
            cookie++; // next cookie try karte hai
        }
        
        return child; // number of satisfied children
    }
};