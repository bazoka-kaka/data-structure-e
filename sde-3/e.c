#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long
#define MAX_ELE 16
int c = 0;


typedef struct node{
  ll data, height, index;
  struct node *left, *right;
}node, Node, *NodePtr;

ll height(node *root){
  if(root == 0) return 0;
  return root->height;
}

ll getBalance(node *root){
  if(root == 0) return 0;
  return height(root->left)-height(root->right);
}

node *getNewNode(ll data){
  node *newNode = (node*)malloc(sizeof(node));
  newNode->data = data;
  newNode->left = newNode->right = 0;
  newNode->height = 1;
  newNode->index = 0;
  return newNode;
}

int max(int a, ll b){
  return a > b? a: b;
}

/*
    y
  x
    t2
*/

node *rightRotate(node *y){
  node *x = y->left;
  node *t2 = x->right;
  //do the rotation
  x->right = y;
  y->left = t2;
  //update heights
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  //return the new root
  return x;
}

/*
    x
      y
    t2
*/

node *leftRotate(node *x){
  node *y = x->right;
  node *t2 = y->left;
  //do the rotation
  y->left = x;
  x->right = t2;
  //update heights
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  //return the new root
  return y;
}

node *insert(node *root, ll data){
  if(root == 0) return getNewNode(data);
  if(data < root->data) root->left = insert(root->left, data);
  else if(data > root->data) root->right = insert(root->right, data);
  else return root;
  //update heights
  root->height = max(height(root->left), height(root->right)) + 1;
  //balance
  int balance = getBalance(root);
  //if not balanced, there are 4 cases
  //left left case
  if(balance > 1 && data < root->left->data) return rightRotate(root);
  //right right case
  if(balance < -1 && data > root->right->data) return leftRotate(root);
  //left right case
  if(balance > 1 && data > root->left->data){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  //right left case
  if(balance < -1 && data < root->right->data){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  //return unchanged root
  return root;
}

node *search(node *root, ll data){
  if(root == 0) return root;
  if(data < root->data) return search(root->left, data);
  else if(data > root->data) return search(root->right, data);
  return root;
}

void preorder(node *root){
  if(root == 0) return;
  printf("%lld ", root->data);
  preorder(root->left);  
  preorder(root->right);
}

node *minValueNode(node *n){
  node *curr = n;
  while(curr->left != 0){
    curr = curr->left;
  }
  return curr;
}

node *deleteNode(node *root, ll data){
  if(root == 0) return root;
  if(data < root->data) root->left = deleteNode(root->left, data);
  else if(data > root->data) root->right = deleteNode(root->right, data);
  else{
    //no child
    if(root->left == 0 || root->right == 0){
      free(root);
      root = 0;
    }  
    //one child
    else if(root->left){
      node *temp = root;
      root = root->left;
      free(temp);
    }else if(root->right){
      node *temp = root;
      root = root->right;
      free(temp);
    }
    //two children
    else{
      node *temp = minValueNode(root->right);
      root->data = temp->data;
      root->right = deleteNode(root->right, temp->data);
    }
  }
  if(root == 0) return root;
  root->height = max(height(root->left), height(root->right)) + 1;
  int balance = getBalance(root);
  //left left
  if(balance > 1 && getBalance(root->left) >= 0){
    return rightRotate(root);
  }
  //right right
  if(balance < -1 && getBalance(root->right) < 0)
    return leftRotate(root);
  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
  
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }  
  return root;
}

void inorder(node *root){
  if(root == 0) return;
  inorder(root->left);
  printf("%lld ", root->data);
  inorder(root->right);
}

void postorder(node *root){
  if(root == 0) return;
  postorder(root->left);
  postorder(root->right);
  printf("%lld ", root->data);
}

void arrange(node *root){
  /*if(root == 0) return;
  arrange(root->left, i);
  root->index = (*i)++;
  arrange(root->right, i);
  */
  if(root){
    arrange(root->left);
    root->index = c;
    c++;
    arrange(root->right);
  }
}

ll find(node *root, ll data){
  node *temp = search(root, data);
  if(temp == 0) return -1;
  else if(temp->data == data) return temp->index;
  else return -1;
}

ll MAX_HD = 0;
ll sums[10000] = {0, };



void vertical_sums(node *tree, ll hd){    
    ll index = hd + MAX_HD / 2;

    if (tree == NULL) {
        return;
    }

    sums[index] += tree->data;

    if (tree->left != NULL) {
        vertical_sums(tree->left, hd - 1);
    }
    if (tree->right != NULL) {
        vertical_sums(tree->right, hd + 1);
    }
}


int main(){
  node *root = 0;
  int n, tt = 0;
  scanf("%d", &n);
  while(n--){
    char str[30];
    scanf("%s", str);
    ll data;
    if(str[0] == 'i'){
      scanf("%lld", &data);
      root = insert(root, data);
      tt++;      
    }else{
      MAX_HD = 10000;
      vertical_sums(root, 0);
      for (int i = 0; i < MAX_HD; i++){
        if(sums[i])printf("%lld ", sums[i]);
        sums[i] = 0;
      }
      printf("\n");
    }
  }        
  return 0;
}