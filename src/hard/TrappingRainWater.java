/**
 * Problem 4 (Hard): Trapping Rain Water
 * Given n non-negative integers representing elevation map where width of each bar is 1,
 * compute how much water it can trap after raining.
 * 
 * Student Notes Style Explanation:
 * Imagine you have bars of different heights and it rains.
 * Water gets trapped between the bars. We need to calculate total trapped water.
 * Key insight: Water level at any position = min(max_left, max_right) - current_height
 */

import java.util.*;

public class TrappingRainWater {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: For each position, find max height on left and right, then calculate water
     * This is the most straightforward approach - calculate for each bar individually
     * 
     * How it works:
     * - For each position i, scan left to find max height on left side
     * - Scan right to find max height on right side
     * - Water at position i = min(left_max, right_max) - height[i]
     * - Sum up water at all positions
     * 
     * Time Complexity: O(n²) - for each element, we scan the entire array
     * Space Complexity: O(1) - no extra space used
     */
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
    
    /**
     * BETTER APPROACH (Dynamic Programming)
     * 
     * Idea: Precompute max heights on left and right for all positions
     * Better than brute force because we don't recalculate same values
     * 
     * How it works:
     * - Create leftMax array: leftMax[i] = max height from 0 to i
     * - Create rightMax array: rightMax[i] = max height from i to n-1
     * - For each position, water = min(leftMax[i], rightMax[i]) - height[i]
     * 
     * Time Complexity: O(n) - three passes through array
     * Space Complexity: O(n) - two additional arrays
     */
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
    
    /**
     * OPTIMAL APPROACH (Two Pointers)
     * 
     * Idea: Use two pointers moving from both ends, keeping track of max heights
     * This is the most elegant solution with optimal time and space complexity
     * 
     * Why it's optimal:
     * - Single pass through array
     * - Constant space complexity
     * - No need to store intermediate results
     * 
     * Key insight:
     * - Water trapped depends on the smaller of left_max and right_max
     * - We can process from the side with smaller max height
     * - If left_max < right_max, we know left side determines water level
     * 
     * How it works:
     * - Use left and right pointers
     * - Keep track of left_max and right_max
     * - Move pointer from side with smaller max height
     * - Calculate water as we go
     * 
     * Time Complexity: O(n) - single pass
     * Space Complexity: O(1) - only using variables
     */
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
    
    /**
     * ALTERNATIVE OPTIMAL APPROACH (Stack)
     * 
     * Idea: Use stack to find previous greater elements and calculate water layer by layer
     * This is another optimal approach that's good to know
     * 
     * Time Complexity: O(n) - each element pushed/popped once
     * Space Complexity: O(n) - stack in worst case
     */
    public int trapStack(int[] height) {
        Stack<Integer> stack = new Stack<>();
        int totalWater = 0;
        
        for (int i = 0; i < height.length; i++) {
            while (!stack.isEmpty() && height[i] > height[stack.peek()]) {
                int top = stack.pop();
                
                if (stack.isEmpty()) break;
                
                int distance = i - stack.peek() - 1;
                int boundedHeight = Math.min(height[i], height[stack.peek()]) - height[top];
                totalWater += distance * boundedHeight;
            }
            stack.push(i);
        }
        
        return totalWater;
    }
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        TrappingRainWater solution = new TrappingRainWater();
        int[][] testCases = {
            {0,1,0,2,1,0,1,3,2,1,2,1},
            {4,2,0,3,2,5},
            {3,0,2,0,4},
            {0,2,0},
            {2,0,2}
        };
        
        for (int[] test : testCases) {
            System.out.println("Heights: " + Arrays.toString(test));
            System.out.println("Brute Force: " + solution.trapBruteForce(test));
            System.out.println("Better (DP): " + solution.trapBetter(test));
            System.out.println("Optimal (Two Pointers): " + solution.trapOptimal(test));
            System.out.println("Stack Approach: " + solution.trapStack(test));
            System.out.println("---");
        }
    }
}