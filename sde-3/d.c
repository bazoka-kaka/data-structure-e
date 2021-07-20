#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long
int c = 1;

typedef struct node{
  ll data, height, id;
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

node *getNewNode(ll data, ll id){
  node *newNode = (node*)malloc(sizeof(node));
  newNode->data = data;
  newNode->left = newNode->right = 0;
  newNode->height = 1;
  newNode->id = id;
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

node *insert(node *root, ll data, ll id){
  if(root == 0) return getNewNode(data, id);
  if(id < root->id) root->left = insert(root->left, data, id);
  else if(id > root->id) root->right = insert(root->right, data, id);
  else return root;
  //update heights
  root->height = max(height(root->left), height(root->right)) + 1;
  //balance
  int balance = getBalance(root);
  //if not balanced, there are 4 cases
  //left left case
  if(balance > 1 && id < root->left->id) return rightRotate(root);
  //right right case
  if(balance < -1 && id > root->right->id) return leftRotate(root);
  //left right case
  if(balance > 1 && id > root->left->id){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  //right left case
  if(balance < -1 && id < root->right->id){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  //return unchanged root
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
    root->id = c;
    c++;
    arrange(root->right);
  }
}

node *search(node *root, ll data){
  if(root == 0) return root;
  if(data < root->id) return search(root->left, data);
  else if(data > root->id) return search(root->right, data);
  return root;
}

ll find(node *root, ll data){
  node *temp = search(root, data);
  if(temp == 0) return 0;
  else if(temp->id == data) return temp->data;
  else return 0;
}

int main(){
  /*
    membuat semua id berurutan starting 1
    input:
    m - id
    n - harga
    bagian pertama selesai ketika 0 0
    note: jika id tidak urut output: ID harus urut lalu program dihentikan
    jika id produk tidak ada output: 
  */
  ll tmp = 0;
  ll ans = 0;
  bool t = 1;
  node *root = 0;
  while(1){
    ll id, harga;
    scanf("%lld %lld", &id, &harga);
    tmp++;
    if(id == 0 && harga == 0) break;    
    if(id != tmp){
      printf("ID harus urut\n");
      t = 0;
      break;
    }    
    root = insert(root, harga, id);
  }
  while(t){
    ll jml, id;
    scanf("%lld %lld", &jml, &id);
    if(jml == 0 && id == 0) break;        
    ll temp = find(root, id) * jml;
    if(temp == 0){
      printf("Maaf barang tidak tersedia\n");
      continue;
    }
    else ans += temp;
  }
  if(t)printf("%lld", ans);
  return 0;
}