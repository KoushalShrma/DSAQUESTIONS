#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

// 46. Gas Station - Array (Medium)
class Solution46_Medium {
public:
    // Brute Force - Try starting from each station O(n²) time, O(1) space
    int canCompleteCircuit_bruteforce(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        // har station se start karne ki koshish karte hai
        for(int start = 0; start < n; start++) {
            int tank = 0;
            bool canComplete = true;
            
            // circuit complete karne ki koshish karte hai
            for(int i = 0; i < n; i++) {
                int currentStation = (start + i) % n;
                tank += gas[currentStation] - cost[currentStation];
                
                if(tank < 0) {
                    canComplete = false;
                    break;
                }
            }
            
            if(canComplete) return start;
        }
        
        return -1;
    }
    
    // Better - Check total gas vs total cost first O(n) time, O(1) space
    int canCompleteCircuit_better(vector<int>& gas, vector<int>& cost) {
        int totalGas = 0, totalCost = 0;
        
        // total gas aur cost check karte hai
        for(int i = 0; i < gas.size(); i++) {
            totalGas += gas[i];
            totalCost += cost[i];
        }
        
        if(totalGas < totalCost) return -1; // impossible
        
        // ek valid starting point try karte hai
        int tank = 0, start = 0;
        
        for(int i = 0; i < gas.size(); i++) {
            tank += gas[i] - cost[i];
            
            if(tank < 0) {
                start = i + 1; // next station se try karte hai
                tank = 0;
            }
        }
        
        return start;
    }
    
    // Optimal - Single pass greedy O(n) time, O(1) space
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalBalance = 0;
        int currentBalance = 0;
        int startStation = 0;
        
        for(int i = 0; i < gas.size(); i++) {
            int balance = gas[i] - cost[i];
            totalBalance += balance;
            currentBalance += balance;
            
            // agar current balance negative ho gaya
            if(currentBalance < 0) {
                startStation = i + 1;
                currentBalance = 0;
            }
        }
        
        return totalBalance >= 0 ? startStation : -1;
    }
};

// 47. Insert Interval - Array (Medium)
class Solution47_Medium {
public:
    // Brute Force - Insert and merge O(n²) time, O(n) space
    vector<vector<int>> insert_bruteforce(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        
        // new interval ko appropriate position pe insert karte hai
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());
        
        // merge overlapping intervals
        for(auto interval : intervals) {
            if(result.empty() || result.back()[1] < interval[0]) {
                result.push_back(interval);
            } else {
                result.back()[1] = max(result.back()[1], interval[1]);
            }
        }
        
        return result;
    }
    
    // Better - Three-phase approach O(n) time, O(n) space
    vector<vector<int>> insert_better(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        int n = intervals.size();
        
        // phase 1: add intervals that end before newInterval starts
        while(i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }
        
        // phase 2: merge overlapping intervals with newInterval
        while(i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.push_back(newInterval);
        
        // phase 3: add remaining intervals
        while(i < n) {
            result.push_back(intervals[i]);
            i++;
        }
        
        return result;
    }
    
    // Optimal - Direct insertion and merge O(n) time, O(1) extra space
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        
        // add non-overlapping intervals before newInterval
        while(i < intervals.size() && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i++]);
        }
        
        // merge overlapping intervals
        while(i < intervals.size() && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.push_back(newInterval);
        
        // add remaining intervals
        while(i < intervals.size()) {
            result.push_back(intervals[i++]);
        }
        
        return result;
    }
};

