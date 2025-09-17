# DSA Questions Repository

This repository contains comprehensive solutions to 154 Data Structures and Algorithms questions, organized by difficulty level. Each solution follows a consistent format with multiple approaches explained in a student-friendly manner.

## 📁 Repository Structure

```
DSAQUESTIONS/
├── src/
│   ├── easy/           # 66 Easy problems
│   ├── medium/         # 78 Medium problems
│   ├── hard/           # 10 Hard problems
│   └── utils/          # Common utility classes
├── docs/
│   └── AllSolutions.docx  # Combined Word document
└── README.md
```

## 📋 Solution Format

Each problem follows this consistent structure:

### 🔴 Problem Name
*One-line problem statement*

#### 1. Brute Force Approach
- **Explanation**: Simple, intuitive approach explained in student-friendly language
- **Java Code**: Clean, well-commented implementation
- **Complexity**: Time and Space complexity analysis

#### 2. Better Approach (if applicable)
- **Explanation**: Improved approach with optimization details
- **Java Code**: Enhanced implementation
- **Complexity**: Better time/space complexity

#### 3. Optimal Approach
- **Explanation**: Most efficient solution with detailed reasoning
- **Java Code**: Optimal implementation
- **Complexity**: Best possible time/space complexity

## 🟢 Easy Problems (66)

1. [Two Sum](src/easy/TwoSum.java) - Find two numbers that add up to target
2. [Palindrome Number](src/easy/PalindromeNumber.java) - Check if number reads same forwards and backwards
3. Roman to Integer - Convert Roman numerals to integers
4. Longest Common Prefix - Find longest common prefix string
5. [Valid Parentheses](src/easy/ValidParentheses.java) - Check if brackets are properly balanced
6. Merge Two Sorted Lists - Merge two sorted linked lists
7. Remove Duplicates from Sorted Array - Remove duplicates in-place
8. Remove Element - Remove all instances of value
9. Find the Index of the First Occurrence in a String - Find needle in haystack
10. Search Insert Position - Find position to insert target
11. Length of Last Word - Return length of last word in string
12. Plus One - Add one to number represented as array
13. Sqrt(x) - Integer square root
14. Climbing Stairs - Count ways to reach top
15. Remove Duplicates from Sorted List - Remove duplicates from linked list
16. Merge Sorted Array - Merge two sorted arrays in-place
17. Best Time to Buy and Sell Stock - Maximum profit from stock prices
18. Valid Palindrome - Check if string is palindrome
19. Single Number - Find number that appears once
20. Linked List Cycle - Detect cycle in linked list
21. Intersection of Two Linked Lists - Find intersection point
22. Majority Element - Find element appearing more than n/2 times
23. Reverse Linked List - Reverse a linked list
24. Palindrome Linked List - Check if linked list is palindrome
25. Power of Two - Check if number is power of 2
26. Implement Queue using Stacks - Queue implementation using stacks
27. Remove Linked List Elements - Remove all nodes with given value
28. Delete Node in a Linked List - Delete node given only access to that node
29. Valid Anagram - Check if two strings are anagrams
30. Missing Number - Find missing number in array
31. Move Zeroes - Move all zeros to end
32. Power of Three - Check if number is power of 3
33. Power of Four - Check if number is power of 4
34. Reverse String - Reverse character array in-place
35. Reverse Vowels of a String - Reverse only vowels in string
36. Valid Perfect Square - Check if number is perfect square
37. Arranging Coins - Find rows that can be formed with coins
38. Find All Numbers Disappeared in an Array - Find missing numbers
39. Assign Cookies - Assign cookies to children optimally
40. Fibonacci Number - Calculate nth Fibonacci number
41. Reverse Words in a String III - Reverse words individually
42. Binary Search - Classic binary search implementation
43. Find Pivot Index - Find index where left sum equals right sum
44. Find Smallest Letter Greater Than Target - Binary search variant
45. Jewels and Stones - Count jewels in stones
46. Middle of the Linked List - Find middle node of linked list
47. Reverse Only Letters - Reverse only alphabetic characters
48. Relative Sort Array - Sort array according to relative order
49. Unique Number of Occurrences - Check if all frequencies are unique
50. Convert Binary Number in a Linked List to Integer - Binary to decimal conversion
51. Find Numbers with Even Number of Digits - Count numbers with even digits
52. Number of Steps to Reduce a Number to Zero - Count steps to reach zero
53. Check If a Word Occurs As a Prefix - String prefix matching
54. Running Sum of 1d Array - Calculate running sum
55. Path Sum - Check if root-to-leaf sum exists
56. Diameter of Binary Tree - Find diameter of binary tree
57. Defanging an IP Address - Replace dots with special string
58. Split a String in Balanced Strings - Count balanced substrings
59. Widest Vertical Area Between Two Points - Find widest area
60. Check If Two String Arrays are Equivalent - Compare string arrays
61. Richest Customer Wealth - Find customer with maximum wealth
62. Goal Parser Interpretation - Parse goal string
63. Count the Number of Consistent Strings - Count valid strings
64. Truncate Sentence - Truncate sentence to k words
65. Minimum Operations to Make the Array Increasing - Make array strictly increasing
66. Build Array from Permutation - Build array using permutation

