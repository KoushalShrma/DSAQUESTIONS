/**
 * Problem 17: Best Time to Buy and Sell Stock
 * Find the maximum profit you can achieve from buying and selling stock once.
 * 
 * Student Notes Style Explanation:
 * We have an array of stock prices and want to buy low, sell high.
 * The rule is: we can only buy once and sell once, and we must buy before we sell.
 * This is a classic DP problem that teaches us about keeping track of minimum values.
 */

public class BestTimeToBuyAndSellStock {
    
    /**
     * BRUTE FORCE APPROACH
     * 
     * Idea: Try every possible buy-sell combination
     * For each day we could buy, check all future days we could sell
     * 
     * How it works:
     * - For each buy day i, check all sell days j where j > i
     * - Calculate profit = prices[j] - prices[i]
     * - Keep track of maximum profit seen
     * 
     * Time Complexity: O(n²) - nested loops through all pairs
     * Space Complexity: O(1) - only using variables
     */
    public int maxProfitBruteForce(int[] prices) {
        int maxProfit = 0;
        int n = prices.length;
        
        // Try every buy day
        for (int buyDay = 0; buyDay < n - 1; buyDay++) {
            // Try every sell day after buy day
            for (int sellDay = buyDay + 1; sellDay < n; sellDay++) {
                int profit = prices[sellDay] - prices[buyDay];
                maxProfit = Math.max(maxProfit, profit);
            }
        }
        
        return maxProfit;
    }
    
    /**
     * BETTER APPROACH (Two Pass)
     * 
     * Idea: Precompute maximum price for each position from right
     * Better because we avoid recalculating max prices repeatedly
     * 
     * How it works:
     * - First pass: compute maxPriceFromRight[i] = max price from day i to end
     * - Second pass: for each buy day, profit = maxPriceFromRight[i+1] - prices[i]
     * 
     * Time Complexity: O(n) - two passes through array
     * Space Complexity: O(n) - additional array for max prices
     */
    public int maxProfitBetter(int[] prices) {
        int n = prices.length;
        if (n <= 1) return 0;
        
        // Precompute maximum price from each position to the right
        int[] maxPriceFromRight = new int[n];
        maxPriceFromRight[n - 1] = prices[n - 1];
        
        for (int i = n - 2; i >= 0; i--) {
            maxPriceFromRight[i] = Math.max(prices[i], maxPriceFromRight[i + 1]);
        }
        
        // Find maximum profit
        int maxProfit = 0;
        for (int i = 0; i < n - 1; i++) {
            int profit = maxPriceFromRight[i + 1] - prices[i];
            maxProfit = Math.max(maxProfit, profit);
        }
        
        return maxProfit;
    }
    
    /**
     * OPTIMAL APPROACH (Single Pass)
     * 
     * Idea: Keep track of minimum price seen so far and calculate profit on each day
     * This is the most elegant solution - classic DP thinking!
     * 
     * Why it's optimal:
     * - Single pass through array
     * - Constant space usage
     * - Simple and intuitive logic
     * 
     * Key insight:
     * - For each day, we can either sell (if we bought on minimum price day)
     * - Or update our minimum price if current price is lower
     * - We always want to buy at the lowest price we've seen so far
     * 
     * Time Complexity: O(n) - single pass
     * Space Complexity: O(1) - only using variables
     */
    public int maxProfitOptimal(int[] prices) {
        if (prices.length <= 1) return 0;
        
        int minPrice = prices[0];  // Minimum price seen so far (best buy day)
        int maxProfit = 0;        // Maximum profit achievable
        
        for (int i = 1; i < prices.length; i++) {
            // If we sell today, what profit would we get?
            int todayProfit = prices[i] - minPrice;
            maxProfit = Math.max(maxProfit, todayProfit);
            
            // Update minimum price if today's price is lower
            minPrice = Math.min(minPrice, prices[i]);
        }
        
        return maxProfit;
    }
    
    // Test method to demonstrate all approaches
    public static void main(String[] args) {
        BestTimeToBuyAndSellStock solution = new BestTimeToBuyAndSellStock();
        int[][] testCases = {
            {7, 1, 5, 3, 6, 4},  // Expected: 5 (buy at 1, sell at 6)
            {7, 6, 4, 3, 1},     // Expected: 0 (no profit possible)
            {1, 2, 3, 4, 5},     // Expected: 4 (buy at 1, sell at 5)
            {2, 4, 1},           // Expected: 2 (buy at 2, sell at 4)
            {1}                  // Expected: 0 (need at least 2 days)
        };
        
        for (int[] prices : testCases) {
            System.out.println("Prices: " + java.util.Arrays.toString(prices));
            System.out.println("Brute Force: " + solution.maxProfitBruteForce(prices));
            System.out.println("Better: " + solution.maxProfitBetter(prices));
            System.out.println("Optimal: " + solution.maxProfitOptimal(prices));
            System.out.println("---");
        }
    }
}