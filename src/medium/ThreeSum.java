/**
 * Problem 4 (Medium): 3Sum
 * Given an integer array nums, return all unique triplets that sum to zero.
 * 
 * Student Notes Style Explanation:
 * We need to find three numbers that add up to 0, like [-1, 0, 1] or [-1, -1, 2]
 * The tricky part is avoiding duplicate triplets while being efficient.
 * This builds on the Two Sum problem but with an extra number!
 */

import java.util.*;

public class ThreeSum {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Check every possible combination of three numbers
     * This is like trying all possible triplets one by one
     * 
     * How it works:
     * - Use three nested loops to check all combinations
     * - For each triplet, check if sum equals zero
     * - Use Set to avoid duplicate triplets
     * 
     * Time Complexity: O(n³) - three nested loops
     * Space Complexity: O(n) - for storing unique triplets in set
     */
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
    
    /**
     * BETTER APPROACH (HashSet with Two Sum)
     * 
     * Idea: For each number, use Two Sum approach to find the other two
     * Better than brute force because we reduce one loop
     * 
     * How it works:
     * - Fix first number, then use Two Sum for remaining two numbers
     * - Use HashSet to find complement quickly
     * - Still need to handle duplicates carefully
     * 
     * Time Complexity: O(n²) - outer loop O(n) × inner Two Sum O(n)
     * Space Complexity: O(n) - HashSet for complements + result set
     */
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
    
    /**
     * OPTIMAL APPROACH (Sort + Two Pointers)
     * 
     * Idea: Sort array first, then use two pointers technique
     * This is the most elegant and efficient solution!
     * 
     * Why it's optimal:
     * - Sorting helps us skip duplicates easily
     * - Two pointers technique is very efficient
     * - No need for extra HashSet
     * - Natural duplicate handling
     * 
     * How it works:
     * - Sort the array first
     * - Fix first element, use two pointers for remaining two
     * - If sum < 0, move left pointer right (increase sum)
     * - If sum > 0, move right pointer left (decrease sum)
     * - Skip duplicates at each step
     * 
     * Time Complexity: O(n²) - O(n log n) sorting + O(n²) two pointers
     * Space Complexity: O(1) - no extra space except output
     */
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
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        ThreeSum solution = new ThreeSum();
        int[][] testCases = {
            {-1, 0, 1, 2, -1, -4},
            {0, 1, 1},
            {0, 0, 0},
            {-2, 0, 1, 1, 2}
        };
        
        for (int[] test : testCases) {
            System.out.println("Array: " + Arrays.toString(test));
            System.out.println("Brute Force: " + solution.threeSumBruteForce(test));
            System.out.println("Better: " + solution.threeSumBetter(test));
            System.out.println("Optimal: " + solution.threeSumOptimal(test));
            System.out.println("---");
        }
    }
}