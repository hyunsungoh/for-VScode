#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int num = 0;
int bn = 0;
int loop=0;

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
    int balance = 0;

    if((*node) == NULL)
        (*node) = new_node(key);
    if(key < (*node)->fp)
    {
        (*node)->left = insert_node(&((*node)->left), key);
        balance = breakingNode(*node);
        if(balance > 1 || balance < -1)
        {
            if(loop==0){
                bn = (*node)->fp;
                loop++;
            }
        }        
    }
        
    else if(key > (*node)->fp)
    {
        (*node)->right = insert_node(&((*node)->right), key);
        balance = breakingNode(*node);
        if(balance > 1 || balance < -1)
        {
            if(loop==0){
                bn = (*node)->fp;
                loop++;
            }
        }                            
    }
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
    char input[10];
    

    fp = fopen("AVL.in", "r");  // 파일 읽기
    fp2 = fopen("AVL.out", "w"); // 파일 쓰기

    if(fp==NULL)
    {
        printf("file open fail\n");
        exit(0);
    }
    while(fscanf(fp, "%s%d", input, &num) != EOF)
    {
        insert_node(&root, num);

        fprintf(fp2, "I ");
        inorder(fp2, root);
        fprintf(fp2, "\nP ");
        preorder(fp2, root);
        fprintf(fp2, "\nBN ");
        fprintf(fp2, "%d", bn);
        fprintf(fp2, "\n\n");

        loop=0;
    }

    fclose(fp);
    fclose(fp2);

    return 0;
}