## 🟡 Medium Problems (78)

1. [Longest Substring Without Repeating Characters](src/medium/LongestSubstringWithoutRepeating.java) - Find longest substring with unique characters
2. Reverse Integer - Reverse digits of integer
3. Container With Most Water - Find maximum water container
4. 3Sum - Find triplets that sum to zero
5. Remove Nth Node From End of List - Remove nth node from end
6. Generate Parentheses - Generate all valid parentheses combinations
7. Next Permutation - Find next lexicographically greater permutation
8. Search in Rotated Sorted Array - Search in rotated array
9. Find First and Last Position of Element - Find range of target
10. Count and Say - Generate count-and-say sequence
... *[Additional 68 medium problems listed in implementation]*

## 🔴 Hard Problems (10)

1. Median of Two Sorted Arrays - Find median of two sorted arrays
2. Merge k Sorted Lists - Merge multiple sorted lists
3. First Missing Positive - Find smallest missing positive
4. [Trapping Rain Water](src/hard/TrappingRainWater.java) - Calculate trapped rainwater
5. Permutation Sequence - Find kth permutation
6. Largest Rectangle in Histogram - Find largest rectangle area
7. Reducing Dishes - Maximize satisfaction score
8. Find Minimum in Rotated Sorted Array II - Find minimum with duplicates
9. Longest Valid Parentheses - Find longest valid parentheses
10. Minimum Window Substring - Find minimum window containing all characters

## 🛠️ How to Use

### Compile and Run Individual Solutions
```bash
# Navigate to specific difficulty folder
cd src/easy

# Compile and run a solution
javac TwoSum.java
java TwoSum
```

### Run All Tests
```bash
# From repository root
find src -name "*.java" -exec javac {} \;
find src -name "*.class" -exec java {} \;
```

### View Combined Document
Open `docs/AllSolutions.docx` for a comprehensive document containing all solutions.

## 📚 Learning Path

### For Beginners
1. Start with Easy problems 1-20
2. Focus on understanding brute force approaches first
3. Gradually move to optimal solutions

### For Intermediate
1. Complete all Easy problems
2. Tackle Medium problems by category (arrays, strings, trees, etc.)
3. Study time/space complexity patterns

### For Advanced
1. Master all Medium problems
2. Solve Hard problems
3. Focus on optimization techniques and edge cases

## 💡 Key Concepts Covered

- **Arrays & Strings**: Two pointers, sliding window, binary search
- **Linked Lists**: Fast/slow pointers, cycle detection, reversal
- **Stacks & Queues**: Monotonic stack, deque operations
- **Trees**: DFS, BFS, tree traversals
- **Dynamic Programming**: Memoization, tabulation
- **Hash Tables**: Frequency counting, mapping techniques
- **Sorting & Searching**: Various algorithms and optimizations
- **Graph Algorithms**: BFS, DFS, topological sort

## 🎯 Practice Tips

1. **Understand the Pattern**: Each problem teaches specific algorithmic patterns
2. **Code Quality**: Focus on clean, readable code with proper comments
3. **Edge Cases**: Always consider boundary conditions
4. **Complexity Analysis**: Understand why certain approaches are better
5. **Multiple Solutions**: Try to implement different approaches for comparison

## 📖 Additional Resources

- [LeetCode](https://leetcode.com/) - Original problem source
- [GeeksforGeeks](https://www.geeksforgeeks.org/) - Algorithm explanations
- [Visualizing Algorithms](https://visualgo.net/) - Algorithm visualizations

## 🤝 Contributing

Feel free to:
- Improve existing solutions
- Add alternative approaches
- Fix bugs or typos
- Enhance documentation

## 📄 License

This repository is for educational purposes. Solutions are implemented independently and explained in a student-friendly manner.

---

*Happy Coding! 🚀*