#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// 6. Move Zeroes - Array
class Solution6 {
public:
    // Brute Force - O(n²) time, O(1) space
    void moveZeroes_bruteforce(vector<int>& nums) {
        int n = nums.size();
        
        // har zero ko end mein move karte hai
        for(int i = 0; i < n; i++) {
            if(nums[i] == 0) {
                // zero ko end tak shift karte hai
                for(int j = i; j < n-1; j++) {
                    swap(nums[j], nums[j+1]);
                }
            }
        }
    }
    
    // Better - Extra space O(n) time, O(n) space
    void moveZeroes_better(vector<int>& nums) {
        vector<int> result;
        int zeroCount = 0;
        
        // pehle non-zero elements add karte hai
        for(int num : nums) {
            if(num != 0) {
                result.push_back(num);
            } else {
                zeroCount++;
            }
        }
        
        // phir zeros add karte hai
        for(int i = 0; i < zeroCount; i++) {
            result.push_back(0);
        }
        
        nums = result;
    }
    
    // Optimal - Two pointers O(n) time, O(1) space
    void moveZeroes(vector<int>& nums) {
        int left = 0; // non-zero elements ka position
        
        // non-zero elements ko left side move karte hai
        for(int right = 0; right < nums.size(); right++) {
            if(nums[right] != 0) {
                swap(nums[left], nums[right]);
                left++;
            }
        }
    }
};

// 7. Find All Numbers Disappeared in an Array - Array
class Solution7 {
public:
    // Brute Force - O(n²) time, O(1) space
    vector<int> findDisappearedNumbers_bruteforce(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();
        
        // 1 se n tak har number check karte hai
        for(int i = 1; i <= n; i++) {
            bool found = false;
            // array mein ye number hai ya nahi
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
    
    // Better - Hash Set O(n) time, O(n) space
    vector<int> findDisappearedNumbers_better(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        vector<int> result;
        
        // 1 se n tak check karte hai
        for(int i = 1; i <= nums.size(); i++) {
            if(numSet.find(i) == numSet.end()) {
                result.push_back(i);
            }
        }
        return result;
    }
    
    // Optimal - Mark indices as negative O(n) time, O(1) space
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // present numbers ke corresponding indices ko negative mark karte hai
        for(int i = 0; i < nums.size(); i++) {
            int index = abs(nums[i]) - 1; // 1-indexed to 0-indexed
            if(nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }
        
        vector<int> result;
        // positive values ke indices + 1 missing numbers hai
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
};

// 8. Single Number - Array
class Solution8 {
public:
    // Brute Force - O(n²) time, O(1) space
    int singleNumber_bruteforce(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 0; i < n; i++) {
            int count = 0;
            // current number kitni baar appear hota hai
            for(int j = 0; j < n; j++) {
                if(nums[j] == nums[i]) {
                    count++;
                }
            }
            // agar sirf ek baar appear karta hai
            if(count == 1) {
                return nums[i];
            }
        }
        return -1;
    }
    
    // Better - Sorting O(nlogn) time, O(1) space
    int singleNumber_better(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // pairs check karte hai
        for(int i = 0; i < nums.size(); i += 2) {
            // agar last element hai ya current aur next different hai
            if(i == nums.size() - 1 || nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        return -1;
    }
    
    // Optimal - XOR operation O(n) time, O(1) space
    int singleNumber(vector<int>& nums) {
        int result = 0;
        
        // XOR property: a ^ a = 0, a ^ 0 = a
        // sabka XOR karne se duplicate cancel ho jayenge
        for(int num : nums) {
            result ^= num;
        }
        return result;
    }
};

// 9. Plus One - Array
class Solution9 {
public:
    // Brute Force - Convert to number and back O(n) time, O(n) space
    vector<int> plusOne_bruteforce(vector<int>& digits) {
        // Note: This approach fails for large numbers
        // Converting to long long and back to vector
        long long number = 0;
        
        // array se number banate hai
        for(int digit : digits) {
            number = number * 10 + digit;
        }
        number++;
        
        // number se wapas array banate hai
        vector<int> result;
        if(number == 0) {
            result.push_back(0);
        } else {
            while(number > 0) {
                result.insert(result.begin(), number % 10);
                number /= 10;
            }
        }
        return result;
    }
    
    // Better - Handle carry manually O(n) time, O(n) space
    vector<int> plusOne_better(vector<int>& digits) {
        vector<int> result = digits;
        int carry = 1;
        
        // right se left mein carry propagate karte hai
        for(int i = result.size() - 1; i >= 0 && carry > 0; i--) {
            int sum = result[i] + carry;
            result[i] = sum % 10;
            carry = sum / 10;
        }
        
        // agar abhi bhi carry hai to front mein add karte hai
        if(carry > 0) {
            result.insert(result.begin(), carry);
        }
        
        return result;
    }
    
    // Optimal - In-place carry handling O(n) time, O(1) space
    vector<int> plusOne(vector<int>& digits) {
        // last se start karte hai
        for(int i = digits.size() - 1; i >= 0; i--) {
            // agar 9 nahi hai to simply increment karte hai
            if(digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            // agar 9 hai to 0 banate hai aur carry aage
            digits[i] = 0;
        }
        
        // agar yaha tak pahuche to saare digits 9 the
        // to result 1000...0 hoga
        vector<int> result(digits.size() + 1, 0);
        result[0] = 1;
        return result;
    }
};

// 10. Remove Duplicates from Sorted Array - Array
class Solution10 {
public:
    // Brute Force - Extra space O(n) time, O(n) space
    int removeDuplicates_bruteforce(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        vector<int> unique;
        unique.push_back(nums[0]);
        
        // unique elements collect karte hai
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] != nums[i-1]) {
                unique.push_back(nums[i]);
            }
        }
        
        // original array mein copy karte hai
        for(int i = 0; i < unique.size(); i++) {
            nums[i] = unique[i];
        }
        
        return unique.size();
    }
    
    // Better - Two pointers with extra comparisons O(n) time, O(1) space
    int removeDuplicates_better(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int writeIndex = 1;
        
        for(int readIndex = 1; readIndex < nums.size(); readIndex++) {
            bool isDuplicate = false;
            // check if current element is duplicate
            for(int j = 0; j < writeIndex; j++) {
                if(nums[readIndex] == nums[j]) {
                    isDuplicate = true;
                    break;
                }
            }
            
            if(!isDuplicate) {
                nums[writeIndex] = nums[readIndex];
                writeIndex++;
            }
        }
        
        return writeIndex;
    }
    
    // Optimal - Two pointers O(n) time, O(1) space
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int slow = 0; // position for next unique element
        
        // fast pointer array traverse karta hai
        for(int fast = 1; fast < nums.size(); fast++) {
            // agar current element previous se different hai
            if(nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }
        
        return slow + 1; // length of unique elements
    }
};