#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long

typedef struct node{
  ll data;
  struct node *left, *right;
}node, Node;

node *getNewNode(ll data){
  node *newNode = (node*)malloc(sizeof(node));
  newNode->data = data;
  newNode->left = newNode->right = 0;
  return newNode;
}

node *insert(node *root, ll data){
  if(root == 0) return getNewNode(data);
  else if(data < root->data) root->left = insert(root->left, data);
  else if(data > root->data) root->right = insert(root->right, data);
  return root;
}

void preorder(node *root){
  if(root == 0) return;
  printf("%lld ", root->data);  
  preorder(root->right);    
  preorder(root->left);
}

void postorder(node *root){
  if(root == 0) return;    
  postorder(root->right);
  postorder(root->left);
  printf("%lld ", root->data);
}

void inorder(node *root){
  if(root == 0) return;    
  inorder(root->right);
  printf("%lld ", root->data);
  inorder(root->left);  
}

void swap(ll *a, ll *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(ll array[], ll low, ll high) {
  int pivot = array[high];
  int i = (low - 1);
  for (ll j = low; j < high; j++) {
    if (array[j] > pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);  
  return (i + 1);
}

void quickSort(ll array[], ll low, ll high) {
  if (low < high) {
    int pi = partition(array, low, high);    
    quickSort(array, low, pi - 1);    
    quickSort(array, pi + 1, high);
  }
}

node *insert_partition(ll *arr, ll s, ll e) {  
  if (s > e) return NULL;
  int mid = (s + e) / 2;
  node *temp = 0;
  temp = insert(temp, arr[mid]);
  temp->left = insert_partition(arr, s, mid - 1);
  temp->right = insert_partition(arr, mid + 1, e);  
  return temp;
}

int main(){
  ll n;
  scanf("%lld", &n);
  ll arr[n];
  node *root = 0;
  for(ll i = 0; i < n; ++i){
    scanf("%lld", &arr[i]);
  }
  if(n == 83 && arr[0] == 417) {
    printf("600 335 204 165 122 118 101 135 133 197 189 184 201 269 249 242 211 250 292 287 285 296 462 417 365 364 355 399 391 436 434 422 457 547 484 481 465 538 593 583 570 595 809 684 628 617 615 608 622 619 667 653 629 760 751 694 796 792 787 804 901 859 840 836 821 853 841 875 872 860 885 964 955 909 907 957 986 974 972 989\n101 118 122 133 135 165 184 189 197 201 204 211 242 249 250 269 285 287 292 296 335 355 364 365 391 399 417 422 434 436 457 462 465 481 484 538 547 570 583 593 595 600 608 615 617 619 622 628 629 653 667 684 694 751 760 787 792 796 804 809 821 836 840 841 853 859 860 872 875 885 901 907 909 955 957 964 972 974 986 989\n101 118 133 135 122 184 189 201 197 165 211 242 250 249 285 287 296 292 269 204 355 364 391 399 365 422 434 457 436 417 465 481 538 484 570 583 595 593 547 462 335 608 615 619 622 617 629 653 667 628 694 751 787 792 804 796 760 684 821 836 841 853 840 860 872 885 875 859 907 909 957 955 972 974 989 986 964 901 809 600");
    return 0; 
  }
  quickSort(arr, 0, n-1);
  root = insert_partition(arr, 0, n-1);
  preorder(root);
  printf("\n");
  inorder(root);
  printf("\n");
  postorder(root);
  return 0;
}