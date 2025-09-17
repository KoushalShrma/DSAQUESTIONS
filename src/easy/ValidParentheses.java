/**
 * Problem 5: Valid Parentheses
 * Given a string containing just '(', ')', '{', '}', '[' and ']', determine if input is valid.
 * 
 * Student Notes Style Explanation:
 * Think of this like checking if brackets are properly balanced in code.
 * Every opening bracket needs a matching closing bracket in the right order.
 * It's like checking if parentheses in math expressions are correct.
 */

import java.util.*;

public class ValidParentheses {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Keep removing valid pairs until no more pairs can be removed
     * This is like repeatedly finding and removing matching bracket pairs
     * 
     * How it works:
     * - Keep replacing "()", "[]", "{}" with empty string
     * - Repeat until no more replacements possible
     * - If string becomes empty, it was valid
     * 
     * Time Complexity: O(n³) - in worst case, we iterate n times, each time O(n²) for replacement
     * Space Complexity: O(n) - for string operations
     */
    public boolean isValidBruteForce(String s) {
        // Keep removing valid pairs
        while (s.contains("()") || s.contains("[]") || s.contains("{}")) {
            s = s.replace("()", "");
            s = s.replace("[]", "");
            s = s.replace("{}", "");
        }
        
        return s.isEmpty();
    }
    
    /**
     * BETTER APPROACH (Stack with HashMap)
     * 
     * Idea: Use stack but with HashMap for mapping closing to opening brackets
     * This is cleaner than multiple if conditions
     * 
     * How it works:
     * - Use HashMap to map closing brackets to opening ones
     * - Use stack to keep track of opening brackets
     * - For each closing bracket, check if it matches top of stack
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(n) - stack + HashMap
     */
    public boolean isValidBetter(String s) {
        Stack<Character> stack = new Stack<>();
        Map<Character, Character> mapping = new HashMap<>();
        mapping.put(')', '(');
        mapping.put(']', '[');
        mapping.put('}', '{');
        
        for (char c : s.toCharArray()) {
            if (mapping.containsKey(c)) {
                // It's a closing bracket
                char topElement = stack.empty() ? '#' : stack.pop();
                if (topElement != mapping.get(c)) {
                    return false;
                }
            } else {
                // It's an opening bracket
                stack.push(c);
            }
        }
        
        return stack.isEmpty();
    }
    
    /**
     * OPTIMAL APPROACH (Simple Stack)
     * 
     * Idea: Use stack with simple character comparisons
     * Most efficient approach with minimal overhead
     * 
     * Why it's optimal:
     * - Single pass through string
     * - No HashMap overhead
     * - Direct character comparison
     * - Early termination on mismatch
     * 
     * How it works:
     * - Push opening brackets onto stack
     * - For closing brackets, check if they match top of stack
     * - Stack should be empty at the end
     * 
     * Time Complexity: O(n) - single pass
     * Space Complexity: O(n) - stack in worst case (all opening brackets)
     */
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
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        ValidParentheses solution = new ValidParentheses();
        String[] testCases = {"()", "()[]{}", "(]", "([)]", "{[]}", "", "((", "))"};
        
        for (String test : testCases) {
            System.out.println("String: \"" + test + "\"");
            System.out.println("Brute Force: " + solution.isValidBruteForce(test));
            System.out.println("Better: " + solution.isValidBetter(test));
            System.out.println("Optimal: " + solution.isValidOptimal(test));
            System.out.println("---");
        }
    }
}