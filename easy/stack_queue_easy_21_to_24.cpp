#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// 21. Valid Parentheses - Stack
class Solution21 {
public:
    // Brute Force - Count approach O(n) time, O(1) space (works only for single type)
    bool isValid_bruteforce(string s) {
        // Simple counting approach (incomplete for mixed brackets)
        int count = 0;
        for(char c : s) {
            if(c == '(') count++;
            else if(c == ')') count--;
            if(count < 0) return false; // more closing than opening
        }
        return count == 0;
    }
    
    // Better - Manual tracking O(n) time, O(n) space
    bool isValid_better(string s) {
        vector<char> openBrackets;
        
        for(char c : s) {
            // opening brackets ko store karte hai
            if(c == '(' || c == '{' || c == '[') {
                openBrackets.push_back(c);
            }
            // closing brackets check karte hai
            else {
                if(openBrackets.empty()) return false;
                
                char lastOpen = openBrackets.back();
                openBrackets.pop_back();
                
                // matching pairs check karte hai
                if((c == ')' && lastOpen != '(') ||
                   (c == '}' && lastOpen != '{') ||
                   (c == ']' && lastOpen != '[')) {
                    return false;
                }
            }
        }
        
        return openBrackets.empty();
    }
    
    // Optimal - Stack approach O(n) time, O(n) space
    bool isValid(string s) {
        stack<char> brackets;
        
        for(char c : s) {
            // opening brackets push karte hai
            if(c == '(' || c == '{' || c == '[') {
                brackets.push(c);
            }
            // closing brackets ke liye matching check karte hai
            else {
                if(brackets.empty()) return false;
                
                char top = brackets.top();
                brackets.pop();
                
                // matching pairs verify karte hai
                if((c == ')' && top != '(') ||
                   (c == '}' && top != '{') ||
                   (c == ']' && top != '[')) {
                    return false;
                }
            }
        }
        
        // sab brackets match ho gaye
        return brackets.empty();
    }
};

// 22. Implement Queue using Stacks - Stack/Queue
class MyQueue22_bruteforce {
    stack<int> s1, s2;
    
public:
    // Brute Force - Move elements for every operation
    MyQueue22_bruteforce() {}
    
    void push(int x) {
        // sab elements s2 mein move karte hai
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        
        // new element s1 mein push karte hai
        s1.push(x);
        
        // sab elements wapas s1 mein move karte hai
        while(!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    int pop() {
        int front = s1.top();
        s1.pop();
        return front;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};

class MyQueue22_better {
    stack<int> input, output;
    
public:
    // Better - Move only when output is empty
    MyQueue22_better() {}
    
    void push(int x) {
        input.push(x);
    }
    
    int pop() {
        // agar output empty hai to input se transfer karte hai
        if(output.empty()) {
            while(!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        
        int front = output.top();
        output.pop();
        return front;
    }
    
    int peek() {
        if(output.empty()) {
            while(!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        
        return output.top();
    }
    
    bool empty() {
        return input.empty() && output.empty();
    }
};

// Optimal - Amortized O(1) operations
class MyQueue {
    stack<int> input, output;
    
    // helper function to transfer elements
    void transfer() {
        while(!input.empty()) {
            output.push(input.top());
            input.pop();
        }
    }
    
public:
    MyQueue() {}
    
    void push(int x) {
        input.push(x); // hamesha input mein push karte hai
    }
    
    int pop() {
        if(output.empty()) {
            transfer(); // transfer only when needed
        }
        
        int front = output.top();
        output.pop();
        return front;
    }
    
    int peek() {
        if(output.empty()) {
            transfer();
        }
        
        return output.top();
    }
    
    bool empty() {
        return input.empty() && output.empty();
    }
};

// 23. Implement Stack using Queues - Stack/Queue
class MyStack23_bruteforce {
    queue<int> q1, q2;
    
public:
    // Brute Force - Use two queues, move elements for every push
    MyStack23_bruteforce() {}
    
    void push(int x) {
        // new element q2 mein push karte hai
        q2.push(x);
        
        // q1 ke sab elements q2 mein move karte hai
        while(!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // q1 aur q2 swap karte hai
        swap(q1, q2);
    }
    
    int pop() {
        int top = q1.front();
        q1.pop();
        return top;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

class MyStack23_better {
    queue<int> q;
    
public:
    // Better - Single queue, rotate for push operation
    MyStack23_better() {}
    
    void push(int x) {
        int size = q.size();
        q.push(x);
        
        // x ko front pe lane ke liye size times rotate karte hai
        for(int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int top = q.front();
        q.pop();
        return top;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

// Optimal - Same as better (single queue is optimal)
class MyStack {
    queue<int> q;
    
public:
    MyStack() {}
    
    void push(int x) {
        int size = q.size();
        q.push(x);
        
        // newly added element ko front pe rotate karte hai
        for(int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int result = q.front();
        q.pop();
        return result;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

// 24. Min Stack - Stack
class MinStack24_bruteforce {
    vector<int> stack;
    
public:
    // Brute Force - Find minimum each time O(n) for getMin
    MinStack24_bruteforce() {}
    
    void push(int val) {
        stack.push_back(val);
    }
    
    void pop() {
        if(!stack.empty()) {
            stack.pop_back();
        }
    }
    
    int top() {
        return stack.back();
    }
    
    int getMin() {
        int minVal = stack[0];
        // har baar minimum find karte hai
        for(int val : stack) {
            minVal = min(minVal, val);
        }
        return minVal;
    }
};

class MinStack24_better {
    stack<int> mainStack;
    stack<int> minStack; // minimum elements track karte hai
    
public:
    // Better - Two stacks approach O(1) all operations
    MinStack24_better() {}
    
    void push(int val) {
        mainStack.push(val);
        
        // agar minStack empty hai ya current value choti hai
        if(minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if(!mainStack.empty()) {
            // agar top element minimum tha to minStack se bhi remove karte hai
            if(mainStack.top() == minStack.top()) {
                minStack.pop();
            }
            mainStack.pop();
        }
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

// Optimal - Space optimized using mathematical trick
class MinStack {
    stack<long long> st;
    long long minElement;
    
public:
    MinStack() {}
    
    void push(int val) {
        if(st.empty()) {
            st.push(val);
            minElement = val;
        }
        else if(val >= minElement) {
            st.push(val);
        }
        else {
            // encode karte hai: 2*val - minElement
            st.push(2LL * val - minElement);
            minElement = val;
        }
    }
    
    void pop() {
        if(!st.empty()) {
            long long top = st.top();
            st.pop();
            
            // agar encoded value hai to previous minimum recover karte hai
            if(top < minElement) {
                minElement = 2 * minElement - top;
            }
        }
    }
    
    int top() {
        long long topVal = st.top();
        // agar encoded hai to actual value return karte hai
        if(topVal < minElement) {
            return minElement;
        }
        return topVal;
    }
    
    int getMin() {
        return minElement;
    }
};