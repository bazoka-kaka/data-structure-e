#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define ll long long
#define INT_MIN -2000
 
typedef struct Node{
    ll data;
    struct Node *left, *right;
}node, Node;

node *getNewNode(ll data){
  node *newNode = (node*)malloc(sizeof(node));
  newNode->data = data;
  newNode->left = newNode->right = 0;
  return newNode;
}

node *insert(node *root, ll data){
  if(root == 0){
    return getNewNode(data);
  }else if(data < root->data){
    root->left = insert(root->left, data);
  }else if(data > root->data){
    root->right = insert(root->right, data);
  }
  return root;
}
 
bool isNodePresent(Node* root, Node* n){    
    if (root == 0) {
        return false;
    }
 
    if (root == n) {
        return true;
    }
 
    return isNodePresent(root->left, n) || isNodePresent(root->right, n);
}
 
ll findLevel(Node* root, Node* n, ll level){
    if (root == 0) {
        return INT_MIN;
    }
    if (root == n) {
        return level;
    }
                                                      
    int left = findLevel(root->left, n, level + 1);
    if (left != INT_MIN) {
        return left;
    }
    return findLevel(root->right, n, level + 1);
}

Node* findLCA(Node* root, Node* x, Node* y){
 
    if (root == 0) {
        return 0;
    }
 
 
    if (root == x || root == y) {
        return root;
    }
 
    Node* left = findLCA(root->left, x, y);
    Node* right = findLCA(root->right, x, y);
    if (left && right) {
        return root;
    }
 
    
    if (left) {
        return left;
    }

    if (right) {
        return right;
    }
    return 0;
}

int findDistance(Node* root, Node* x, Node* y){
    Node* lca = 0;
    if (isNodePresent(root, y) && isNodePresent(root, x)) {
        lca = findLCA(root, x, y);
    }
    else {
        return INT_MIN;
    }
    return findLevel(lca, x, 0) + findLevel(lca, y, 0);
}

node *bst_search(node *root, ll data){
  if(root == 0) return 0;
  else if(root->data == data) return root;
  if(data < root->data) return bst_search(root->left, data);
  if(data > root->data) return bst_search(root->right, data);
  return root;
}
 
int main(){
     Node *root = 0;
     int n, q;
     scanf("%d %d", &n, &q);
     while(n--){
       ll temp;
       scanf("%lld", &temp);
       root = insert(root, temp);
     }
    while(q--){
      ll a, b;
      scanf("%lld %lld", &a, &b);
      node *root_a = bst_search(root, a);
      node *root_b = bst_search(root, b);
      ll ans = findDistance(root, root_a, root_b);
      printf("%lld\n", ans);
    }
 
    return 0;
}
