/**
 * Problem 2: Palindrome Number
 * Determine whether an integer is a palindrome (reads the same forward and backward).
 * 
 * Student Notes Style Explanation:
 * A palindrome number is like 121, 1331 - same when read forwards or backwards.
 * We need to check this without converting to string (that would be too easy!)
 */

public class PalindromeNumber {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Convert number to string and check if string is palindrome
     * This is the most obvious approach but uses extra space
     * 
     * How it works:
     * - Convert integer to string
     * - Use two pointers from start and end
     * - Compare characters moving towards center
     * 
     * Time Complexity: O(log n) - where n is the input number (digits in number)
     * Space Complexity: O(log n) - string conversion takes space
     */
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
    
    /**
     * BETTER APPROACH (Reverse entire number)
     * 
     * Idea: Reverse the entire number and compare with original
     * Better than string approach as we stay in integer domain
     * 
     * How it works:
     * - Reverse the entire number mathematically
     * - Compare reversed number with original
     * - Handle overflow case
     * 
     * Time Complexity: O(log n) - process each digit once
     * Space Complexity: O(1) - only using variables
     */
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
    
    /**
     * OPTIMAL APPROACH (Reverse half of the number)
     * 
     * Idea: Only reverse half the digits and compare with remaining half
     * This is optimal because we do half the work and avoid overflow
     * 
     * Why it's better:
     * - Only process half the digits
     * - No risk of integer overflow
     * - Still O(1) space but more efficient
     * 
     * How it works:
     * - Keep reversing digits until reversed part >= remaining part
     * - For even digits: reversed == remaining
     * - For odd digits: reversed/10 == remaining (middle digit doesn't matter)
     * 
     * Time Complexity: O(log n) - but only half the digits
     * Space Complexity: O(1) - constant space
     */
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
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        PalindromeNumber solution = new PalindromeNumber();
        int[] testCases = {121, -121, 10, 1221, 12321, 0};
        
        for (int num : testCases) {
            System.out.println("Number: " + num);
            System.out.println("Brute Force: " + solution.isPalindromeBruteForce(num));
            System.out.println("Better: " + solution.isPalindromeBetter(num));
            System.out.println("Optimal: " + solution.isPalindromeOptimal(num));
            System.out.println("---");
        }
    }
}