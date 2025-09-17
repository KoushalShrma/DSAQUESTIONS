#include <vector>
#include <unordered_set>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 16. Reverse Linked List - LinkedList
class Solution16 {
public:
    // Brute Force - Using array O(n) time, O(n) space
    ListNode* reverseList_bruteforce(ListNode* head) {
        if(!head) return nullptr;
        
        vector<int> values;
        ListNode* current = head;
        
        // sab values array mein store karte hai
        while(current) {
            values.push_back(current->val);
            current = current->next;
        }
        
        // reverse order mein values assign karte hai
        current = head;
        for(int i = values.size() - 1; i >= 0; i--) {
            current->val = values[i];
            current = current->next;
        }
        
        return head;
    }
    
    // Better - Recursive approach O(n) time, O(n) space
    ListNode* reverseList_better(ListNode* head) {
        // base case
        if(!head || !head->next) return head;
        
        // recursively reverse remaining list
        ListNode* reversedHead = reverseList_better(head->next);
        
        // reverse current connection
        head->next->next = head;
        head->next = nullptr;
        
        return reversedHead;
    }
    
    // Optimal - Iterative approach O(n) time, O(1) space
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while(current) {
            ListNode* nextTemp = current->next; // next node save karte hai
            current->next = prev; // reverse karte hai
            prev = current; // prev ko aage move karte hai
            current = nextTemp; // current ko aage move karte hai
        }
        
        return prev; // new head
    }
};

// 17. Merge Two Sorted Lists - LinkedList
class Solution17 {
public:
    // Brute Force - Create new list O(n+m) time, O(n+m) space
    ListNode* mergeTwoLists_bruteforce(ListNode* list1, ListNode* list2) {
        vector<int> values;
        
        // dono lists ki values collect karte hai
        ListNode* current = list1;
        while(current) {
            values.push_back(current->val);
            current = current->next;
        }
        
        current = list2;
        while(current) {
            values.push_back(current->val);
            current = current->next;
        }
        
        // sort karte hai
        sort(values.begin(), values.end());
        
        // new list banate hai
        if(values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        current = head;
        for(int i = 1; i < values.size(); i++) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
        
        return head;
    }
    
    // Better - Recursive approach O(n+m) time, O(n+m) space
    ListNode* mergeTwoLists_better(ListNode* list1, ListNode* list2) {
        // base cases
        if(!list1) return list2;
        if(!list2) return list1;
        
        // chota element choose karte hai
        if(list1->val <= list2->val) {
            list1->next = mergeTwoLists_better(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists_better(list1, list2->next);
            return list2;
        }
    }
    
    // Optimal - Iterative approach O(n+m) time, O(1) space
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(0); // dummy node
        ListNode* current = dummy;
        
        // dono lists compare karte hai
        while(list1 && list2) {
            if(list1->val <= list2->val) {
                current->next = list1;
                list1 = list1->next;
            } else {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }
        
        // remaining nodes attach karte hai
        if(list1) current->next = list1;
        if(list2) current->next = list2;
        
        ListNode* result = dummy->next;
        delete dummy; // dummy node delete karte hai
        return result;
    }
};

// 18. Linked List Cycle - LinkedList
class Solution18 {
public:
    // Brute Force - Hash set O(n) time, O(n) space
    bool hasCycle_bruteforce(ListNode *head) {
        unordered_set<ListNode*> visited;
        ListNode* current = head;
        
        while(current) {
            // agar node pehle visit ki hai
            if(visited.find(current) != visited.end()) {
                return true;
            }
            visited.insert(current);
            current = current->next;
        }
        
        return false;
    }
    
    // Better - Mark visited nodes O(n) time, O(1) space (but modifies values)
    bool hasCycle_better(ListNode *head) {
        ListNode* current = head;
        const int VISITED = INT_MAX; // visited ka marker
        
        while(current) {
            // agar pehle se visited hai
            if(current->val == VISITED) {
                return true;
            }
            
            current->val = VISITED; // mark as visited
            current = current->next;
        }
        
        return false;
    }
    
    // Optimal - Floyd's Cycle Detection (Two pointers) O(n) time, O(1) space
    bool hasCycle(ListNode *head) {
        if(!head || !head->next) return false;
        
        ListNode* slow = head; // turtle - 1 step
        ListNode* fast = head; // rabbit - 2 steps
        
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            // agar slow aur fast mil gaye to cycle hai
            if(slow == fast) {
                return true;
            }
        }
        
        return false;
    }
};

// 19. Remove Nth Node From End of List - LinkedList
class Solution19 {
public:
    // Brute Force - Two pass O(n) time, O(1) space
    ListNode* removeNthFromEnd_bruteforce(ListNode* head, int n) {
        // first pass: length calculate karte hai
        int length = 0;
        ListNode* current = head;
        while(current) {
            length++;
            current = current->next;
        }
        
        // special case: first node remove karna hai
        if(n == length) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        
        // second pass: target node tak jaate hai
        current = head;
        for(int i = 0; i < length - n - 1; i++) {
            current = current->next;
        }
        
        // target node remove karte hai
        ListNode* nodeToRemove = current->next;
        current->next = current->next->next;
        delete nodeToRemove;
        
        return head;
    }
    