// 48. String to Integer (atoi) - String (Medium)
class Solution48_Medium {
public:
    // Brute Force - Character by character processing O(n) time, O(1) space
    int myAtoi_bruteforce(string s) {
        if(s.empty()) return 0;
        
        int i = 0, n = s.length();
        long long result = 0;
        int sign = 1;
        
        // skip leading whitespaces
        while(i < n && s[i] == ' ') i++;
        
        // check sign
        if(i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // convert digits
        while(i < n && isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // overflow check (brute force way)
            if(result > (LLONG_MAX - digit) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + digit;
            i++;
        }
        
        result *= sign;
        
        // clamp to int range
        if(result > INT_MAX) return INT_MAX;
        if(result < INT_MIN) return INT_MIN;
        
        return result;
    }
    
    // Better - Overflow handling with checks O(n) time, O(1) space
    int myAtoi_better(string s) {
        int i = 0, sign = 1;
        long long result = 0;
        
        // skip whitespace
        while(i < s.length() && s[i] == ' ') i++;
        
        // handle sign
        if(i < s.length() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i++] == '-') ? -1 : 1;
        }
        
        // process digits
        while(i < s.length() && isdigit(s[i])) {
            // overflow prevention
            if(result > INT_MAX / 10 || 
               (result == INT_MAX / 10 && (s[i] - '0') > INT_MAX % 10)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            
            result = result * 10 + (s[i++] - '0');
        }
        
        return result * sign;
    }
    
    // Optimal - State machine approach O(n) time, O(1) space
    int myAtoi(string s) {
        enum State { START, SIGN, NUMBER, END };
        State state = START;
        
        int sign = 1;
        long long result = 0;
        
        for(char c : s) {
            switch(state) {
                case START:
                    if(c == ' ') continue;
                    else if(c == '+' || c == '-') {
                        sign = (c == '-') ? -1 : 1;
                        state = SIGN;
                    }
                    else if(isdigit(c)) {
                        result = c - '0';
                        state = NUMBER;
                    }
                    else {
                        state = END;
                    }
                    break;
                    
                case SIGN:
                    if(isdigit(c)) {
                        result = c - '0';
                        state = NUMBER;
                    }
                    else {
                        state = END;
                    }
                    break;
                    
                case NUMBER:
                    if(isdigit(c)) {
                        // overflow check
                        if(result > INT_MAX / 10 || 
                           (result == INT_MAX / 10 && (c - '0') > INT_MAX % 10)) {
                            return (sign == 1) ? INT_MAX : INT_MIN;
                        }
                        result = result * 10 + (c - '0');
                    }
                    else {
                        state = END;
                    }
                    break;
                    
                case END:
                    break;
            }
            
            if(state == END) break;
        }
        
        return result * sign;
    }
};

// 49. Multiply Strings - String (Medium)
class Solution49_Medium {
public:
    // Brute Force - Simulate multiplication by hand O(m*n) time, O(m+n) space
    string multiply_bruteforce(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        
        vector<string> partialProducts;
        
        // har digit of num2 ke liye num1 se multiply karte hai
        for(int i = num2.length() - 1; i >= 0; i--) {
            string product = multiplyByDigit(num1, num2[i] - '0');
            
            // appropriate zeros append karte hai
            for(int j = 0; j < num2.length() - 1 - i; j++) {
                product += "0";
            }
            
            partialProducts.push_back(product);
        }
        
        // sab partial products add karte hai
        string result = "0";
        for(string product : partialProducts) {
            result = addStrings(result, product);
        }
        
        return result;
    }
    
    string multiplyByDigit(string num, int digit) {
        string result = "";
        int carry = 0;
        
        for(int i = num.length() - 1; i >= 0; i--) {
            int prod = (num[i] - '0') * digit + carry;
            result = char(prod % 10 + '0') + result;
            carry = prod / 10;
        }
        
        if(carry > 0) {
            result = to_string(carry) + result;
        }
        
        return result;
    }
    
    string addStrings(string num1, string num2) {
        string result = "";
        int carry = 0;
        int i = num1.length() - 1, j = num2.length() - 1;
        
        while(i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if(i >= 0) sum += num1[i--] - '0';
            if(j >= 0) sum += num2[j--] - '0';
            
            result = char(sum % 10 + '0') + result;
            carry = sum / 10;
        }
        
        return result;
    }
    
    // Better - Grade school multiplication O(m*n) time, O(m+n) space
    string multiply_better(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        
        int m = num1.length(), n = num2.length();
        vector<int> result(m + n, 0);
        
        // reverse order mein multiply karte hai
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int sum = mul + result[p2];
                
                result[p2] = sum % 10;
                result[p1] += sum / 10;
            }
        }
        
        // convert to string
        string str = "";
        for(int i = 0; i < result.size(); i++) {
            if(!(str.empty() && result[i] == 0)) {
                str += to_string(result[i]);
            }
        }
        
        return str.empty() ? "0" : str;
    }
    
    // Optimal - Optimized grade school O(m*n) time, O(m+n) space
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        
        int m = num1.length(), n = num2.length();
        vector<int> pos(m + n, 0);
        
        for(int i = m - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int sum = mul + pos[p2];
                
                pos[p2] = sum % 10;
                pos[p1] += sum / 10;
            }
        }
        
        int i = 0;
        while(i < pos.size() && pos[i] == 0) i++; // skip leading zeros
        
        string result = "";
        while(i < pos.size()) {
            result += to_string(pos[i++]);
        }
        
        return result.empty() ? "0" : result;
    }
};

