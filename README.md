## Binary Search Tree (ABB - Árvore de Busca Binária)

This code implements the main functions of a binary search tree, which represents a family of ordered structures. The concept behind the BST code is in machine memory, decision systems, trajectories representations, ordination methods (such as the Heap Sort model), and much more.

Structure of the binary tree node:

```C
typedef struct btnode bintree;
struct btnode {
    int value;
    bintree *left;
    bintree *right;
};
```

In this code, it is possible to create a new BST, add new elements, search, remove and print them in the three possible ways (in order, post-order, and pre-order). The removal part considers the three following cases:

- First Case: the node does not have children;
- Second Case: node has one child;
- Third Case: node has two children.