    // Better - Using array O(n) time, O(n) space
    ListNode* removeNthFromEnd_better(ListNode* head, int n) {
        vector<ListNode*> nodes;
        ListNode* current = head;
        
        // sab nodes array mein store karte hai
        while(current) {
            nodes.push_back(current);
            current = current->next;
        }
        
        int length = nodes.size();
        
        // first node remove karna hai
        if(n == length) {
            ListNode* newHead = head->next;
            delete head;
            return newHead;
        }
        
        // target index calculate karte hai
        int targetIndex = length - n;
        ListNode* nodeToRemove = nodes[targetIndex];
        nodes[targetIndex - 1]->next = nodeToRemove->next;
        delete nodeToRemove;
        
        return head;
    }
    
    // Optimal - One pass with two pointers O(n) time, O(1) space
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode* first = dummy;
        ListNode* second = dummy;
        
        // first pointer ko n+1 steps aage move karte hai
        for(int i = 0; i <= n; i++) {
            first = first->next;
        }
        
        // dono pointers ko end tak move karte hai
        while(first) {
            first = first->next;
            second = second->next;
        }
        
        // target node remove karte hai
        ListNode* nodeToRemove = second->next;
        second->next = second->next->next;
        delete nodeToRemove;
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

// 20. Middle of the Linked List - LinkedList
class Solution20 {
public:
    // Brute Force - Count then traverse O(n) time, O(1) space
    ListNode* middleNode_bruteforce(ListNode* head) {
        // first pass: length count karte hai
        int length = 0;
        ListNode* current = head;
        while(current) {
            length++;
            current = current->next;
        }
        
        // middle index calculate karte hai
        int middleIndex = length / 2;
        
        // second pass: middle tak jaate hai
        current = head;
        for(int i = 0; i < middleIndex; i++) {
            current = current->next;
        }
        
        return current;
    }
    
    // Better - Using array O(n) time, O(n) space
    ListNode* middleNode_better(ListNode* head) {
        vector<ListNode*> nodes;
        ListNode* current = head;
        
        // sab nodes array mein store karte hai
        while(current) {
            nodes.push_back(current);
            current = current->next;
        }
        
        // middle index return karte hai
        return nodes[nodes.size() / 2];
    }
    
    // Optimal - Two pointers (Slow and Fast) O(n) time, O(1) space
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head; // 1 step
        ListNode* fast = head; // 2 steps
        
        // fast end tak pahuche ya uske aage
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // jab fast end pe hoga, slow middle pe hoga
        return slow;
    }
};