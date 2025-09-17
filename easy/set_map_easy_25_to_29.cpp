#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// 25. Intersection of Two Arrays - Set
class Solution25 {
public:
    // Brute Force - O(n*m) time, O(min(n,m)) space
    vector<int> intersection_bruteforce(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        
        // nums1 ke har element ko nums2 mein find karte hai
        for(int i = 0; i < nums1.size(); i++) {
            // duplicate check karte hai result mein
            bool alreadyInResult = false;
            for(int res : result) {
                if(res == nums1[i]) {
                    alreadyInResult = true;
                    break;
                }
            }
            
            if(alreadyInResult) continue;
            
            // nums2 mein search karte hai
            for(int j = 0; j < nums2.size(); j++) {
                if(nums1[i] == nums2[j]) {
                    result.push_back(nums1[i]);
                    break;
                }
            }
        }
        
        return result;
    }
    
    // Better - Sort both arrays O(nlogn + mlogm) time, O(1) space
    vector<int> intersection_better(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        vector<int> result;
        int i = 0, j = 0;
        
        // two pointers approach
        while(i < nums1.size() && j < nums2.size()) {
            if(nums1[i] < nums2[j]) {
                i++;
            }
            else if(nums1[i] > nums2[j]) {
                j++;
            }
            else {
                // match mila
                if(result.empty() || result.back() != nums1[i]) {
                    result.push_back(nums1[i]);
                }
                i++;
                j++;
            }
        }
        
        return result;
    }
    
    // Optimal - Using Set O(n+m) time, O(n) space
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> resultSet;
        
        // nums2 ke elements check karte hai
        for(int num : nums2) {
            if(set1.find(num) != set1.end()) {
                resultSet.insert(num);
            }
        }
        
        return vector<int>(resultSet.begin(), resultSet.end());
    }
};

// 26. Intersection of Two Arrays II - Map
class Solution26 {
public:
    // Brute Force - O(n*m) time, O(min(n,m)) space
    vector<int> intersect_bruteforce(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        vector<bool> used(nums2.size(), false);
        
        // nums1 ke har element ke liye nums2 mein find karte hai
        for(int i = 0; i < nums1.size(); i++) {
            for(int j = 0; j < nums2.size(); j++) {
                if(!used[j] && nums1[i] == nums2[j]) {
                    result.push_back(nums1[i]);
                    used[j] = true; // mark as used
                    break;
                }
            }
        }
        
        return result;
    }
    
    // Better - Sort both arrays O(nlogn + mlogm) time, O(1) space
    vector<int> intersect_better(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        vector<int> result;
        int i = 0, j = 0;
        
        while(i < nums1.size() && j < nums2.size()) {
            if(nums1[i] < nums2[j]) {
                i++;
            }
            else if(nums1[i] > nums2[j]) {
                j++;
            }
            else {
                // match mila to dono ko result mein add karte hai
                result.push_back(nums1[i]);
                i++;
                j++;
            }
        }
        
        return result;
    }
    
    // Optimal - Hash Map O(n+m) time, O(min(n,m)) space
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        // chota array ko map banate hai
        if(nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        
        unordered_map<int, int> countMap;
        
        // nums1 ke elements ka count karte hai
        for(int num : nums1) {
            countMap[num]++;
        }
        
        vector<int> result;
        
        // nums2 mein check karte hai
        for(int num : nums2) {
            if(countMap[num] > 0) {
                result.push_back(num);
                countMap[num]--; // count decrease karte hai
            }
        }
        
        return result;
    }
};

// 27. Happy Number - Set
class Solution27 {
public:
    // Helper function to calculate sum of squares of digits
    int getSumOfSquares(int n) {
        int sum = 0;
        while(n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
    
    // Brute Force - Limited iterations O(logn) time, O(1) space
    bool isHappy_bruteforce(int n) {
        // maximum 1000 iterations try karte hai
        for(int i = 0; i < 1000; i++) {
            n = getSumOfSquares(n);
            if(n == 1) return true;
        }
        return false; // probably in cycle
    }
    
    // Better - Floyd's cycle detection O(logn) time, O(1) space
    bool isHappy_better(int n) {
        int slow = n;
        int fast = n;
        
        do {
            slow = getSumOfSquares(slow); // 1 step
            fast = getSumOfSquares(getSumOfSquares(fast)); // 2 steps
        } while(slow != fast);
        
        return slow == 1; // agar 1 pe cycle hai to happy number
    }
    
    // Optimal - Hash Set O(logn) time, O(logn) space
    bool isHappy(int n) {
        unordered_set<int> seen;
        
        while(n != 1 && seen.find(n) == seen.end()) {
            seen.insert(n);
            n = getSumOfSquares(n);
        }
        
        return n == 1;
    }
};

// 28. Isomorphic Strings - Map
class Solution28 {
public:
    // Brute Force - O(n²) time, O(1) space
    bool isIsomorphic_bruteforce(string s, string t) {
        if(s.length() != t.length()) return false;
        
        int n = s.length();
        
        // har character ke liye mapping check karte hai
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                // agar s mein same characters hai
                if(s[i] == s[j]) {
                    // to t mein bhi same hone chahiye
                    if(t[i] != t[j]) return false;
                }
                // agar s mein different hai
                else {
                    // to t mein bhi different hone chahiye
                    if(t[i] == t[j]) return false;
                }
            }
        }
        
        return true;
    }
    
