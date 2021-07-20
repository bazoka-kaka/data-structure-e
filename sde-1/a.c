#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ll long long

typedef struct node{
  ll data;
  struct node *next;
}node;

void push(node **a, ll n){
  node *temp = (node*)malloc(sizeof(node));
  temp->data = n;
  temp->next = 0;
  if(*a == 0){
    *a = temp;
    return;
  }
  node *temp1 = *a, *temp2 = *a;
  while(n <= temp1->data && temp1->next != 0){
    temp1 = temp1->next;
  }
  if(temp1 == *a){
    if(n <= temp1->data){
      temp1->next = temp;
      return;
    }
    temp->next = *a;
    *a = temp;
    return;
  }
  if(temp1->next == 0){
    if(n <= temp1->data){
      temp1->next = temp;
      return;
    }
    while(temp2->next != temp1){
      temp2 = temp2->next;
    }
    temp2->next = temp;
    temp->next = temp1;
    return;
  }
  if(temp1->next != 0){
    if(n > temp1->data){
      while(temp2->next != temp1){
        temp2 = temp2->next;
      }
      temp2->next = temp;
      temp->next = temp1;
      return;
    }
  }
}

void print(node *a){
  node *temp = a;
  while(temp != 0){
    if(temp->next != 0)
      printf("%lld, ", temp->data);
    else
      printf("%lld", temp->data);
    temp = temp->next;
  }
}

int main(){
  int n;
  scanf("%d", &n);
  node *a = 0;
  while(n--){
    ll temp;
    scanf("%lld", &temp);
    push(&a, temp);
  }
  print(a);
  return 0;
}