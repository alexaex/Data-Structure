#ifndef CONTAINER_TREE_H
#define CONTAINER_TREE_H
#include "iostream"
#include <stack>
#include <queue>
#include <array>

namespace container {
    using datatype = int;

    //BINARY TREE NODE
    struct BT_Node {
        BT_Node* left;
        BT_Node* right;
        datatype data;

        BT_Node(datatype val) :data(val), left(nullptr), right(nullptr) {};

        BT_Node() :left(nullptr), right(nullptr) {};

    };

    //BINARY TREE
    using BT = BT_Node*;

    BT_Node* create_BT(datatype data, BT_Node* left, BT_Node* right);

    void pre_order(BT root);
    void mid_order(BT root);
    void post_order(BT root);

    void mid_order_with_stack(BT root);
    //void post_order_with_stack(BT root);
    void pre_order_with_stack(BT root);

    template<typename T>
    struct Huffman_Tree_Node {
        T data;
        int left, right;
        int weight;
        int idx;
    };

    template<typename T>
    inline bool operator<(const Huffman_Tree_Node<T>& self, const Huffman_Tree_Node<T>& other) {
        return other.weight < self.weight;
    }

    template<typename T, size_t capacity = 32>
    struct Huffman_Tree {
        Huffman_Tree_Node<T> root[capacity];
        size_t M = capacity;
        Huffman_Tree_Node<T>& operator[](int index) {
            return root[index];
        }
        const Huffman_Tree_Node<T>& operator[](int index)const {
            return root[index];
        }
    };

    template<typename T, size_t capacity, size_t M>
    static void generic_Huffman_Tree(Huffman_Tree<T, capacity>& HT, const std::array<T, M>& data, const std::array<int, M>weight) {
        int i;
        container::Huffman_Tree_Node<T> parent, lc, rc;
        std::priority_queue<container::Huffman_Tree_Node<T>> queue;
        for (i = 1; i <= M; i++) {
            HT[i].data = data[i - 1];
            HT[i].weight = weight[i - 1];
            HT[i].idx = i;
            HT[i].left = HT[i].right = -1;
            queue.push(HT[i]);
        }
        while (queue.size() > 1) {
            lc = queue.top(), queue.pop();
            rc = queue.top(), queue.pop();
            parent.weight = lc.weight + rc.weight;
            parent.idx = i;
            parent.left = lc.idx;
            parent.right = rc.idx;

            queue.push(parent);
            HT[i++] = parent;
        }
        HT[0] = queue.top();
        HT[0].idx = 0;
        queue.pop();
    }


    template<typename T, size_t capacity>
    static int Weighted_path_length(Huffman_Tree<T, capacity> root, int idx = 0, int depth = 0) {
        int res = 0;
        if (root[idx].left == -1 && root[idx].right == -1)
            return depth * root[idx].weight;
        res += (Weighted_path_length(root, root[idx].left, depth + 1) + Weighted_path_length(root, root[idx].right, depth + 1));
        return res;
    }


    template<typename T, size_t capacity = 32>
    using Array_Tree = T[capacity];
    /*
     *                     0
     *            1                 2
     *       3          4      5           6
     *      7  8     9    10 11  12     13    14
    */
    // if parent node's index is i, the left child node's is (2*i)+1 and right is 2*(i+1)

    template<typename T, size_t capacity = 32>
    inline void heap_adjust(Array_Tree<T, capacity>& tree, int cur, int n) {
        int i;
        int tmp = tree[cur];
        while (i = (2 * cur) + 1, i < n) {
            if (i + 1 < n && tree[i] < tree[i + 1]) i++;
            if (tree[i] <= tmp) break;
            tree[cur] = tree[i];
            cur = i;
        }
        tree[cur] = tmp;
    };


    template<typename T, size_t capacity = 32>
    inline void generic_heap(Array_Tree<T, capacity>& tree, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heap_adjust(tree, i, n);
    }

    template<typename T, size_t capacity = 32>
    inline void heap_push(Array_Tree<T, capacity>& heap, int& end, T key_value) {
        int cur, par;
        cur = end;
        end++;
        while (cur > 0) {
            par = (cur - 1) / 2;
            if (heap[par] >= key_value) break;
            heap[cur] = heap[par];
            cur = par;
        }
        heap[cur] = key_value;
    }

    template<typename T, size_t capacity = 32>
    inline T heap_pop(Array_Tree<T, capacity>& heap, int& end) {
        auto ret = heap[0];
        heap[0] = heap[end - 1];
        end--;
        heap_adjust(heap, 0, end);
        return ret;
    }




}

#endif //CONTAINER_TREE_H