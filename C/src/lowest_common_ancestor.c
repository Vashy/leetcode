/* 236. Lowest Common Ancestor of a Binary Tree
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
 *
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 * Constraints:
 *
 *  The number of nodes in the tree is in the range [2, 105].
 *  - -10^9 <= Node.val <= 10^9
 *  - All Node.val are unique.
 *  - p != q
 *  - p and q will exist in the tree.
*/

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void tree_node_init(TreeNode* tree, int val)
{
    assert(tree != NULL);
    const int ONE_BILLION = 1000000000;
    assert(val >= -ONE_BILLION && val <= ONE_BILLION);
    tree->val = val;
    tree->left = NULL;
    tree->right = NULL;
}

void print_tree(TreeNode* root)
{
    if (root == NULL)
        return;

    printf("%d ", root->val);
    print_tree(root->left);
    print_tree(root->right);
}

TreeNode* lowest_common_ancestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    assert(p != NULL && q != NULL);

    if (root == NULL) return NULL;
    if (root == p) return p;
    if (root == q) return q;

    TreeNode* left = lowest_common_ancestor(root->left, p, q);
    TreeNode* right = lowest_common_ancestor(root->right, p, q);

    if (left && right) return root;

    if (left) return left;
    if (right) return right;

    return NULL;
}

int main(int argc, char** argv)
{

    /*
       1
     2   3
    4 5 6 7
    */
    TreeNode root;
    TreeNode left;
    TreeNode right;
    TreeNode left_left;
    TreeNode left_right;
    TreeNode right_left;
    TreeNode right_right;
    tree_node_init(&root, 1);
    tree_node_init(&left, 2);
    tree_node_init(&right, 3);
    tree_node_init(&left_left, 4);
    tree_node_init(&left_right, 5);
    tree_node_init(&right_left, 6);
    tree_node_init(&right_right, 7);
    root.left = &left;
    root.right = &right;
    root.left->left = &left_left;
    root.left->right = &left_right;
    root.right->left = &right_left;
    root.right->right = &right_right;

    TreeNode* lca_left = lowest_common_ancestor(&root, &left_left, &left_right);
    assert(lca_left == &left);

    TreeNode* lca_right = lowest_common_ancestor(&root, &right_left, &right_right);
    assert(lca_right == &right);

    TreeNode* lca_root = lowest_common_ancestor(&root, &left_left, &right_right);
    assert(lca_root == &root);

    return 0;
}
