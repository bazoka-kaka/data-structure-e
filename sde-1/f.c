#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long

typedef struct node{
  int data;
  struct node *next, *prev;
}node;

void push_back(node **a, node **e, int n){
  node *temp = (node*)malloc(sizeof(node));
  temp->data = n;
  temp->next = 0;
  temp->prev = 0;
  if(*a == 0){
    *a = temp;
    *e = temp;
    return;
  }
  node *temp1 = *e;
  temp1->next = temp;
  temp->prev = temp1;
  *e = temp;
}

void print(node *a){
  node *temp = a;
  while(temp != 0){
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

void remove_at(node **a, node **e, node *temp){
  if(*a == 0){
    return;
  }
  if(*a == temp){
    *a = 0;
    *e = 0;
    free(temp);
    return;
  }
  node *temp1 = *a;
  while(temp1 != temp){
    temp1 = temp1->next;
  }
  node *temp2 = temp1->prev;
  temp2->next = temp1->next;
  if(temp1->next){
    temp2 = temp1->next;
    temp2->prev = temp1->prev;
    free(temp1);
    return;
  }
  else{
    *e = temp2;
    free(temp1);
  }  
}

int main(){
  ll tt;
  scanf("%lld", &tt);
  while(tt--){
    int n;
    scanf("%d", &n);
    node *a = 0, *e = 0;
    for(int i = 0; i < n; ++i){
      int t;
      scanf("%d", &t);
      if(a == 0){
        push_back(&a, &e, t);
        continue;
      }
      node *temp = a;
      while(temp->next != 0){
        node *temp1 = temp->next;
        if(temp->data < t){
          remove_at(&a, &e, temp);
        }
        temp = temp1;
      }
      if(temp->data < t){
        if(temp->prev != 0){
          remove_at(&a, &e, temp);
          push_back(&a, &e, t);
          continue;
        }
        else{
          a = 0;
          e = 0;
          free(temp);
          push_back(&a, &e, t);
          continue;
        }
      }else{
        push_back(&a, &e, t);
      }
    }
    print(a);
  }
  return 0;
}