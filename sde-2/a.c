#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll unsigned long long
int s=0;
int c=1;

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

node *search(node *root, ll data){
  while(root){
    if(data < root->data) root = root->left;
    else if(data > root->data) root = root->right;
    else return root;
  }
  return root;
}

ll find(node *root, ll data){
  node *temp = search(root, data);
  if(temp == 0) return -1;
  else if(temp->data == data) return temp->index;
  else return -1;
}

void arrange(node *root){
  /*if(root == 0) return;
  arrange(root->left, i);
  root->index = (*i)++;
  arrange(root->right, i);
  */
  if(root){
    arrange(root->left);
    root->index = c-1;
    c++;
    arrange(root->right);
  }
}

void print(node *root){
  if(root == 0) return;  
  print(root->left);
  printf("%lld ", root->index);
  print(root->right);
}

int main(){
  ll tt;
  scanf("%llu", &tt);
  node *root = 0;
  while(tt--){
    ll data, n;
    scanf("%llu %llu", &n, &data);
    if(n == 1){
      if(s == 1){
        s = 0;
      }
      root = insert(root, data);
    }else{     
       if(s == 0){
        c = 1;
        arrange(root);
        s = 1;
       }

      ll ans = find(root, data);
      ans != -1? printf("%llu\n", ans): printf("Gak ada ngab\n");
    }
  }
  //print(root);
  return 0;
}