#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 78. Reverse String II - String
class Solution78 {
public:
    // Brute Force - Process character by character O(n) time, O(n) space
    string reverseStr_bruteforce(string s, int k) {
        string result = s;
        
        for(int i = 0; i < s.length(); i += 2 * k) {
            // first k characters reverse karte hai
            int start = i;
            int end = min(i + k - 1, (int)s.length() - 1);
            
            while(start < end) {
                swap(result[start], result[end]);
                start++;
                end--;
            }
        }
        
        return result;
    }
    
    // Better - In-place reversal O(n) time, O(1) space
    string reverseStr_better(string s, int k) {
        for(int i = 0; i < s.length(); i += 2 * k) {
            int left = i;
            int right = min(i + k - 1, (int)s.length() - 1);
            
            // reverse substring from left to right
            reverse(s.begin() + left, s.begin() + right + 1);
        }
        
        return s;
    }
    
    // Optimal - Manual reversal O(n) time, O(1) space
    string reverseStr(string s, int k) {
        for(int i = 0; i < s.length(); i += 2 * k) {
            int left = i;
            int right = min(i + k - 1, (int)s.length() - 1);
            
            // manual reversal
            while(left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
        }
        
        return s;
    }
};

// 79. Student Attendance Record I - String
class Solution79 {
public:
    // Brute Force - Check all conditions step by step O(n) time, O(1) space
    bool checkRecord_bruteforce(string s) {
        int absentCount = 0;
        int consecutiveLate = 0;
        
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == 'A') {
                absentCount++;
                consecutiveLate = 0; // reset consecutive late count
            }
            else if(s[i] == 'L') {
                consecutiveLate++;
                if(consecutiveLate > 2) {
                    return false; // more than 2 consecutive late
                }
            }
            else { // 'P' - Present
                consecutiveLate = 0; // reset consecutive late count
            }
            
            if(absentCount > 1) {
                return false; // more than 1 absent
            }
        }
        
        return true;
    }
    
    // Better - Single pass with early termination O(n) time, O(1) space
    bool checkRecord_better(string s) {
        int absent = 0;
        
        for(int i = 0; i < s.length(); i++) {
            // check for absent
            if(s[i] == 'A') {
                absent++;
                if(absent > 1) return false;
            }
            
            // check for consecutive late
            if(s[i] == 'L') {
                if(i >= 2 && s[i-1] == 'L' && s[i-2] == 'L') {
                    return false; // 3 consecutive L's
                }
            }
        }
        
        return true;
    }
    
    // Optimal - Pattern matching approach O(n) time, O(1) space
    bool checkRecord(string s) {
        // count A's and check for LLL pattern
        int absentCount = 0;
        
        for(char c : s) {
            if(c == 'A') absentCount++;
        }
        
        if(absentCount > 1) return false;
        
        // check for "LLL" substring
        return s.find("LLL") == string::npos;
    }
};

// 80. Reverse Words in a String III - String
class Solution80 {
public:
    // Brute Force - Split words and reverse each O(n) time, O(n) space
    string reverseWords_bruteforce(string s) {
        vector<string> words;
        string word = "";
        
        // split into words
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
        
        // reverse each word
        for(string& w : words) {
            reverse(w.begin(), w.end());
        }
        
        // join words back
        string result = "";
        for(int i = 0; i < words.size(); i++) {
            if(i > 0) result += " ";
            result += words[i];
        }
        
        return result;
    }
    
    // Better - In-place reversal with two pointers O(n) time, O(1) space
    string reverseWords_better(string s) {
        int start = 0;
        
        for(int i = 0; i <= s.length(); i++) {
            // word boundary mila (space ya end)
            if(i == s.length() || s[i] == ' ') {
                // current word reverse karte hai
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1; // next word ka start
            }
        }
        
        return s;
    }
    
    // Optimal - Manual reversal O(n) time, O(1) space
    string reverseWords(string s) {
        int n = s.length();
        int start = 0;
        
        for(int i = 0; i < n; i++) {
            if(s[i] == ' ') {
                // reverse word from start to i-1
                int left = start, right = i - 1;
                while(left < right) {
                    swap(s[left], s[right]);
                    left++;
                    right--;
                }
                start = i + 1;
            }
        }
        
        // reverse last word
        int left = start, right = n - 1;
        while(left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
        
        return s;
    }
};