// 50. Reverse Words in a String - String (Medium)
class Solution50_Medium {
public:
    // Brute Force - Split and reverse O(n) time, O(n) space
    string reverseWords_bruteforce(string s) {
        vector<string> words;
        string word = "";
        
        // words extract karte hai
        for(char c : s) {
            if(c == ' ') {
                if(!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
            } else {
                word += c;
            }
        }
        if(!word.empty()) words.push_back(word);
        
        // reverse order mein join karte hai
        string result = "";
        for(int i = words.size() - 1; i >= 0; i--) {
            if(!result.empty()) result += " ";
            result += words[i];
        }
        
        return result;
    }
    
    // Better - Two pointers approach O(n) time, O(n) space
    string reverseWords_better(string s) {
        string result = "";
        int n = s.length();
        int i = n - 1;
        
        while(i >= 0) {
            // skip trailing spaces
            while(i >= 0 && s[i] == ' ') i--;
            
            if(i < 0) break;
            
            // extract word from right to left
            int j = i;
            while(i >= 0 && s[i] != ' ') i--;
            
            // add word to result
            if(!result.empty()) result += " ";
            result += s.substr(i + 1, j - i);
        }
        
        return result;
    }
    
    // Optimal - In-place with string stream O(n) time, O(1) extra space
    string reverseWords(string s) {
        // remove leading and trailing spaces, and reduce multiple spaces to single
        int left = 0, right = 0;
        
        // remove leading spaces
        while(right < s.length() && s[right] == ' ') right++;
        
        // process characters
        while(right < s.length()) {
            if(s[right] != ' ') {
                s[left++] = s[right];
            } else if(left > 0 && s[left - 1] != ' ') {
                s[left++] = ' ';
            }
            right++;
        }
        
        // remove trailing space
        if(left > 0 && s[left - 1] == ' ') left--;
        s.resize(left);
        
        // reverse entire string
        reverse(s.begin(), s.end());
        
        // reverse each word
        int start = 0;
        for(int i = 0; i <= s.length(); i++) {
            if(i == s.length() || s[i] == ' ') {
                reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }
        }
        
        return s;
    }
};

// 51. Maximum Product Subarray - Array (Medium)
class Solution51_Medium {
public:
    // Brute Force - Check all subarrays O(n²) time, O(1) space
    int maxProduct_bruteforce(vector<int>& nums) {
        int maxProd = nums[0];
        
        for(int i = 0; i < nums.size(); i++) {
            int currentProd = 1;
            
            for(int j = i; j < nums.size(); j++) {
                currentProd *= nums[j];
                maxProd = max(maxProd, currentProd);
            }
        }
        
        return maxProd;
    }
    
    // Better - Track min and max products O(n) time, O(1) space
    int maxProduct_better(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int maxProd = nums[0];
        int currentMax = nums[0];
        int currentMin = nums[0];
        
        for(int i = 1; i < nums.size(); i++) {
            // agar current element negative hai to max aur min swap ho jayenge
            if(nums[i] < 0) {
                swap(currentMax, currentMin);
            }
            
            currentMax = max(nums[i], currentMax * nums[i]);
            currentMin = min(nums[i], currentMin * nums[i]);
            
            maxProd = max(maxProd, currentMax);
        }
        
        return maxProd;
    }
    
    // Optimal - Forward and backward scan O(n) time, O(1) space
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int maxProd = nums[0];
        
        // forward scan
        int prod = 1;
        for(int i = 0; i < n; i++) {
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0) prod = 1; // reset after zero
        }
        
        // backward scan
        prod = 1;
        for(int i = n - 1; i >= 0; i--) {
            prod *= nums[i];
            maxProd = max(maxProd, prod);
            if(prod == 0) prod = 1; // reset after zero
        }
        
        return maxProd;
    }
};

// 52. Meeting Rooms II - Array (Medium)
class Solution52_Medium {
public:
    // Brute Force - Check conflicts for each interval O(n²) time, O(1) space
    int minMeetingRooms_bruteforce(vector<vector<int>>& intervals) {
        if(intervals.empty()) return 0;
        
        int maxRooms = 1;
        
        // har interval ke liye check karte hai kitne overlap karte hai
        for(int i = 0; i < intervals.size(); i++) {
            int overlaps = 1; // current interval
            
            for(int j = 0; j < intervals.size(); j++) {
                if(i != j) {
                    // check if intervals[j] overlaps with intervals[i]
                    if(intervals[j][0] < intervals[i][1] && intervals[j][1] > intervals[i][0]) {
                        overlaps++;
                    }
                }
            }
            
            maxRooms = max(maxRooms, overlaps);
        }
        
        return maxRooms;
    }
    
