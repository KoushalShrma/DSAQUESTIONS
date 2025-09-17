# Complete DSA Solutions Collection

This document contains all 154 DSA problems with multiple solution approaches.

## Table of Contents
- [Easy Problems (66)](#easy-problems)
- [Medium Problems (78)](#medium-problems)
- [Hard Problems (10)](#hard-problems)

## Easy Problems

### Palindrome Number

**Problem:** Determine whether an integer is a palindrome (reads the same forward and backward).

#### 1. Brute Force

**Explanation:**
Idea: Convert number to string and check if string is palindrome
This is the most obvious approach but uses extra space

How it works:
- Convert integer to string
- Use two pointers from start and end
- Compare characters moving towards center

**Java Code:**
```java
public boolean isPalindromeBruteForce(int x) {
        // Negative numbers are not palindromes
        if (x < 0) return false;
        
        String str = String.valueOf(x);
        int left = 0, right = str.length() - 1;
        
        while (left < right) {
            if (str.charAt(left) != str.charAt(right)) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
```

**Complexity:**
- Time Complexity: O(log n) - where n is the input number (digits in number)
- Space Complexity: O(log n) - string conversion takes space

#### 2. Better Approach

**Explanation:**
Idea: Reverse the entire number and compare with original
Better than string approach as we stay in integer domain

How it works:
- Reverse the entire number mathematically
- Compare reversed number with original
- Handle overflow case

**Java Code:**
```java
public boolean isPalindromeBetter(int x) {
        // Negative numbers and numbers ending with 0 (except 0) are not palindromes
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        int original = x;
        int reversed = 0;
        
        // Reverse the number
        while (x > 0) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }
        
        return original == reversed;
    }
```

**Complexity:**
- Time Complexity: O(log n) - process each digit once
- Space Complexity: O(1) - only using variables

#### 3. Optimal Approach

**Explanation:**
Idea: Only reverse half the digits and compare with remaining half
This is optimal because we do half the work and avoid overflow

Why it's better:
- Only process half the digits
- No risk of integer overflow
- Still O(1) space but more efficient

How it works:
- Keep reversing digits until reversed part >= remaining part
- For even digits: reversed == remaining
- For odd digits: reversed/10 == remaining (middle digit doesn't matter)

**Java Code:**
```java
public boolean isPalindromeOptimal(int x) {
        // Special cases: negative numbers and numbers ending with 0 (except 0)
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        int reversedHalf = 0;
        
        // Continue until we've processed half the digits
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }
        
        // For even number of digits: x == reversedHalf
        // For odd number of digits: x == reversedHalf/10 (ignore middle digit)
        return x == reversedHalf || x == reversedHalf / 10;
    }
```

**Complexity:**
- Time Complexity: O(log n) - but only half the digits
- Space Complexity: O(1) - constant space

---

### Roman to Integer

#### 1. Brute Force

**Explanation:**
Idea: Check every possible Roman numeral pattern and replace them
This is like manually finding and replacing each Roman pattern

How it works:
- Replace all subtractive cases first (IV, IX, XL, etc.)
- Then replace individual characters
- Count total replacements

**Java Code:**
```java
public int romanToIntBruteForce(String s) {
        // Replace subtractive cases first
        s = s.replace("IV", "IIII");  // 4 -> 1+1+1+1
        s = s.replace("IX", "IIIIIIIII");  // 9 -> 1+1+1+1+1+1+1+1+1
        s = s.replace("XL", "XXXX");  // 40 -> 10+10+10+10
        s = s.replace("XC", "XXXXXXXXX");  // 90 -> 10*9
        s = s.replace("CD", "CCCC");  // 400 -> 100*4
        s = s.replace("CM", "CCCCCCCCC");  // 900 -> 100*9
        
        int result = 0;
        for (char c : s.toCharArray()) {
            switch (c) {
                case 'I': result += 1; break;
                case 'V': result += 5; break;
                case 'X': result += 10; break;
                case 'L': result += 50; break;
                case 'C': result += 100; break;
                case 'D': result += 500; break;
                case 'M': result += 1000; break;
            }
        }
        
        return result;
    }
```

**Complexity:**
- Time Complexity: O(n) - multiple passes through string
- Space Complexity: O(n) - string replacements create new strings

#### 2. Better Approach

**Explanation:**
Idea: Use HashMap for values and handle subtraction cases while iterating
Better because we avoid string replacements and process in one pass

How it works:
- Store Roman character values in HashMap
- Iterate through string from left to right
- If current value < next value, subtract current (subtractive case)
- Otherwise add current value

**Java Code:**
```java
public int romanToIntBetter(String s) {
        Map<Character, Integer> romanMap = new HashMap<>();
        romanMap.put('I', 1);
        romanMap.put('V', 5);
        romanMap.put('X', 10);
        romanMap.put('L', 50);
        romanMap.put('C', 100);
        romanMap.put('D', 500);
        romanMap.put('M', 1000);
        
        int result = 0;
        
        for (int i = 0; i < s.length(); i++) {
            int currentValue = romanMap.get(s.charAt(i));
            
            // Check if this is a subtractive case
            if (i + 1 < s.length() && currentValue < romanMap.get(s.charAt(i + 1))) {
                result -= currentValue;  // Subtract for subtractive cases
            } else {
                result += currentValue;  // Add normally
            }
        }
        
        return result;
    }
```

**Complexity:**
- Time Complexity: O(n) - single pass through string
- Space Complexity: O(1) - HashMap has fixed size (7 entries)

#### 3. Optimal Approach

**Explanation:**
Idea: Use switch statement instead of HashMap for better performance
Most efficient as it avoids HashMap overhead and has cleaner logic

Why it's optimal:
- No HashMap lookup overhead
- Switch statement is faster than HashMap for small number of cases
- Same logic but better performance
- More readable code

**Java Code:**
```java
public int romanToIntOptimal(String s) {
        int result = 0;
        
        for (int i = 0; i < s.length(); i++) {
            int currentValue = getValue(s.charAt(i));
            
            // Check if this is a subtractive case
            if (i + 1 < s.length() && currentValue < getValue(s.charAt(i + 1))) {
                result -= currentValue;
            } else {
                result += currentValue;
            }
        }
        
        return result;
    }
```

**Complexity:**
- Time Complexity: O(n) - single pass
- Space Complexity: O(1) - no extra data structures

---

### Two Sum

**Problem:** Given an array of integers nums and an integer target, return indices of two numbers that add up to target.

#### 1. Brute Force

**Explanation:**
Idea: Check every possible pair of numbers to see if they add up to target
This is like manually checking each combination one by one - simple but slow

How it works:
- Use two nested loops
- For each number, check it with every other number after it
- If sum equals target, return their indices

**Java Code:**
```java
public int[] twoSumBruteForce(int[] nums, int target) {
        // Check every possible pair
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                    return new int[]{i, j};
                }
            }
        }
        return new int[]{}; // No solution found
    }
```

**Complexity:**
- Time Complexity: O(n²) - we check each pair once
- Space Complexity: O(1) - no extra space needed

#### 2. Better Approach

**Explanation:**
Idea: Use a HashMap to store numbers we've seen and their indices
This is better because we don't need to check the same pairs multiple times

How it works:
- First pass: Put all numbers and their indices in a HashMap
- Second pass: For each number, check if (target - current number) exists in map

**Java Code:**
```java
public int[] twoSumTwoPass(int[] nums, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        
        // First pass: store all numbers with their indices
        for (int i = 0; i < nums.length; i++) {
            numMap.put(nums[i], i);
        }
        
        // Second pass: find complement
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (numMap.containsKey(complement) && numMap.get(complement) != i) {
                return new int[]{i, numMap.get(complement)};
            }
        }
        
        return new int[]{}; // No solution found
    }
```

**Complexity:**
- Time Complexity: O(n) - two passes through the array
- Space Complexity: O(n) - HashMap stores all elements

#### 3. Optimal Approach

**Explanation:**
Idea: As we iterate through array, check if complement exists in map
If not, add current number to map. This is most efficient!

Why it's optimal:
- Only one pass through the array
- We build the map as we go
- Find solution as soon as we encounter the second number

**Java Code:**
```java
public int[] twoSumOptimal(int[] nums, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in map
            if (numMap.containsKey(complement)) {
                return new int[]{numMap.get(complement), i};
            }
            
            // Add current number to map
            numMap.put(nums[i], i);
        }
        
        return new int[]{}; // No solution found
    }
```

**Complexity:**
- Time Complexity: O(n) - single pass through array
- Space Complexity: O(n) - HashMap in worst case stores n-1 elements

---

### Valid Parentheses

**Problem:** Given a string containing just '(', ')', '{', '}', '[' and ']', determine if input is valid.

#### 1. Brute Force

**Explanation:**
Idea: Keep removing valid pairs until no more pairs can be removed
This is like repeatedly finding and removing matching bracket pairs

How it works:
- Keep replacing "()", "[]", "{}" with empty string
- Repeat until no more replacements possible
- If string becomes empty, it was valid

**Java Code:**
```java
public boolean isValidBruteForce(String s) {
        // Keep removing valid pairs
        while (s.contains("()") || s.contains("[]") || s.contains("{}")) {
            s = s.replace("()", "");
            s = s.replace("[]", "");
            s = s.replace("{}", "");
        }
        
        return s.isEmpty();
    }
```

**Complexity:**
- Time Complexity: O(n³) - in worst case, we iterate n times, each time O(n²) for replacement
- Space Complexity: O(n) - for string operations

#### 2. Better Approach

**Explanation:**
Idea: Use stack but with HashMap for mapping closing to opening brackets
This is cleaner than multiple if conditions

How it works:
- Use HashMap to map closing brackets to opening ones
- Use stack to keep track of opening brackets
- For each closing bracket, check if it matches top of stack

**Java Code:**
```java
public boolean isValidBetter(String s) {
        Stack<Character> stack = new Stack<>();
        Map<Character, Character> mapping = new HashMap<>();
        mapping.put(')', '(');
        mapping.put(']', '[');
        mapping.put('}
```

**Complexity:**
- Time Complexity: O(n) - single pass through string
- Space Complexity: O(n) - stack + HashMap

#### 3. Optimal Approach

**Explanation:**
Idea: Use stack with simple character comparisons
Most efficient approach with minimal overhead

Why it's optimal:
- Single pass through string
- No HashMap overhead
- Direct character comparison
- Early termination on mismatch

How it works:
- Push opening brackets onto stack
- For closing brackets, check if they match top of stack
- Stack should be empty at the end

**Java Code:**
```java
public boolean isValidOptimal(String s) {
        Stack<Character> stack = new Stack<>();
        
        for (char c : s.toCharArray()) {
            // Push opening brackets
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            }
            // Handle closing brackets
            else if (c == ')' || c == ']' || c == '}') {
                if (stack.isEmpty()) {
                    return false; // No matching opening bracket
                }
                
                char top = stack.pop();
                
                // Check if brackets match
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }
            }
        }
        
        return stack.isEmpty(); // All brackets should be matched
    }
```

**Complexity:**
- Time Complexity: O(n) - single pass
- Space Complexity: O(n) - stack in worst case (all opening brackets)

---

## Medium Problems

### Longest Substring Without Repeating Characters

**Problem:** Given a string s, find the length of the longest substring without repeating characters.

#### 1. Brute Force

**Explanation:**
Idea: Check every possible substring and see if it has all unique characters
This is like manually checking each possible substring one by one

How it works:
- Generate all possible substrings
- For each substring, check if all characters are unique
- Keep track of maximum length found

**Java Code:**
```java
public int lengthOfLongestSubstringBruteForce(String s) {
        int n = s.length();
        int maxLength = 0;
        
        // Check all possible substrings
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (allUnique(s, i, j)) {
                    maxLength = Math.max(maxLength, j - i + 1);
                }
            }
        }
        
        return maxLength;
    }
```

**Complexity:**
- Time Complexity: O(n³) - O(n²) for substrings × O(n) for uniqueness check
- Space Complexity: O(min(m,n)) - for the character set used in uniqueness check

#### 2. Better Approach

**Explanation:**
Idea: Use sliding window technique with a set to track characters
Much better than brute force as we don't recalculate everything

How it works:
- Use two pointers (left and right) to maintain a window
- Expand right pointer and add characters to set
- When duplicate found, shrink from left until duplicate is removed
- Keep track of maximum window size

**Java Code:**
```java
public int lengthOfLongestSubstringBetter(String s) {
        int n = s.length();
        Set<Character> set = new HashSet<>();
        int maxLength = 0, left = 0, right = 0;
        
        while (right < n) {
            // If character not in current window, expand window
            if (!set.contains(s.charAt(right))) {
                set.add(s.charAt(right));
                maxLength = Math.max(maxLength, right - left + 1);
                right++;
            } else {
                // Duplicate found, shrink window from left
                set.remove(s.charAt(left));
                left++;
            }
        }
        
        return maxLength;
    }
```

**Complexity:**
- Time Complexity: O(2n) = O(n) - each character visited at most twice
- Space Complexity: O(min(m,n)) - set stores unique characters

#### 3. Optimal Approach

**Explanation:**
Idea: Use HashMap to store character and its latest index
This allows us to skip characters instead of removing one by one

Why it's optimal:
- Each character is visited at most once
- When duplicate found, we can jump directly to position after last occurrence
- More efficient than gradually shrinking window

How it works:
- Use HashMap to store character -> index mapping
- When duplicate found, move left pointer to max(current left, last seen index + 1)
- This ensures we skip the duplicate character entirely

**Java Code:**
```java
public int lengthOfLongestSubstringOptimal(String s) {
        int n = s.length();
        Map<Character, Integer> charIndexMap = new HashMap<>();
        int maxLength = 0;
        int left = 0;
        
        for (int right = 0; right < n; right++) {
            char currentChar = s.charAt(right);
            
            // If character is in current window, move left pointer
            if (charIndexMap.containsKey(currentChar) && 
                charIndexMap.get(currentChar) >= left) {
                left = charIndexMap.get(currentChar) + 1;
            }
            
            // Update character's latest index
            charIndexMap.put(currentChar, right);
            
            // Update maximum length
            maxLength = Math.max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
```

**Complexity:**
- Time Complexity: O(n) - each character visited exactly once
- Space Complexity: O(min(m,n)) - HashMap stores character mappings

---

### 3Sum

**Problem:** Given an integer array nums, return all unique triplets that sum to zero.

#### 1. Brute Force

**Explanation:**
Idea: Check every possible combination of three numbers
This is like trying all possible triplets one by one

How it works:
- Use three nested loops to check all combinations
- For each triplet, check if sum equals zero
- Use Set to avoid duplicate triplets

**Java Code:**
```java
public List<List<Integer>> threeSumBruteForce(int[] nums) {
        Set<List<Integer>> result = new HashSet<>();
        int n = nums.length;
        
        // Check all possible triplets
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        List<Integer> triplet = Arrays.asList(nums[i], nums[j], nums[k]);
                        Collections.sort(triplet);  // Sort to handle duplicates
                        result.add(triplet);
                    }
                }
            }
        }
        
        return new ArrayList<>(result);
    }
```

**Complexity:**
- Time Complexity: O(n³) - three nested loops
- Space Complexity: O(n) - for storing unique triplets in set

#### 2. Better Approach

**Explanation:**
Idea: For each number, use Two Sum approach to find the other two
Better than brute force because we reduce one loop

How it works:
- Fix first number, then use Two Sum for remaining two numbers
- Use HashSet to find complement quickly
- Still need to handle duplicates carefully

**Java Code:**
```java
public List<List<Integer>> threeSumBetter(int[] nums) {
        Set<List<Integer>> result = new HashSet<>();
        int n = nums.length;
        
        for (int i = 0; i < n - 2; i++) {
            Set<Integer> seen = new HashSet<>();
            int target = -nums[i];  // We want nums[j] + nums[k] = target
            
            for (int j = i + 1; j < n; j++) {
                int complement = target - nums[j];
                
                if (seen.contains(complement)) {
                    // Found a triplet
                    List<Integer> triplet = Arrays.asList(nums[i], nums[j], complement);
                    Collections.sort(triplet);
                    result.add(triplet);
                }
                
                seen.add(nums[j]);
            }
        }
        
        return new ArrayList<>(result);
    }
```

**Complexity:**
- Time Complexity: O(n²) - outer loop O(n) × inner Two Sum O(n)
- Space Complexity: O(n) - HashSet for complements + result set

#### 3. Optimal Approach

**Explanation:**
Idea: Sort array first, then use two pointers technique
This is the most elegant and efficient solution!

Why it's optimal:
- Sorting helps us skip duplicates easily
- Two pointers technique is very efficient
- No need for extra HashSet
- Natural duplicate handling

How it works:
- Sort the array first
- Fix first element, use two pointers for remaining two
- If sum < 0, move left pointer right (increase sum)
- If sum > 0, move right pointer left (decrease sum)
- Skip duplicates at each step

**Java Code:**
```java
public List<List<Integer>> threeSumOptimal(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums);  // Sort to enable two pointers technique
        int n = nums.length;
        
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int left = i + 1;
            int right = n - 1;
            int target = -nums[i];  // We want nums[left] + nums[right] = target
            
            while (left < right) {
                int sum = nums[left] + nums[right];
                
                if (sum == target) {
                    // Found a triplet
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    
                    // Skip duplicates for left pointer
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    
                    // Skip duplicates for right pointer
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;  // Need larger sum
                } else {
                    right--;  // Need smaller sum
                }
            }
        }
        
        return result;
    }
```

**Complexity:**
- Time Complexity: O(n²) - O(n log n) sorting + O(n²) two pointers
- Space Complexity: O(1) - no extra space except output

---

## Hard Problems

### Trapping Rain Water

**Problem:** Given n non-negative integers representing elevation map where width of each bar is 1,

#### 1. Brute Force

**Explanation:**
Idea: For each position, find max height on left and right, then calculate water
This is the most straightforward approach - calculate for each bar individually

How it works:
- For each position i, scan left to find max height on left side
- Scan right to find max height on right side
- Water at position i = min(left_max, right_max) - height[i]
- Sum up water at all positions

**Java Code:**
```java
public int trapBruteForce(int[] height) {
        int n = height.length;
        if (n <= 2) return 0;
        
        int totalWater = 0;
        
        // For each position, calculate trapped water
        for (int i = 1; i < n - 1; i++) {
            // Find max height on left
            int leftMax = 0;
            for (int j = 0; j < i; j++) {
                leftMax = Math.max(leftMax, height[j]);
            }
            
            // Find max height on right
            int rightMax = 0;
            for (int j = i + 1; j < n; j++) {
                rightMax = Math.max(rightMax, height[j]);
            }
            
            // Calculate water trapped at current position
            int waterLevel = Math.min(leftMax, rightMax);
            if (waterLevel > height[i]) {
                totalWater += waterLevel - height[i];
            }
        }
        
        return totalWater;
    }
```

**Complexity:**
- Time Complexity: O(n²) - for each element, we scan the entire array
- Space Complexity: O(1) - no extra space used

#### 2. Better Approach

**Explanation:**
Idea: Precompute max heights on left and right for all positions
Better than brute force because we don't recalculate same values

How it works:
- Create leftMax array: leftMax[i] = max height from 0 to i
- Create rightMax array: rightMax[i] = max height from i to n-1
- For each position, water = min(leftMax[i], rightMax[i]) - height[i]

**Java Code:**
```java
public int trapBetter(int[] height) {
        int n = height.length;
        if (n <= 2) return 0;
        
        // Precompute left max for each position
        int[] leftMax = new int[n];
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(leftMax[i - 1], height[i]);
        }
        
        // Precompute right max for each position
        int[] rightMax = new int[n];
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = Math.max(rightMax[i + 1], height[i]);
        }
        
        // Calculate trapped water
        int totalWater = 0;
        for (int i = 0; i < n; i++) {
            int waterLevel = Math.min(leftMax[i], rightMax[i]);
            if (waterLevel > height[i]) {
                totalWater += waterLevel - height[i];
            }
        }
        
        return totalWater;
    }
```

**Complexity:**
- Time Complexity: O(n) - three passes through array
- Space Complexity: O(n) - two additional arrays

#### 3. Optimal Approach

**Explanation:**
Idea: Use two pointers moving from both ends, keeping track of max heights
This is the most elegant solution with optimal time and space complexity

Why it's optimal:
- Single pass through array
- Constant space complexity
- No need to store intermediate results

Key insight:
- Water trapped depends on the smaller of left_max and right_max
- We can process from the side with smaller max height
- If left_max < right_max, we know left side determines water level

How it works:
- Use left and right pointers
- Keep track of left_max and right_max
- Move pointer from side with smaller max height
- Calculate water as we go

**Java Code:**
```java
public int trapOptimal(int[] height) {
        int n = height.length;
        if (n <= 2) return 0;
        
        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int totalWater = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                // Process left side
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    // Water can be trapped
                    totalWater += leftMax - height[left];
                }
                left++;
            } else {
                // Process right side
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    // Water can be trapped
                    totalWater += rightMax - height[right];
                }
                right--;
            }
        }
        
        return totalWater;
    }
```

**Complexity:**
- Time Complexity: O(n) - single pass
- Space Complexity: O(1) - only using variables

---

