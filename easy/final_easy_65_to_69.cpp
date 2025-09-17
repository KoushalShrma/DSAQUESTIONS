#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stack>
using namespace std;

// 65. Relative Ranks - Array
class Solution65 {
public:
    // Brute Force - For each athlete find rank O(n²) time, O(n) space
    vector<string> findRelativeRanks_bruteforce(vector<int>& score) {
        int n = score.size();
        vector<string> result(n);
        
        for(int i = 0; i < n; i++) {
            int rank = 1;
            
            // kitne athletes isse better score hai
            for(int j = 0; j < n; j++) {
                if(score[j] > score[i]) {
                    rank++;
                }
            }
            
            // rank ke according string assign karte hai
            if(rank == 1) result[i] = "Gold Medal";
            else if(rank == 2) result[i] = "Silver Medal";
            else if(rank == 3) result[i] = "Bronze Medal";
            else result[i] = to_string(rank);
        }
        
        return result;
    }
    
    // Better - Sort with indices O(nlogn) time, O(n) space
    vector<string> findRelativeRanks_better(vector<int>& score) {
        vector<pair<int, int>> scoreWithIndex;
        
        // score aur index store karte hai
        for(int i = 0; i < score.size(); i++) {
            scoreWithIndex.push_back({score[i], i});
        }
        
        // descending order mein sort karte hai
        sort(scoreWithIndex.begin(), scoreWithIndex.end(), greater<pair<int, int>>());
        
        vector<string> result(score.size());
        
        // ranks assign karte hai
        for(int i = 0; i < scoreWithIndex.size(); i++) {
            int originalIndex = scoreWithIndex[i].second;
            
            if(i == 0) result[originalIndex] = "Gold Medal";
            else if(i == 1) result[originalIndex] = "Silver Medal";
            else if(i == 2) result[originalIndex] = "Bronze Medal";
            else result[originalIndex] = to_string(i + 1);
        }
        
        return result;
    }
    
    // Optimal - Using priority queue concept O(nlogn) time, O(n) space
    vector<string> findRelativeRanks(vector<int>& score) {
        vector<pair<int, int>> athletes; // {score, original_index}
        
        for(int i = 0; i < score.size(); i++) {
            athletes.push_back({score[i], i});
        }
        
        // sort by score in descending order
        sort(athletes.begin(), athletes.end(), 
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.first > b.first;
             });
        
        vector<string> result(score.size());
        string medals[] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        
        for(int i = 0; i < athletes.size(); i++) {
            int index = athletes[i].second;
            
            if(i < 3) {
                result[index] = medals[i];
            } else {
                result[index] = to_string(i + 1);
            }
        }
        
        return result;
    }
};

// 66. Base 7 - Math
class Solution66 {
public:
    // Brute Force - Repeated division with string building O(logn) time, O(logn) space
    string convertToBase7_bruteforce(int num) {
        if(num == 0) return "0";
        
        bool negative = num < 0;
        num = abs(num);
        
        string result = "";
        
        while(num > 0) {
            result = to_string(num % 7) + result;
            num /= 7;
        }
        
        return negative ? "-" + result : result;
    }
    
    // Better - Build string and reverse O(logn) time, O(logn) space
    string convertToBase7_better(int num) {
        if(num == 0) return "0";
        
        bool negative = num < 0;
        num = abs(num);
        
        string result = "";
        
        while(num > 0) {
            result += to_string(num % 7);
            num /= 7;
        }
        
        reverse(result.begin(), result.end());
        return negative ? "-" + result : result;
    }
    
    // Optimal - Recursive approach O(logn) time, O(logn) space
    string convertToBase7(int num) {
        if(num == 0) return "0";
        if(num < 0) return "-" + convertToBase7(-num);
        
        if(num < 7) return to_string(num);
        
        return convertToBase7(num / 7) + to_string(num % 7);
    }
};

// 67. Next Greater Element I - Stack
class Solution67 {
public:
    // Brute Force - For each element in nums1, find in nums2 O(n*m) time, O(1) space
    vector<int> nextGreaterElement_bruteforce(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        
        for(int i = 0; i < nums1.size(); i++) {
            int target = nums1[i];
            int nextGreater = -1;
            bool found = false;
            
            // nums2 mein target find karte hai
            for(int j = 0; j < nums2.size(); j++) {
                if(nums2[j] == target) {
                    found = true;
                    continue;
                }
                
                // target ke baad first greater element
                if(found && nums2[j] > target) {
                    nextGreater = nums2[j];
                    break;
                }
            }
            
            result.push_back(nextGreater);
        }
        
        return result;
    }
    
    // Better - Use hash map for indices O(n*m) time, O(m) space
    vector<int> nextGreaterElement_better(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> indexMap;
        
        // nums2 ke elements ka index map banate hai
        for(int i = 0; i < nums2.size(); i++) {
            indexMap[nums2[i]] = i;
        }
        
        vector<int> result;
        
        for(int num : nums1) {
            int index = indexMap[num];
            int nextGreater = -1;
            
            // index ke baad greater element find karte hai
            for(int i = index + 1; i < nums2.size(); i++) {
                if(nums2[i] > num) {
                    nextGreater = nums2[i];
                    break;
                }
            }
            
            result.push_back(nextGreater);
        }
        
        return result;
    }
    
    // Optimal - Monotonic stack O(n+m) time, O(m) space
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreaterMap;
        stack<int> stk;
        
        // nums2 ke liye next greater elements find karte hai
        for(int i = nums2.size() - 1; i >= 0; i--) {
            // stack se chote elements remove karte hai
            while(!stk.empty() && stk.top() <= nums2[i]) {
                stk.pop();
            }
            
            // next greater element store karte hai
            nextGreaterMap[nums2[i]] = stk.empty() ? -1 : stk.top();
            stk.push(nums2[i]);
        }
        
