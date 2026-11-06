#include "Solution.cpp"

void printList(ListNode* head);

void printVector(vector<vector<string>> vec) {
    for (const auto& row : vec) {
        for (const auto& str : row) {
            cout << str << " \n";
        }
        cout << "==================\n";
    }
}

int main() {
    printVector((new Solution)->solveNQueens(5));
    return 0;
}


void printList(ListNode* head) {
    ListNode* current = head;

    while (current != nullptr) {
        cout << current->val;

        if (current->next != nullptr)
            cout << " -> ";

        current = current->next;
    }

    cout << endl;
}