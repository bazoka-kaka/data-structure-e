#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_min(int *arr, int a, int b, int n, int m) {
  if(a < 0) a = 0;
  if(b > n - 1) b = n - 1;
  int mini = arr[a];
  if(mini == m) return mini;
  for(int i = a + 1; i <= b; ++i) {
    if(arr[i] == m) return arr[i];
    if(arr[i] < mini) mini = arr[i];
  }
  return mini;
}

int main() {
  int n;
  scanf("%d", &n);
  int arr[n], mini = 0, y = 0;
  for(int i = 0; i < n; ++i){
    scanf("%d", &arr[i]);
    if(y == 0) {
      mini = arr[i];
      y = 1;
    }else{
      if(arr[i] < mini) mini = arr[i];
    }
  }
  int q;
  scanf("%d", &q);
  while(q--) {
    int t, a, b;
    scanf("%d%d%d", &t, &a, &b);
    if(t == 1) {
      arr[a] = b;
      if(b < mini) mini = b;
    }else {
      int ans = find_min(arr, a, b, n, mini);
      printf("%d\n", ans);
    }
  }
  return 0;
}