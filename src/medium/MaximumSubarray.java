/**
 * Problem 16 (Medium): Maximum Subarray (Kadane's Algorithm)
 * Given an integer array nums, find the contiguous subarray with the largest sum.
 * 
 * Student Notes Style Explanation:
 * We need to find a continuous part of the array that gives maximum sum.
 * Like in [-2,1,-3,4,-1,2,1,-5,4], the answer is [4,-1,2,1] with sum 6.
 * This is THE classic problem for learning Kadane's algorithm!
 */

public class MaximumSubarray {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Check every possible subarray and find the one with maximum sum
     * This is like manually checking all possible continuous parts
     * 
     * How it works:
     * - Use two nested loops to generate all subarrays
     * - For each subarray, calculate its sum
     * - Keep track of maximum sum seen
     * 
     * Time Complexity: O(n³) - O(n²) for subarrays × O(n) for sum calculation
     * Space Complexity: O(1) - only using variables
     */
    public int maxSubArrayBruteForce(int[] nums) {
        int n = nums.length;
        int maxSum = Integer.MIN_VALUE;
        
        // Check all possible subarrays
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                // Calculate sum of subarray from i to j
                int currentSum = 0;
                for (int k = i; k <= j; k++) {
                    currentSum += nums[k];
                }
                maxSum = Math.max(maxSum, currentSum);
            }
        }
        
        return maxSum;
    }
    
    /**
     * BETTER APPROACH (Optimized Brute Force)
     * 
     * Idea: Calculate subarray sums incrementally instead of recalculating
     * Better because we don't recalculate the same sums repeatedly
     * 
     * How it works:
     * - For each starting position i, extend the subarray one element at a time
     * - Add each new element to the running sum
     * - This avoids the inner sum calculation loop
     * 
     * Time Complexity: O(n²) - two nested loops
     * Space Complexity: O(1) - only using variables
     */
    public int maxSubArrayBetter(int[] nums) {
        int n = nums.length;
        int maxSum = Integer.MIN_VALUE;
        
        // Try each starting position
        for (int i = 0; i < n; i++) {
            int currentSum = 0;
            
            // Extend subarray from position i
            for (int j = i; j < n; j++) {
                currentSum += nums[j];
                maxSum = Math.max(maxSum, currentSum);
            }
        }
        
        return maxSum;
    }
    
    /**
     * OPTIMAL APPROACH (Kadane's Algorithm)
     * 
     * Idea: At each position, decide whether to extend previous subarray or start new one
     * This is one of the most elegant algorithms in CS!
     * 
     * Why it's optimal:
     * - Single pass through array
     * - Constant space
     * - Beautiful logic: if current sum becomes negative, start fresh
     * 
     * Key insight:
     * - If sum of subarray ending at i-1 is negative, don't extend it
     * - Better to start a new subarray from current position
     * - Always keep track of maximum sum seen so far
     * 
     * Think of it as: "Should I add this number to my current subarray,
     * or is it better to start a new subarray from here?"
     * 
     * Time Complexity: O(n) - single pass
     * Space Complexity: O(1) - constant space
     */
    public int maxSubArrayOptimal(int[] nums) {
        int maxSoFar = nums[0];    // Maximum sum found so far
        int maxEndingHere = nums[0]; // Maximum sum ending at current position
        
        for (int i = 1; i < nums.length; i++) {
            // Either extend the existing subarray or start new one
            maxEndingHere = Math.max(nums[i], maxEndingHere + nums[i]);
            
            // Update global maximum
            maxSoFar = Math.max(maxSoFar, maxEndingHere);
        }
        
        return maxSoFar;
    }
    
    /**
     * ALTERNATIVE OPTIMAL (Kadane's with clear logic)
     * 
     * Same algorithm but with more explicit logic for learning
     */
    public int maxSubArrayKadaneExplicit(int[] nums) {
        int globalMax = nums[0];
        int currentMax = nums[0];
        
        for (int i = 1; i < nums.length; i++) {
            // If current subarray sum becomes negative, abandon it
            if (currentMax < 0) {
                currentMax = nums[i];  // Start new subarray
            } else {
                currentMax += nums[i]; // Extend current subarray
            }
            
            // Update global maximum
            globalMax = Math.max(globalMax, currentMax);
        }
        
        return globalMax;
    }
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        MaximumSubarray solution = new MaximumSubarray();
        int[][] testCases = {
            {-2, 1, -3, 4, -1, 2, 1, -5, 4},  // Expected: 6 ([4,-1,2,1])
            {1},                               // Expected: 1
            {5, 4, -1, 7, 8},                 // Expected: 23 (whole array)
            {-1},                              // Expected: -1
            {-2, -1, -3},                     // Expected: -1 (least negative)
            {1, 2, 3, 4, 5}                   // Expected: 15 (whole array)
        };
        
        for (int[] nums : testCases) {
            System.out.println("Array: " + java.util.Arrays.toString(nums));
            System.out.println("Brute Force: " + solution.maxSubArrayBruteForce(nums));
            System.out.println("Better: " + solution.maxSubArrayBetter(nums));
            System.out.println("Optimal (Kadane's): " + solution.maxSubArrayOptimal(nums));
            System.out.println("Kadane's Explicit: " + solution.maxSubArrayKadaneExplicit(nums));
            System.out.println("---");
        }
    }
}