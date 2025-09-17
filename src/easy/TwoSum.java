/**
 * Problem 1: Two Sum
 * Given an array of integers nums and an integer target, return indices of two numbers that add up to target.
 * 
 * Student Notes Style Explanation:
 * This is like finding two numbers in a list that when added together give us our target.
 * It's one of the most fundamental problems in DSA.
 */

import java.util.*;

public class TwoSum {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Check every possible pair of numbers to see if they add up to target
     * This is like manually checking each combination one by one - simple but slow
     * 
     * How it works:
     * - Use two nested loops
     * - For each number, check it with every other number after it
     * - If sum equals target, return their indices
     * 
     * Time Complexity: O(n²) - we check each pair once
     * Space Complexity: O(1) - no extra space needed
     */
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
    
    /**
     * BETTER APPROACH (Two-pass Hash Table)
     * 
     * Idea: Use a HashMap to store numbers we've seen and their indices
     * This is better because we don't need to check the same pairs multiple times
     * 
     * How it works:
     * - First pass: Put all numbers and their indices in a HashMap
     * - Second pass: For each number, check if (target - current number) exists in map
     * 
     * Time Complexity: O(n) - two passes through the array
     * Space Complexity: O(n) - HashMap stores all elements
     */
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
    
    /**
     * OPTIMAL APPROACH (One-pass Hash Table)
     * 
     * Idea: As we iterate through array, check if complement exists in map
     * If not, add current number to map. This is most efficient!
     * 
     * Why it's optimal:
     * - Only one pass through the array
     * - We build the map as we go
     * - Find solution as soon as we encounter the second number
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(n) - HashMap in worst case stores n-1 elements
     */
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
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        TwoSum solution = new TwoSum();
        int[] nums = {2, 7, 11, 15};
        int target = 9;
        
        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("Target: " + target);
        
        System.out.println("Brute Force: " + Arrays.toString(solution.twoSumBruteForce(nums, target)));
        System.out.println("Two Pass: " + Arrays.toString(solution.twoSumTwoPass(nums, target)));
        System.out.println("Optimal: " + Arrays.toString(solution.twoSumOptimal(nums, target)));
    }
}