#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
  char data;
  struct node *next;
}node, Node, *NodePtr;

void push_back(node **a, char c){
  node *temp = (node*)malloc(sizeof(node));
  temp->data = c;
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

int main(){
  int tt;
  scanf("%d", &tt);
  while(tt--){
    node *a = 0;
    int n;
    scanf("%d", &n);
    int aa = 0, b = 0, ans = 0;
    for(int i = 0; i < n; ++i){
      char c;
      scanf(" %c", &c);
      push_back(&a, c);
      if(c == '('){
        aa++;
      }else{
        b++;
        aa == 0? ++ans: --aa;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}