#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (a)

int balance;

typedef struct _TreeNode
{
    int fp;
    struct _TreeNode* left;
    struct _TreeNode* right;
}TreeNode;


int Height(TreeNode *node);
int breakingNode(TreeNode *node);
TreeNode* new_node(int key);
TreeNode* insert_node(TreeNode **node, int key);
void preorder(FILE *file, TreeNode *root);
void inorder(FILE *file, TreeNode *root);


int Height(TreeNode *node)
{
    int height = 0;
    if(node == NULL)
        return 0;
    else if(node != NULL)
        height = 1 + MAX(Height(node->left), Height(node->right));

    return height;
}

int breakingNode(TreeNode *node)
{
    if(node == NULL)
        return 0;
    
    return Height(node->left) - Height(node->right);
}


TreeNode* new_node(int key)
{
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->fp = key;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode **node, int key)
{
    if((*node) == NULL)
        (*node) = new_node(key);
    if(key < (*node)->fp)
        (*node)->left = insert_node(&((*node)->left), key);
    else if(key > (*node)->fp)
        (*node)->right = insert_node(&((*node)->right), key);

    balance = breakingNode(*node);
    return *node;
}

void preorder(FILE *file, TreeNode *root)
{
    if(root)
    {
        fprintf(file, "%d ", root->fp);
        preorder(file, root->left);
        preorder(file, root->right);
    }
}

void inorder(FILE *file, TreeNode *root)
{
    if(root)
    {
        inorder(file, root->left);
        fprintf(file, "%d ", root->fp);
        inorder(file, root->right);
        
    }
}

int main()
{
    TreeNode *root = NULL;
    FILE *fp, *fp2;
    char insert[10];
    int num;
    

    fp = fopen("AVL.in.", "r");  // 파일 읽기
    int ret;
    fp2 = fopen("AVL.out.", "w"); // 파일 쓰기

    if(fp==NULL)
    {
        printf("file open fail\n");
        exit(0);
    }
    while(fscanf(fp, "%s%d", insert, &num) != EOF)
    {
        insert_node(&root, num);

        fprintf(fp2, "I ");
        inorder(fp2, root);
        fprintf(fp2, "\nP ");
        preorder(fp2, root);
        fprintf(fp2, "\nBN ");
        fprintf(fp2, "%d", balance);
        fprintf(fp2, "\n\n");

        if(ret==EOF)
            break;
    }
    

    fclose(fp);
    fclose(fp2);

    return 0;
}