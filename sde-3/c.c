#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll unsigned long long

typedef struct node{
  ll data, index;
  struct node *left, *right;
}node;

node *getNewNode(ll data){
  node *newNode = (node*)malloc(sizeof(node));
  newNode->data = data;
  newNode->index = 0;
  newNode->left = newNode->right = 0;
  return newNode;
}

node *insert(node *root, ll data){
  if(root == 0){
    root = getNewNode(data);
  }else if(data < root->data){
    root->left = insert(root->left, data);
  }else if(data > root->data){
    root->right = insert(root->right, data);
  }
  return root;
}

int height(struct node* node);
bool isBalanced(struct node* root)
{
    int lh;
    int rh;
  
    if (root == NULL)
        return 1;
  
    lh = height(root->left);
    rh = height(root->right);
  
    if (abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;
  
    return 0;
}
  
int max(ll a, ll b)
{
    return (a >= b) ? a : b;
}
  
int height(struct node* node)
{
    if (node == NULL)
        return 0;
  
    return 1 + max(height(node->left), height(node->right));
}
  
int main(){
    node *root = 0;
    ll t;
    scanf("%lld", &t);
    while(t--){
      ll n;
      scanf("%lld", &n);
      while(n--){
        ll temp;
        scanf("%lld", &temp);
        root = insert(root, temp);
      }
      bool ans = isBalanced(root);
      ans? printf("YES"): printf("NO");
      printf("\n");
      free(root);
      root = 0;
    }
    return 0;
}