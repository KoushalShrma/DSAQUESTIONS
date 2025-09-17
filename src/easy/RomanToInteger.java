/**
 * Problem 3: Roman to Integer
 * Convert Roman numerals to integer value.
 * 
 * Student Notes Style Explanation:
 * Roman numerals use letters like I=1, V=5, X=10, L=50, C=100, D=500, M=1000
 * Key rule: If smaller numeral comes before larger one, subtract it (like IV = 4)
 * Otherwise, just add the values (like VI = 6)
 */

import java.util.*;

public class RomanToInteger {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Check every possible Roman numeral pattern and replace them
     * This is like manually finding and replacing each Roman pattern
     * 
     * How it works:
     * - Replace all subtractive cases first (IV, IX, XL, etc.)
     * - Then replace individual characters
     * - Count total replacements
     * 
     * Time Complexity: O(n) - multiple passes through string
     * Space Complexity: O(n) - string replacements create new strings
     */
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
    
    /**
     * BETTER APPROACH (HashMap with subtraction logic)
     * 
     * Idea: Use HashMap for values and handle subtraction cases while iterating
     * Better because we avoid string replacements and process in one pass
     * 
     * How it works:
     * - Store Roman character values in HashMap
     * - Iterate through string from left to right
     * - If current value < next value, subtract current (subtractive case)
     * - Otherwise add current value
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(1) - HashMap has fixed size (7 entries)
     */
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
    
    /**
     * OPTIMAL APPROACH (Direct character mapping)
     * 
     * Idea: Use switch statement instead of HashMap for better performance
     * Most efficient as it avoids HashMap overhead and has cleaner logic
     * 
     * Why it's optimal:
     * - No HashMap lookup overhead
     * - Switch statement is faster than HashMap for small number of cases
     * - Same logic but better performance
     * - More readable code
     * 
     * Time Complexity: O(n) - single pass
     * Space Complexity: O(1) - no extra data structures
     */
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
    
    // Helper method to get value of Roman character
    private int getValue(char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        RomanToInteger solution = new RomanToInteger();
        String[] testCases = {"III", "LVIII", "MCMXC", "IV", "IX", "XL", "XC", "CD", "CM"};
        
        for (String test : testCases) {
            System.out.println("Roman: " + test);
            System.out.println("Brute Force: " + solution.romanToIntBruteForce(test));
            System.out.println("Better: " + solution.romanToIntBetter(test));
            System.out.println("Optimal: " + solution.romanToIntOptimal(test));
            System.out.println("---");
        }
    }
}