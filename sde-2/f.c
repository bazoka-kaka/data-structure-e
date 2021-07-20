#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define ll long long unsigned

/**
 * Node structure and
 * uniqueBST structure
 */

typedef struct bstnode_t {
    ll key;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    ll _size;
} BST;

/**
 * !!! WARNING UTILITY FUNCTION !!!
 * Recognized by prefix "__bst__"
 * ---------------------------------------------
 * Note that you better never access these functions, 
 * unless you need to modify or you know how these functions work.
 */

BSTNode* __bst__createNode(ll value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, ll value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, ll a, ll b) {    
    while (root != NULL) {
      if(root->right && root->left){
          if (root->key < a && root->key < b)
              return __bst__search(root->right, a, b);
          else if (root->key > a && root->key > b)
                return __bst__search(root->left, a, b);
          else if((root->left)->key == a && (root->right)->key == b) return root;
          else if(root->key == a && root->key < b) return __bst__search(root->right, a, b);
          else if(root->key == a && root->key > b) return __bst__search(root->left, a, b);
          else if(root->key == b && root->key < a) return __bst__search(root->right, a, b);
          else if(root->key == b && root->key > a) return __bst__search(root->left, a, b);
          return root;
      }
      else if(!root->right && root->left){
        if(root->key == b && (root->left)->key == a) return root;
        return __bst__search(root->left, a, b);
      }else if(!root->left && root->right){
        if(root->key == a && (root->right)->key == b) return root;
        return __bst__search(root->right, a, b);
      }else{
        return 0;
      }
    }
    return 0;
}

void __bst__inorder(BSTNode *root) {
    if (root) {
        __bst__inorder(root->left);
        printf("%llu ", root->key);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root) {
    if (root) {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%llu ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%llu ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

/**
 * PRIMARY FUNCTION
 * ---------------------------
 * Accessible and safe to use.
 */

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

ll bst_find(BST *bst, ll a, ll b) {
    BSTNode *temp = __bst__search(bst->_root, a, b);
    if (temp == NULL)
        return 0;
    
    if (temp)
        return temp->key;
    else
        return 0;
}

void bst_insert(BST *bst, ll value) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
}
/**
 * Binary search tree traversal
 * - Inorder
 * - Postorder
 * - Preorder
 */

void bst_inorder(BST *bst) {
    __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst) {
    __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst) {
    __bst__preorder(bst->_root);
}

 /*
int main()
{
    BST set;
    bst_init(&set);

    bst_insert(&set, 6);
    bst_insert(&set, 1);
    bst_insert(&set, 8);
    bst_insert(&set, 12);
    bst_insert(&set, 1);
    bst_insert(&set, 3);
    bst_insert(&set, 7);

    bst_inorder(&set);
    puts("");

    bst_remove(&set, 8);
    bst_remove(&set, 6);
    bst_inorder(&set);
    puts("");
    
    return 0;
}
*/

int main(){
  ll t;
  BST set;
  bst_init(&set);
  scanf("%llu", &t);
  while(t--){
    int n;
    scanf("%d", &n);    
    if(n == 1){
      ll a;
      scanf("%llu", &a);
      //insert the new kid
      bst_insert(&set, a);
    }else{
      ll a, b;
      scanf("%llu %llu", &a, &b);
      //search the boss
      ll ans = bst_find(&set, a, b);
      ans? printf("%llu\n", ans): printf("Maaf, Data Tidak Valid.\n");
    }
  }
  //bst_inorder(&set);
  return 0;
}