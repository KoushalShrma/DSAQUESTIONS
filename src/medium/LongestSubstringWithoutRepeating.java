/**
 * Problem 1 (Medium): Longest Substring Without Repeating Characters
 * Given a string s, find the length of the longest substring without repeating characters.
 * 
 * Student Notes Style Explanation:
 * We need to find the longest part of the string where no character repeats.
 * Like "abcabcbb" -> "abc" is longest (length 3)
 * This is a classic sliding window problem!
 */

import java.util.*;

public class LongestSubstringWithoutRepeating {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Check every possible substring and see if it has all unique characters
     * This is like manually checking each possible substring one by one
     * 
     * How it works:
     * - Generate all possible substrings
     * - For each substring, check if all characters are unique
     * - Keep track of maximum length found
     * 
     * Time Complexity: O(n³) - O(n²) for substrings × O(n) for uniqueness check
     * Space Complexity: O(min(m,n)) - for the character set used in uniqueness check
     */
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
    
    // Helper method to check if substring has all unique characters
    private boolean allUnique(String s, int start, int end) {
        Set<Character> set = new HashSet<>();
        for (int i = start; i <= end; i++) {
            if (set.contains(s.charAt(i))) {
                return false;
            }
            set.add(s.charAt(i));
        }
        return true;
    }
    
    /**
     * BETTER APPROACH (Sliding Window with Set)
     * 
     * Idea: Use sliding window technique with a set to track characters
     * Much better than brute force as we don't recalculate everything
     * 
     * How it works:
     * - Use two pointers (left and right) to maintain a window
     * - Expand right pointer and add characters to set
     * - When duplicate found, shrink from left until duplicate is removed
     * - Keep track of maximum window size
     * 
     * Time Complexity: O(2n) = O(n) - each character visited at most twice
     * Space Complexity: O(min(m,n)) - set stores unique characters
     */
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
    
    /**
     * OPTIMAL APPROACH (Sliding Window with HashMap)
     * 
     * Idea: Use HashMap to store character and its latest index
     * This allows us to skip characters instead of removing one by one
     * 
     * Why it's optimal:
     * - Each character is visited at most once
     * - When duplicate found, we can jump directly to position after last occurrence
     * - More efficient than gradually shrinking window
     * 
     * How it works:
     * - Use HashMap to store character -> index mapping
     * - When duplicate found, move left pointer to max(current left, last seen index + 1)
     * - This ensures we skip the duplicate character entirely
     * 
     * Time Complexity: O(n) - each character visited exactly once
     * Space Complexity: O(min(m,n)) - HashMap stores character mappings
     */
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
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        LongestSubstringWithoutRepeating solution = new LongestSubstringWithoutRepeating();
        String[] testCases = {"abcabcbb", "bbbbb", "pwwkew", "", "au", "dvdf"};
        
        for (String test : testCases) {
            System.out.println("String: \"" + test + "\"");
            System.out.println("Brute Force: " + solution.lengthOfLongestSubstringBruteForce(test));
            System.out.println("Better: " + solution.lengthOfLongestSubstringBetter(test));
            System.out.println("Optimal: " + solution.lengthOfLongestSubstringOptimal(test));
            System.out.println("---");
        }
    }
}