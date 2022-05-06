#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int fp;
    struct node* left;
    struct node* right;
}TreeNode;


TreeNode* new_node(int key)
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->fp = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode *node,int key)
{
    if(node == NULL)
        return new_node(key);
    if(key < node->fp)
        node->left = insert_node(node->left, key);
    else if(key > node->fp)
        node->right = insert_node(node->right, key);

    return node;
}

void preorder(TreeNode *root)
{
    if(root)
    {
        printf("%d", root->fp);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TreeNode *root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d", root->fp);
        inorder(root->right);
        
    }
}

int main()
{
    TreeNode *root = NULL;
    FILE *fp, *fp2;
    int num1;
    int p ,i;
    

    fp = fopen("AVL.in.", "r");  // 파일 읽기
    if(fp==NULL)
    {
        printf("file open fail\n");
        exit(0);
    }
    while(1)
    {
        fscanf(fp, "%d", &num1);
    }


    fp2 = fopen("AVL.out.", "w");    // 파일 쓰기
    while(1)
    {
        fprintf(fp2, "I ");
        inorder(root);
        fprintf(fp2, "P ");
        preorder(root);
        fprintf(fp2, "BN ");
    }
    

    fclose(fp);
    fclose(fp2);

    return 0;


}