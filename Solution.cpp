//
// Created by vuk00 on 11/5/2026.
//
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {};
};
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 0)return 0;
        int sum = 0 , curr$sum = 0;
        for (int i = 0 ; i < nums.size() ; i++ ) {
            curr$sum = nums[i]+curr$sum;
            curr$sum = max(nums[i] , curr$sum);
            sum = max(sum , curr$sum);
        }
        return sum;
    }
    int reverse(int x) {
        string result = "";
        string x$string = to_string(x);
        if(x<0) {
            result+="-";
            x$string = x$string.substr(1);
        }
        if(x$string.size() == 1)return x;
        for(int i = x$string.size()-1; i>=0 ; i--) {
            result += x$string[i];
        }
        try {

            return stoi(result);
        }catch (const out_of_range&){return 0;}
    }
    int reverse2 (int x) {
        bool negative = false;
        if (x < 0){
            negative = true;
            x*=-1;
        }
        int res = 0;
        for(int i = 0 ; i < 10 ; i++){
            if(x == 0) break;
            res *=10;
            res += x%10;
            x=x/10;
        }
        if (negative)res *= -1;
        return res;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* curr = head, *con_node = nullptr;
        while (curr) {
            if(n == 0){
                con_node = head;
            }
            n--;
            if(curr -> next == nullptr ){
                if(!con_node)return head->next;
                con_node->next = (con_node->next)->next;
                break;
            }
            curr = curr->next;
            if (con_node){
                con_node = con_node->next;
            }

        }
        return head;
    }
    double myPow(double x, int n) {
        if(x == 0)return 0;
        if(x == 1 || n == 0)return 1;
        double res = 1;int sgn = 1;
        if(n < 0)sgn = -1;
        while(n * sgn != 1) {
            if(n % 2 == 0) {
                n = n/2;
                x*=x;
            }else {
                n-= sgn;
                res *= x;
            }
        }
        res *= x;
        if(sgn == -1) res = 1/res;
        return res;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *res = nullptr , *curr = nullptr;
        int val1 = 0, val2 = 0, carry = 0;
        while (l1 != nullptr || l2 != nullptr) {
            val2 = val1 = 0;
            if(l1) {
                val1 = l1->val;
                l1 = l1->next;
            }
            if(l2) {
                val2 = l2->val;
                l2=l2->next;
            }
            val1 = val1 + val2 + carry;
            carry = 0;
            if(val1 >= 10) {
                carry = 1;
                val1 %= 10;
            }
            if (!curr)
                res = curr = new ListNode(val1);
            else {
                curr->next = new ListNode(val1);
                curr = curr->next;
            }
        }
        if (carry == 1) {
            curr->next = new ListNode(1);

        }
        return res;
    }
    int calculate(string s) {
        long long val = 0;
        int res = 0 , sgn = 1; // 1 plus , -1 minus
        stack<long long> val_stack;
        stack<int> sgn_stack;
        for ( char next : s) {
            if( next == ' ')continue;
            //skip whitespace
            else if( next<='9' && next>='0')val = val*10 + next - '0';
            // if  its digit calculate value
            else if( next == '+') {
                res = res + val * sgn;
                val = 0;
                sgn = 1;
            }
            else if (next == '-') {
                res = res + val*sgn;
                val = 0;
                sgn = -1;
            }
            else if ( next == '(') {
                val_stack.push(res);
                sgn_stack.push(sgn);
                val = 0;
                sgn = 1;
                res = 0;
            }
            else if ( next == ')') {
                res = res + val*sgn;
                res = val_stack.top() + sgn_stack.top() * res;
                val_stack.pop(); sgn_stack.pop();
                val = 0; sgn = 1;
            }
        }
        res = res + val*sgn;
        return  res;
    }
    int calculate2(string s) {
        //adding, mul , div  without brackets
        long long val = 0;
        int op = 1; // mnozenje -> 1 , deljenje -> -1
        int res = 1;
        stack<int> res_stack;
        for ( char next : s) {
            if( next == ' ')continue;
            else if ( next <= '9' && next >='0') {
                val = val*10 + next - '0';
            }
            else if ( next == '*' ) {
                res = op == 1 ? res * val : res / val;
                val = 0;
                op = 1;
            }
            else if ( next == '/') {
                res = op == 1 ? res * val : res / val;
                val = 0;
                op = -1;
            }
            else if ( next == '+') {
                res = op == 1 ? res * val : res / val;
                if(res)res_stack.push(res);
                op = 1;
                res = 1;
                val  = 0;
            } else if (next == '-') {
                res = op == 1 ? res * val : res / val;
                if(res)res_stack.push(res);
                op = 1;
                res = -1;
                val = 0;
            }
        }
        res = op == 1 ? res * val : res / val;
        while (!res_stack.empty()) {
            res += res_stack.top();
            res_stack.pop();
        }
        return res;
    }
    int maxArea(vector<int>& height) {
        int left = 0 ,right=height.size() - 1;
        int res = 0 ;
        int volume , distance = right;
        while ( left < right ) {
            volume = min(height[left] , height[right]) * distance;
            res = res < volume ? volume : res;
            distance--;
            if(height[left] < height[right]) {
                left++;
            }else {
                right--;
            }
        }
        return res;
    }

    string intToRoman(int num) {
        //vector<pair<int,string>>
        map<int , string , std::greater<int>> roman_numbers =
        {
            {1000, "M"}, {900, "CM"},
            {500, "D"}, {400, "CD"},
            {100, "C"},{90, "XC"},
            {50, "L"},   {40, "XL"},
            {10, "X"},   {9, "IX"},
            {5, "V"},    {4, "IV"},
            {1, "I"}
        };
        string res = "";
        for( auto sym  : roman_numbers) {
            while ( sym.first <= num) {
                res += sym.second;
                num -=sym.first;
            }
        }
        return res;
    }

    vector<vector<int>> permute3(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> curr;
        perms(res,nums,0);
        return res;
    }

    vector<vector<int>> permute2(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() == 1) {
            res.push_back({nums[0]});
            return res;
        }
        vector<int> remaining_nums;
        vector<vector<int>>second;
        for(int i = 0 ; i < nums.size() ; i++) {
            remaining_nums = nums;
            int n = nums[i];
            remaining_nums.erase(remaining_nums.begin()+i);
            second = permute2(remaining_nums);
            for(auto p : second) {
                p.push_back(n);
                res.push_back(p);
            }
        }
        return res;
    }

    void perms (vector<vector<int>>& res , vector<int>& nums , int lvl ) {


        if (lvl == nums.size() - 1) {
            res.push_back(nums);
            return;
        }
        perms(res, nums , lvl+1);
        for (int i = lvl ; i < nums.size() ; i++) {
            if(nums[lvl] != nums[i] ) {
                swap(nums[i] , nums[lvl]);
                perms(res , nums , lvl+1);
                swap(nums[i] , nums[lvl]);
            }

        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        perms(res , nums , 0);
        return res;
    }


};