    // Better - Event-based approach O(nlogn) time, O(n) space
    int minMeetingRooms_better(vector<vector<int>>& intervals) {
        vector<pair<int, int>> events; // {time, type} where type: 1=start, -1=end
        
        for(auto& interval : intervals) {
            events.push_back({interval[0], 1});  // meeting starts
            events.push_back({interval[1], -1}); // meeting ends
        }
        
        sort(events.begin(), events.end());
        
        int currentRooms = 0;
        int maxRooms = 0;
        
        for(auto& event : events) {
            currentRooms += event.second;
            maxRooms = max(maxRooms, currentRooms);
        }
        
        return maxRooms;
    }
    
    // Optimal - Min heap approach O(nlogn) time, O(n) space
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if(intervals.empty()) return 0;
        
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });
        
        priority_queue<int, vector<int>, greater<int>> minHeap; // end times
        
        for(auto& interval : intervals) {
            // agar koi meeting end ho gayi hai to room free kar dete hai
            if(!minHeap.empty() && minHeap.top() <= interval[0]) {
                minHeap.pop();
            }
            
            // current meeting ke liye room assign karte hai
            minHeap.push(interval[1]);
        }
        
        return minHeap.size();
    }
};

// 53. Course Schedule - Array (Medium)
class Solution53_Medium {
public:
    // Brute Force - DFS with visited tracking O(V+E) time, O(V) space
    bool canFinish_bruteforce(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        
        // adjacency list banate hai
        for(auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]); // pre[1] -> pre[0]
        }
        
        // har course ke liye cycle check karte hai
        for(int i = 0; i < numCourses; i++) {
            vector<int> visited(numCourses, 0); // 0=unvisited, 1=visiting, 2=visited
            if(hasCycle(graph, i, visited)) {
                return false;
            }
        }
        
        return true;
    }
    
    bool hasCycle(vector<vector<int>>& graph, int node, vector<int>& visited) {
        if(visited[node] == 1) return true;  // cycle detected
        if(visited[node] == 2) return false; // already processed
        
        visited[node] = 1; // mark as visiting
        
        for(int neighbor : graph[node]) {
            if(hasCycle(graph, neighbor, visited)) {
                return true;
            }
        }
        
        visited[node] = 2; // mark as visited
        return false;
    }
    
    // Better - Topological sort with DFS O(V+E) time, O(V) space
    bool canFinish_better(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        
        for(auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]);
        }
        
        vector<int> color(numCourses, 0); // 0=white, 1=gray, 2=black
        
        for(int i = 0; i < numCourses; i++) {
            if(color[i] == 0 && dfs(graph, i, color)) {
                return false;
            }
        }
        
        return true;
    }
    
    bool dfs(vector<vector<int>>& graph, int node, vector<int>& color) {
        color[node] = 1; // gray
        
        for(int neighbor : graph[node]) {
            if(color[neighbor] == 1 || (color[neighbor] == 0 && dfs(graph, neighbor, color))) {
                return true; // cycle found
            }
        }
        
        color[node] = 2; // black
        return false;
    }
    
    // Optimal - Kahn's algorithm (BFS topological sort) O(V+E) time, O(V) space
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // graph aur indegree build karte hai
        for(auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]);
            indegree[pre[0]]++;
        }
        
        queue<int> q;
        
        // indegree 0 wale nodes queue mein add karte hai
        for(int i = 0; i < numCourses; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int processed = 0;
        
        while(!q.empty()) {
            int course = q.front();
            q.pop();
            processed++;
            
            // neighbors ka indegree decrease karte hai
            for(int next : graph[course]) {
                indegree[next]--;
                if(indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return processed == numCourses;
    }
};

// 54. Decode String - String (Medium)
class Solution54_Medium {
public:
    // Brute Force - Recursive approach O(maxK^(countK) * n) time
    string decodeString_bruteforce(string s) {
        return decode(s, 0).first;
    }
    
    pair<string, int> decode(string s, int index) {
        string result = "";
        
        while(index < s.length() && s[index] != ']') {
            if(isdigit(s[index])) {
                // number parse karte hai
                int k = 0;
                while(index < s.length() && isdigit(s[index])) {
                    k = k * 10 + (s[index] - '0');
                    index++;
                }
                
                index++; // skip '['
                
                // recursive call for substring
                auto result_pair = decode(s, index);
                string decoded = result_pair.first;
                index = result_pair.second;
                
                index++; // skip ']'
                
                // k times repeat karte hai
                for(int i = 0; i < k; i++) {
                    result += decoded;
                }
            } else {
                result += s[index];
                index++;
            }
        }
        
        return {result, index};
    }
    
    // Better - Stack approach O(maxK^(countK) * n) time, O(n) space
    string decodeString_better(string s) {
        stack<string> stringStack;
        stack<int> countStack;
        string currentString = "";
        int currentCount = 0;
        
        for(char c : s) {
            if(isdigit(c)) {
                currentCount = currentCount * 10 + (c - '0');
            }
            else if(c == '[') {
                countStack.push(currentCount);
                stringStack.push(currentString);
                currentCount = 0;
                currentString = "";
            }
            else if(c == ']') {
                int count = countStack.top();
                countStack.pop();
                
                string temp = currentString;
                currentString = stringStack.top();
                stringStack.pop();
                
                // temp string ko count times append karte hai
                for(int i = 0; i < count; i++) {
                    currentString += temp;
                }
            }
            else {
                currentString += c;
            }
        }
        
        return currentString;
    }
    
    // Optimal - Iterative with index tracking O(maxK^(countK) * n) time, O(n) space
    string decodeString(string s) {
        stack<pair<string, int>> stk; // {previous_string, repeat_count}
        string currentStr = "";
        int num = 0;
        
        for(char c : s) {
            if(isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            else if(c == '[') {
                stk.push({currentStr, num});
                currentStr = "";
                num = 0;
            }
            else if(c == ']') {
                auto [prevStr, count] = stk.top();
                stk.pop();
                
                string temp = currentStr;
                currentStr = prevStr;
                
                for(int i = 0; i < count; i++) {
                    currentStr += temp;
                }
            }
            else {
                currentStr += c;
            }
        }
        
        return currentStr;
    }
};

// 55. Evaluate Reverse Polish Notation - String (Medium)
class Solution55_Medium {
public:
    // Brute Force - Convert to infix and evaluate O(n²) time, O(n) space
    int evalRPN_bruteforce(vector<string>& tokens) {
        // Note: This is a conceptual brute force - actual implementation would be complex
        // Converting RPN to infix and then evaluating
        
        stack<string> expressions;
        
        for(string token : tokens) {
            if(token == "+" || token == "-" || token == "*" || token == "/") {
                string b = expressions.top(); expressions.pop();
                string a = expressions.top(); expressions.pop();
                
                string expr = "(" + a + " " + token + " " + b + ")";
                expressions.push(expr);
            } else {
                expressions.push(token);
            }
        }
        
        // evaluate the final expression (simplified here)
        return evaluateExpression(expressions.top());
    }
    
    int evaluateExpression(string expr) {
        // Simplified evaluation - in real implementation would need full parser
        return 0;
    }
    
    // Better - Stack with string to int conversion O(n) time, O(n) space
    int evalRPN_better(vector<string>& tokens) {
        stack<long long> stk;
        
        for(string token : tokens) {
            if(token == "+" || token == "-" || token == "*" || token == "/") {
                long long b = stk.top(); stk.pop();
                long long a = stk.top(); stk.pop();
                
                long long result;
                if(token == "+") result = a + b;
                else if(token == "-") result = a - b;
                else if(token == "*") result = a * b;
                else result = a / b; // integer division
                
                stk.push(result);
            } else {
                stk.push(stoll(token));
            }
        }
        
        return stk.top();
    }
    
    // Optimal - Efficient stack operations O(n) time, O(n) space
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        
        for(const string& token : tokens) {
            if(token.length() > 1 || isdigit(token[0])) {
                stk.push(stoi(token));
            } else {
                int b = stk.top(); stk.pop();
                int a = stk.top(); stk.pop();
                
                switch(token[0]) {
                    case '+': stk.push(a + b); break;
                    case '-': stk.push(a - b); break;
                    case '*': stk.push(a * b); break;
                    case '/': stk.push(a / b); break;
                }
            }
        }
        
        return stk.top();
    }
};