        vector<int> result;
        for(int num : nums1) {
            result.push_back(nextGreaterMap[num]);
        }
        
        return result;
    }
};

// 68. Keyboard Row - String
class Solution68 {
public:
    // Brute Force - Check each word character by character O(sum of word lengths) time
    vector<string> findWords_bruteforce(vector<string>& words) {
        string row1 = "qwertyuiop";
        string row2 = "asdfghjkl";
        string row3 = "zxcvbnm";
        
        vector<string> result;
        
        for(string word : words) {
            if(word.empty()) continue;
            
            int row = -1;
            bool canType = true;
            
            // first character se row determine karte hai
            char firstChar = tolower(word[0]);
            if(row1.find(firstChar) != string::npos) row = 1;
            else if(row2.find(firstChar) != string::npos) row = 2;
            else if(row3.find(firstChar) != string::npos) row = 3;
            
            // baki characters check karte hai
            for(int i = 1; i < word.length(); i++) {
                char c = tolower(word[i]);
                
                if(row == 1 && row1.find(c) == string::npos) {
                    canType = false;
                    break;
                }
                else if(row == 2 && row2.find(c) == string::npos) {
                    canType = false;
                    break;
                }
                else if(row == 3 && row3.find(c) == string::npos) {
                    canType = false;
                    break;
                }
            }
            
            if(canType) result.push_back(word);
        }
        
        return result;
    }
    
    // Better - Use sets for faster lookup O(sum of word lengths) time
    vector<string> findWords_better(vector<string>& words) {
        unordered_set<char> row1 = {'q','w','e','r','t','y','u','i','o','p'};
        unordered_set<char> row2 = {'a','s','d','f','g','h','j','k','l'};
        unordered_set<char> row3 = {'z','x','c','v','b','n','m'};
        
        vector<string> result;
        
        for(string word : words) {
            if(word.empty()) continue;
            
            char firstChar = tolower(word[0]);
            unordered_set<char>* targetRow = nullptr;
            
            if(row1.count(firstChar)) targetRow = &row1;
            else if(row2.count(firstChar)) targetRow = &row2;
            else if(row3.count(firstChar)) targetRow = &row3;
            
            bool canType = true;
            for(char c : word) {
                if(targetRow->count(tolower(c)) == 0) {
                    canType = false;
                    break;
                }
            }
            
            if(canType) result.push_back(word);
        }
        
        return result;
    }
    
    // Optimal - Character to row mapping O(sum of word lengths) time
    vector<string> findWords(vector<string>& words) {
        vector<int> keyboard(26);
        
        // har character ka row number assign karte hai
        string rows[] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        
        for(int i = 0; i < 3; i++) {
            for(char c : rows[i]) {
                keyboard[c - 'a'] = i;
            }
        }
        
        vector<string> result;
        
        for(string word : words) {
            if(word.empty()) continue;
            
            int row = keyboard[tolower(word[0]) - 'a'];
            bool valid = true;
            
            for(char c : word) {
                if(keyboard[tolower(c) - 'a'] != row) {
                    valid = false;
                    break;
                }
            }
            
            if(valid) result.push_back(word);
        }
        
        return result;
    }
};

// 69. Detect Capital - String
class Solution69 {
public:
    // Brute Force - Check all conditions manually O(n) time, O(1) space
    bool detectCapitalUse_bruteforce(string word) {
        int n = word.length();
        if(n == 0) return true;
        
        // Case 1: All capitals
        bool allCapitals = true;
        for(char c : word) {
            if(c < 'A' || c > 'Z') {
                allCapitals = false;
                break;
            }
        }
        if(allCapitals) return true;
        
        // Case 2: All small
        bool allSmall = true;
        for(char c : word) {
            if(c < 'a' || c > 'z') {
                allSmall = false;
                break;
            }
        }
        if(allSmall) return true;
        
        // Case 3: First capital, rest small
        if(word[0] >= 'A' && word[0] <= 'Z') {
            for(int i = 1; i < n; i++) {
                if(word[i] < 'a' || word[i] > 'z') {
                    return false;
                }
            }
            return true;
        }
        
        return false;
    }
    
    // Better - Count capitals O(n) time, O(1) space
    bool detectCapitalUse_better(string word) {
        int capitals = 0;
        
        for(char c : word) {
            if(c >= 'A' && c <= 'Z') {
                capitals++;
            }
        }
        
        // Valid cases:
        // 1. All capitals
        // 2. No capitals
        // 3. Only first is capital
        return capitals == word.length() || 
               capitals == 0 || 
               (capitals == 1 && word[0] >= 'A' && word[0] <= 'Z');
    }
    
    // Optimal - Single pass validation O(n) time, O(1) space
    bool detectCapitalUse(string word) {
        int n = word.length();
        if(n <= 1) return true;
        
        bool firstIsCapital = (word[0] >= 'A' && word[0] <= 'Z');
        bool secondIsCapital = (word[1] >= 'A' && word[1] <= 'Z');
        
        // Pattern decide karte hai first 2 characters se
        bool shouldAllBeCapital = firstIsCapital && secondIsCapital;
        bool shouldAllBeSmall = !firstIsCapital || !secondIsCapital;
        
        // baki characters validate karte hai
        for(int i = 1; i < n; i++) {
            bool isCapital = (word[i] >= 'A' && word[i] <= 'Z');
            
            if(shouldAllBeCapital && !isCapital) return false;
            if(shouldAllBeSmall && isCapital) return false;
        }
        
        return true;
    }
};