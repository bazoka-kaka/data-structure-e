#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long

typedef struct node{
  int data;
  struct node *next, *prev;
}node, Node, *NodePtr;

void push_back(node **a, node **e, int n){
  struct node *temp = (node*)malloc(sizeof(node));
  temp->data = n;
  temp->next = 0;
  temp->prev = *e;
  if(*e == 0){
    *a = temp;
    *e = temp;
    return;
  }
  node *temp1 = *e;
  temp1->next = temp;
  *e = temp;
}

void push_front(node **a, node **e, int n){
  struct node *temp = (node*)malloc(sizeof(node));
  temp->data = n;
  temp->next = *a;
  temp->prev = 0; 
  if(*a != 0){
    (*a)->prev = temp;
  }else{
    *e = temp;
  }
  *a = temp;
}

void putar(node **a, node **e){
  Node *temp = NULL;
  *e = *a;
  Node *curr = *a;
  while (curr != NULL){
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;            
    curr = curr->prev;
  }
     
  if(temp != NULL )
    *a = temp->prev;
  
}

bool is_empty(node *a){
  return a == 0;
}

void del_front(node **a, node **e){
  node *temp = *a;
  if(*a == 0) return;
  *a = temp->next;
  if(*a == 0){
    *e = 0;
    free(temp);
    return;
  }
  node *temp1 = *a;
  temp1->prev = 0;
  free(temp);
}

void del_back(node **a, node **e){
  node *temp = *e;
  if(*e == 0) return;
  if(*e == *a){
    *e = 0;
    *a = 0;
    free(temp);
    return;
  }
  node *temp1 = temp->prev;
  temp1->next = 0;
  *e = temp1;
  free(temp);
}

int main(){
  ll n;
  scanf("%lld", &n);
  node *a = 0, *e = 0;
  while(n--){
    char *str = (char*)malloc(sizeof(char) * 20);
    scanf("%s", str);
    if(str[0] == 'T' || str[0] == 'K'){
      int t;
      scanf("%d", &t);
      if(str[0] == 'T')
        push_front(&a, &e, t);
      else
        push_back(&a, &e, t);
      continue;
    }
    if(str[0] == 'P'){
      putar(&a, &e);
      continue;
    }
    if(str[0] == 'U'){
      if(is_empty(a)){
        printf("Yah gabut...\n");
        continue;
      }
      printf("%d\n", a->data);
      del_front(&a, &e);
      continue;
    }
    if(str[0] == 'G'){
      if(is_empty(a)){
        printf("Yah gabut...\n");
        continue;
      }
      printf("%d\n", e->data);
      del_back(&a, &e);
    }
  }
  return 0;
}