    // Better - Two maps O(n) time, O(1) space
    bool isIsomorphic_better(string s, string t) {
        if(s.length() != t.length()) return false;
        
        unordered_map<char, char> sToT;
        unordered_map<char, char> tToS;
        
        for(int i = 0; i < s.length(); i++) {
            char c1 = s[i], c2 = t[i];
            
            // s se t ki mapping check karte hai
            if(sToT.find(c1) != sToT.end()) {
                if(sToT[c1] != c2) return false;
            } else {
                sToT[c1] = c2;
            }
            
            // t se s ki mapping check karte hai
            if(tToS.find(c2) != tToS.end()) {
                if(tToS[c2] != c1) return false;
            } else {
                tToS[c2] = c1;
            }
        }
        
        return true;
    }
    
    // Optimal - Single pass with arrays O(n) time, O(1) space
    bool isIsomorphic(string s, string t) {
        if(s.length() != t.length()) return false;
        
        // ASCII characters ke liye mapping arrays
        vector<int> sToT(256, -1);
        vector<int> tToS(256, -1);
        
        for(int i = 0; i < s.length(); i++) {
            char c1 = s[i], c2 = t[i];
            
            // mapping check karte hai
            if(sToT[c1] != -1) {
                if(sToT[c1] != c2) return false;
            } else {
                sToT[c1] = c2;
            }
            
            if(tToS[c2] != -1) {
                if(tToS[c2] != c1) return false;
            } else {
                tToS[c2] = c1;
            }
        }
        
        return true;
    }
};

// 29. Word Pattern - Map
class Solution29 {
public:
    // Brute Force - O(n*m) time where m is average word length
    bool wordPattern_bruteforce(string pattern, string s) {
        vector<string> words;
        string word = "";
        
        // string ko words mein split karte hai
        for(char c : s) {
            if(c == ' ') {
                if(!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
            } else {
                word += c;
            }
        }
        if(!word.empty()) words.push_back(word);
        
        if(pattern.length() != words.size()) return false;
        
        // har character ke liye manually mapping check karte hai
        for(int i = 0; i < pattern.length(); i++) {
            for(int j = i + 1; j < pattern.length(); j++) {
                // agar pattern mein same characters hai
                if(pattern[i] == pattern[j]) {
                    // to words mein bhi same hone chahiye
                    if(words[i] != words[j]) return false;
                }
                // agar pattern mein different hai
                else {
                    // to words mein bhi different hone chahiye
                    if(words[i] == words[j]) return false;
                }
            }
        }
        
        return true;
    }
    
    // Better - Using two maps O(n) time, O(n) space
    bool wordPattern_better(string pattern, string s) {
        vector<string> words;
        stringstream ss(s);
        string word;
        
        // words extract karte hai
        while(ss >> word) {
            words.push_back(word);
        }
        
        if(pattern.length() != words.size()) return false;
        
        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;
        
        for(int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            string w = words[i];
            
            // char to word mapping
            if(charToWord.find(c) != charToWord.end()) {
                if(charToWord[c] != w) return false;
            } else {
                charToWord[c] = w;
            }
            
            // word to char mapping
            if(wordToChar.find(w) != wordToChar.end()) {
                if(wordToChar[w] != c) return false;
            } else {
                wordToChar[w] = c;
            }
        }
        
        return true;
    }
    
    // Optimal - Single map with index tracking O(n) time, O(n) space
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        stringstream ss(s);
        string word;
        
        while(ss >> word) {
            words.push_back(word);
        }
        
        if(pattern.length() != words.size()) return false;
        
        unordered_map<char, int> charIndex;
        unordered_map<string, int> wordIndex;
        
        for(int i = 0; i < pattern.length(); i++) {
            char c = pattern[i];
            string w = words[i];
            
            // dono ki last seen index same honi chahiye
            if(charIndex[c] != wordIndex[w]) {
                return false;
            }
            
            // current index store karte hai
            charIndex[c] = i + 1;
            wordIndex[w] = i + 1;
        }
        
        return true;
    }
};