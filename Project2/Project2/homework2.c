#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 根据中序和后序遍历结果构建二叉树
TreeNode* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd || postStart > postEnd) {
        return NULL;
    }
    // 后序遍历的最后一个元素是根节点的值
    int rootVal = postorder[postEnd];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = rootVal;
    root->left = root->right = NULL;

    // 在中序遍历中找到根节点的位置
    int inRootIndex;
    for (inRootIndex = inStart; inRootIndex <= inEnd; inRootIndex++) {
        if (inorder[inRootIndex] == rootVal) {
            break;
        }
    }

    // 计算左子树和右子树的长度
    int leftSubtreeLen = inRootIndex - inStart;
    int rightSubtreeLen = inEnd - inRootIndex;

    // 递归构建左子树
    root->left = buildTree(inorder, postorder, inStart, inRootIndex - 1, postStart, postStart + leftSubtreeLen - 1);
    // 递归构建右子树
    root->right = buildTree(inorder, postorder, inRootIndex + 1, inEnd, postStart + leftSubtreeLen, postEnd - 1);

    return root;
}

// 先序遍历二叉树
void preorderTraversal(TreeNode* root) {
    if (root) {
        printf("%d ", root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

int main() {
    int inorder[] = { 9, 3, 15, 20, 7 };
    int postorder[] = { 9, 15, 7, 20, 3 };
    int n = sizeof(inorder) / sizeof(inorder[0]);

    TreeNode* root = buildTree(inorder, postorder, 0, n - 1, 0, n - 1);
    printf("先序序列: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}