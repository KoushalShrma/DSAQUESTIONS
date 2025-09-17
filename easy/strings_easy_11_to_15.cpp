#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// 11. Valid Anagram - String
class Solution11 {
public:
    // Brute Force - O(nlogn) time, O(1) space
    bool isAnagram_bruteforce(string s, string t) {
        if(s.length() != t.length()) return false;
        
        // dono strings ko sort karte hai
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        
        // sorted strings compare karte hai
        return s == t;
    }
    
    // Better - Character count array O(n) time, O(1) space  
    bool isAnagram_better(string s, string t) {
        if(s.length() != t.length()) return false;
        
        // 26 letters ke liye count array
        vector<int> count(26, 0);
        
        // s mein characters ka count increase karte hai
        for(char c : s) {
            count[c - 'a']++;
        }
        
        // t mein characters ka count decrease karte hai
        for(char c : t) {
            count[c - 'a']--;
        }
        
        // agar sab zero hai to anagram hai
        for(int i = 0; i < 26; i++) {
            if(count[i] != 0) return false;
        }
        
        return true;
    }
    
    // Optimal - Hash map O(n) time, O(1) space
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) return false;
        
        unordered_map<char, int> charCount;
        
        // s ke characters count karte hai
        for(char c : s) {
            charCount[c]++;
        }
        
        // t ke characters subtract karte hai
        for(char c : t) {
            charCount[c]--;
            // agar count negative ho gaya to not anagram
            if(charCount[c] < 0) return false;
        }
        
        // sab counts zero hone chahiye
        for(auto& pair : charCount) {
            if(pair.second != 0) return false;
        }
        
        return true;
    }
};

// 12. Valid Palindrome - String
class Solution12 {
public:
    // Brute Force - Create clean string O(n) time, O(n) space
    bool isPalindrome_bruteforce(string s) {
        string cleaned = "";
        
        // alphanumeric characters ko lowercase mein convert karte hai
        for(char c : s) {
            if(isalnum(c)) {
                cleaned += tolower(c);
            }
        }
        
        // cleaned string reverse karte hai
        string reversed = cleaned;
        reverse(reversed.begin(), reversed.end());
        
        return cleaned == reversed;
    }
    
    // Better - Compare with reverse O(n) time, O(n) space
    bool isPalindrome_better(string s) {
        string cleaned = "";
        
        for(char c : s) {
            if(isalnum(c)) {
                cleaned += tolower(c);
            }
        }
        
        int n = cleaned.length();
        // half tak check karte hai
        for(int i = 0; i < n/2; i++) {
            if(cleaned[i] != cleaned[n-1-i]) {
                return false;
            }
        }
        
        return true;
    }
    
    // Optimal - Two pointers O(n) time, O(1) space
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        
        while(left < right) {
            // left pointer ko valid character tak move karte hai
            while(left < right && !isalnum(s[left])) {
                left++;
            }
            
            // right pointer ko valid character tak move karte hai  
            while(left < right && !isalnum(s[right])) {
                right--;
            }
            
            // characters compare karte hai (lowercase mein)
            if(tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
};

// 13. First Unique Character in a String - String
class Solution13 {
public:
    // Brute Force - O(n²) time, O(1) space
    int firstUniqChar_bruteforce(string s) {
        int n = s.length();
        
        for(int i = 0; i < n; i++) {
            bool isUnique = true;
            
            // current character ko baaki sab se compare karte hai
            for(int j = 0; j < n; j++) {
                if(i != j && s[i] == s[j]) {
                    isUnique = false;
                    break;
                }
            }
            
            if(isUnique) {
                return i;
            }
        }
        
        return -1;
    }
    
    // Better - Two pass with array O(n) time, O(1) space
    int firstUniqChar_better(string s) {
        // character count array
        vector<int> count(26, 0);
        
        // pehle pass mein count karte hai
        for(char c : s) {
            count[c - 'a']++;
        }
        
        // dusre pass mein first unique find karte hai
        for(int i = 0; i < s.length(); i++) {
            if(count[s[i] - 'a'] == 1) {
                return i;
            }
        }
        
        return -1;
    }
    
    // Optimal - Hash map O(n) time, O(1) space
    int firstUniqChar(string s) {
        unordered_map<char, int> charCount;
        
        // characters ka count karte hai
        for(char c : s) {
            charCount[c]++;
        }
        
        // first unique character find karte hai
        for(int i = 0; i < s.length(); i++) {
            if(charCount[s[i]] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};

// 14. Reverse String - String
class Solution14 {
public:
    // Brute Force - Extra space O(n) time, O(n) space
    void reverseString_bruteforce(vector<char>& s) {
        vector<char> temp = s;
        int n = s.size();
        
        // reverse order mein copy karte hai
        for(int i = 0; i < n; i++) {
            s[i] = temp[n - 1 - i];
        }
    }
    
    // Better - Using built-in reverse O(n) time, O(1) space
    void reverseString_better(vector<char>& s) {
        reverse(s.begin(), s.end());
    }
    
    // Optimal - Two pointers O(n) time, O(1) space
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        
        // dono ends se center ki taraf move karte hai
        while(left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};

// 15. Longest Common Prefix - String
class Solution15 {
public:
    // Brute Force - Compare all strings O(S) time where S is sum of all chars
    string longestCommonPrefix_bruteforce(vector<string>& strs) {
        if(strs.empty()) return "";
        
        string prefix = "";
        int minLen = strs[0].length();
        
        // minimum length find karte hai
        for(string str : strs) {
            minLen = min(minLen, (int)str.length());
        }
        
        // har position pe sab strings check karte hai
        for(int i = 0; i < minLen; i++) {
            char currentChar = strs[0][i];
            
            // sab strings mein same character hai ya nahi
            bool isSame = true;
            for(int j = 1; j < strs.size(); j++) {
                if(strs[j][i] != currentChar) {
                    isSame = false;
                    break;
                }
            }
            
            if(isSame) {
                prefix += currentChar;
            } else {
                break;
            }
        }
        
        return prefix;
    }
    
    // Better - Use first string as reference O(S) time, O(1) space
    string longestCommonPrefix_better(vector<string>& strs) {
        if(strs.empty()) return "";
        
        string prefix = strs[0];
        
        // har string ke saath prefix compare karte hai
        for(int i = 1; i < strs.size(); i++) {
            string currentStr = strs[i];
            int j = 0;
            
            // common prefix find karte hai
            while(j < prefix.length() && j < currentStr.length() && 
                  prefix[j] == currentStr[j]) {
                j++;
            }
            
            // prefix ko update karte hai
            prefix = prefix.substr(0, j);
            
            // agar prefix empty ho gaya to break
            if(prefix.empty()) break;
        }
        
        return prefix;
    }
    
    // Optimal - Vertical scanning O(S) time, O(1) space
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        
        // first string ki length tak check karte hai
        for(int i = 0; i < strs[0].length(); i++) {
            char c = strs[0][i];
            
            // baaki sab strings mein same position pe same char hai ya nahi
            for(int j = 1; j < strs.size(); j++) {
                // agar length kam hai ya character different hai
                if(i >= strs[j].length() || strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }
        
        return strs[0]; // first string hi common prefix hai
    }
};