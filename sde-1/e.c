#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
  char *name, *play;
  struct node *next;
}node, Node, *NodePtr;

void push(node **a, char *t, char *t1){
  node *temp = (node*)malloc(sizeof(node));
  temp->name = (char*)malloc(sizeof(char) * 21);
  temp->play = (char*)malloc(sizeof(char) * 21);
  strcpy(temp->name, t);
  strcpy(temp->play, t1);
  temp->next = 0;
  if(*a == 0){
    *a = temp;
    return;
  }
  node *temp1 = *a;
  while(temp1->next != 0){
    temp1 = temp1->next;
  }
  temp1->next = temp;
}

void print(node *a){
  node *temp = a;
  while(temp != 0){
    printf("%s %s\n", temp->name, temp->play);
    temp = temp->next;
  }
}

void del(node **a, int x){
  node *temp = *a;
  if(*a == 0) return;
  if(x == 0){
    *a = temp->next;
    free(temp);
    return;
  }
  for(int i = 0; i < x-1; ++i){
    temp = temp->next;
  }
  node *temp1 = temp->next;
  temp->next = temp1->next;
  free(temp1);
}

void print_at(node **a, int n, int *curr, int tt){
  node *temp = *a;
  int it = (*curr + n) % tt;
  *curr = it;
  while(it--){
    temp = temp->next;
  }
  printf("%s %s\n", temp->name, temp->play);
  del(a, *curr);
}

int main(){
  node *a = 0;
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; ++i){
    char *temp = (char*)malloc(sizeof(char) * 21), *temp1 = (char*)malloc(sizeof(char) * 21);
    scanf(" %s %s", temp, temp1);
    push(&a, temp, temp1);
  }
  int curr = 0, tt = n;
  for(int i = 0; i < n; ++i){
    int temp;
    scanf("%d", &temp);
    print_at(&a, temp, &curr, tt--);
  }
  print(a);
  return 0;
}