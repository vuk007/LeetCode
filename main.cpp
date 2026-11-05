#include "Solution.cpp"

void printList(ListNode* head);

int main()
{

    vector<int> nums {2,2,1,1};

    auto matrix = (new Solution)->permuteUnique(nums);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
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