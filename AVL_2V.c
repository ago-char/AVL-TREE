// AvlTree improved version 2 code

#include <stdio.h>
#include <stdlib.h>

typedef struct AvlTree
{
     int key;
     int height;
     struct AvlTree *left, *right;
} node;

int height(node *N)
{
     if (!N)
          return 0;
     return N->height;
}

int balanceFactor(node *N)
{
     if (!N)
          return 0;
     return height(N->left) - height(N->right);
}

int max(int a, int b)
{
     return a > b ? a : b;
}

// this function will create new node and insert essential key and pointer also set the height of tree initially to be 1
node *newNode(int key)
{
     node *N = (node *)malloc(sizeof(node));
     N->key = key;
     N->left = NULL;
     N->right = NULL;
     N->height = 1; // initially height is set to be 1
     return N;
}

node *rightRotate(node *imb)
{
     // changinig place for rotation
     node *tree = imb->left;
     imb->left = tree->right;
     tree->right = imb;

     // updating height first of the node which is imbalanced and of the tree which is to be returned and note that this order is important
     imb->height = 1 + max(height(imb->left), height(imb->right));
     tree->height = 1 + max(height(tree->left), height(tree->right));

     // return new tree i.e the tree pointer will be the root for the tree which is right rotated
     return tree;
}

node *leftRotate(node *imb)
{
     // changinig place for rotation
     node *tree = imb->right;
     imb->right = tree->left;
     tree->left = imb;

     // updating height first of the node which is imbalanced and of the tree which is to be returned and note that this order is important
     imb->height = 1 + max(height(imb->left), height(imb->right));
     tree->height = 1 + max(height(tree->left), height(tree->right));

     // return new tree i.e the tree pointer will be the root for the tree which is right rotated
     return tree;
}

// this function will insert the key or node as general as the insertion in BST and also update height and checks the balanceFactor to rotate
node *insert(node *pointer, int key)
{
     // 1. Do the insertion as same on normal Binary Search Tree

     // if no tree (or subtree coz recursive function) make node and attach
     if (!pointer)
          return newNode(key);

     // move left if the value is less
     if (key < pointer->key)
          pointer->left = insert(pointer->left, key);

     // move right if the value is greater
     else if (key > pointer->key)
          pointer->right = insert(pointer->right, key);

     // return the same pointer if the value is duplicated
     else
          return pointer;

     // this portion of code will first apply for the leaf node i.e the node which is inserted newly it is because we have to track the nearest node from newly inserted node which balanceFactor is disturbed it is possible beacuse the function is recursive

     // 2. Update height and check balanceFactor to rotate left or right under 4 rotation techniques

     // update height of pointer(node)
     pointer->height = 1 + max(height(pointer->left), height(pointer->right));

     // find balanceFactor of the node
     int balance = balanceFactor(pointer);

     // 3. Apply rotation if the balanceFactor is disturbed

     // left left --> Apply rightRotation once
     if (balance > 1 && key < pointer->left->key)
          return rightRotate(pointer);

     // right right --> Apply leftRotation once
     if (balance < -1 && key > pointer->right->key)
          return leftRotate(pointer);

     // left right --> Apply left rotation to make rotaion type "left left" and then rotate right to balance the tree
     if (balance > 1 && key > pointer->left->key)
     {
          // first left rotate the left sub tree and attach to the main tree the rotate whole tree to the right
          pointer->left = leftRotate(pointer->left);
          return rightRotate(pointer);
     }

     // right left --> Apply right rotatioin to make rotation type "right right" and then rotate left to balance the tree
     if (balance < -1 && key < pointer->right->key)
     {
          // first right rotate the right sub tree and attach to the main tree then rotate whole tree to the left
          pointer->right = rightRotate(pointer->right);
          return leftRotate(pointer);
     }

     // return the same pointer if the node do not require rotation i.e for the node which balanceFactor is not disturbed
     return pointer;
}

// this function prints preOrder traversal of AvlTree
void preOrder(node *root)
{
     if (root)
     {
          printf("%d ", root->key);
          preOrder(root->left);
          preOrder(root->right);
     }
}

// main function to create BST which is also AvlTree

int main(int argc, char const *argv[])
{
     system("cls");

     node *root = NULL;
     int arr[] = {50, 40, 60, 30, 45, 55, 70, 65, 75, 80, 77, 20, 73, 72, 76};

     // insert elements of array one by one and view preOrder list
     for (int i = 0; i < 15; i++)
     {
          root = insert(root, arr[i]);
          printf("\n");
          preOrder(root);
     }

     return 0;
}
