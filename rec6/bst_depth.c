#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDepth(struct TreeNode* root)
{
    int depthL = -1;
    int depthR = -1;
    if (root == NULL){
        return -1;
    }
    if (root->right != NULL){
        depthR = maxDepth(root->right);
    }
    if (root->left != NULL){
        depthL = maxDepth(root->left);
    }
    if(depthL<depthR){
        return depthR +1;
    }
    return depthL + 1;
}

int minDepth_helper(struct TreeNode* node)
{
    
    int depthL = 0;
    int depthR = 0;
    
    if(node == NULL){
        return -1;
    }
    if (node->right == NULL && node->left == NULL){
        return 0;
    }
    
    if (node->right == NULL && node->left != NULL){
        
        return maxDepth(node->left) +1;
    }
    if (node->right != NULL && node->left == NULL){
        return maxDepth(node->right) +1;
    }

    if (node->right != NULL){
        depthR = maxDepth(node->right)+1;
    }
    if (node->left != NULL){
        depthL = maxDepth(node->left)+1;
    }
    printf("\ndepth at this node%d: L%d, R%d\n",node->val,depthL,depthR);
    if(depthL<depthR){
        return depthL;
    }
    return depthR;


    
}
int minDepth(struct TreeNode* root){
    if(root == NULL){
        return -1;
    }
    if(root->left == NULL && root->right == NULL){
        return 0;
    }
    int l = minDepth_helper(root->left);
    int r = minDepth_helper(root->right);
     if(root->left == NULL){
        return r;
    }
    if(root->right == NULL){
        return l+1;
    }
    if (l<r){
        return l+1;
    }
    return r+1;
}

struct TreeNode* newNode(int val){
    struct TreeNode *n = malloc(sizeof(struct TreeNode));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int main(void)
{
    
    //test 1: Empty Tree
    printf("\nTest1: Empty Tree....\n");
    printf("Max Depth:\nExpected: -1\nActual: %d\n\n", maxDepth(NULL));
    printf("Min Depth:\nExpected: -1\nActual: %d\n\n", minDepth(NULL));
    
    //  1
    //2    

    struct TreeNode *root = newNode(20);

    //test 2: Tree with only a root node
    printf("\nTest2....\n");
    printf("Max Depth:\nExpected: 0\nActual: %d\n\n", maxDepth(root));
    printf("Min Depth:\nExpected: 0\nActual: %d\n\n", minDepth(root));
    

    struct TreeNode *node1 = newNode(18);
    root->left = node1;

    struct TreeNode *node2 = newNode(16);
    node1->left = node2;

    struct TreeNode *node3 = newNode(14);
    node2->left = node3;

    struct TreeNode *node4 = newNode(12);
    node3->left = node4;

    //test 3:
    //            20
    //         18
    //      16
    //   14
    //12
    printf("\nTest3....\n");
    printf("Max Depth:\nExpected: 4\nActual: %d\n\n", maxDepth(root));
    printf("Min Depth:\nExpected: 4\nActual: %d\n\n", minDepth(root));

    //test 4:
    //            20
    //         18    22
    //      16
    //   14
    //12
    struct TreeNode *node5 = newNode(22);
    root->right = node5;
    printf("\nTest4....\n");
    printf("Max Depth:\nExpected: 4\nActual: %d\n\n", maxDepth(root));
    printf("Min Depth:\nExpected: 1\nActual: %d\n\n", minDepth(root));


    //test 5:
    //            20
    //         18    22
    //      16    21    26 
    //   14                30
    //12
    struct TreeNode *node6 = newNode(21);
    node5->left = node6;
    struct TreeNode *node7 = newNode(26);
    node5->right = node7;
    struct TreeNode *node8 = newNode(30);
    node7->right = node8;
    printf("\nTest5....\n");
    printf("Max Depth:\nExpected: 4\nActual: %d\n\n", maxDepth(root));
    printf("Min Depth:\nExpected: 2\nActual: %d\n\n", minDepth(root));

    free(root);
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    free(node6);
    free(node7);
    free(node8);

    /*
    struct TreeNode *node28i = newNode(28);
    struct TreeNode *node2i = newNode(2);
    node28i->left = node2i;
    struct TreeNode *node1i = newNode(1);
    node2i->left = node1i;
    struct TreeNode *node8i = newNode(8);
    node2i->left = node8i;
    struct TreeNode *node63i = newNode(63);
    struct TreeNode *node30i = newNode(30);
    struct TreeNode *node59i = newNode(59);
    struct TreeNode *node60i = newNode(60);
    struct TreeNode *node67i = newNode(67);
    node28i->right = node63i;
    node63i->left = node30i;
    node30i->right = node59i;
    node59i->right = node60i;
    node63i->right = node67i;
    //printf("Max Depth:\nExpected: 4\nActual??: %d\n\n", maxDepth(node28i));
    */





    return 0;
}