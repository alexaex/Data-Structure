#include "tree.h"

container::BT_Node* container::create_BT(datatype data, BT_Node* left, BT_Node* right) {
    auto root = new BT_Node(data);
    root->left = left, root->right = right;
    return root;
}


void container::pre_order(BT root) {
    if (root == nullptr)
        return;
    printf("%d ", root->data);
    if (root->left)
        printf("left child:%d ", root->left->data);
    else
        printf("left child:NULL ");
    if (root->right)
        printf("right child:%d ", root->right->data);
    else
        printf("right child:NULL ");
    printf("\n");
    pre_order(root->left);
    pre_order(root->right);
}

void container::mid_order(BT root) {
    if (root == nullptr)
        return;

    if (root->left)
        printf("left child:%d ", root->left->data);
    else
        printf("left child:NULL ");
    printf("%d ", root->data);
    if (root->right)
        printf("right child:%d ", root->right->data);
    else
        printf("right child:NULL ");
    printf("\n");
    mid_order(root->left);
    mid_order(root->right);
}

void container::post_order(BT root) {
    if (root == nullptr)
        return;

    if (root->left)
        printf("left child:%d ", root->left->data);
    else
        printf("left child:NULL ");
    if (root->right)
        printf("right child:%d ", root->right->data);
    else
        printf("right child:NULL ");
    printf("%d ", root->data);
    printf("\n");

    mid_order(root->left);
    mid_order(root->right);
}

void container::mid_order_with_stack(BT root) {
    std::stack<BT> stk;
    while (root || !stk.empty()) {
        while (root != nullptr)
        {
            stk.push(root);
            root = root->left;
        }
        if (!stk.empty()) {
            auto cur = stk.top();
            stk.pop();
            printf("%d ", cur->data);
            root = cur->right;
        }
    }
}


void container::pre_order_with_stack(BT root) {
    std::stack<BT> stk;
    while (root || !stk.empty()) {
        while (root != nullptr) {
            printf("%d ", root->data);
            stk.push(root);
            root = root->left;
        }
        if (!stk.empty()) {
            auto cur = stk.top();
            stk.pop();
            root = cur->right;
        }
    }
}

template<typename _T>
void container::A<_T>::update(_T val) {
    data = val;
}

template<typename _T>
_T& container::A<_T>::get_data() const {
    return this->data;
}


