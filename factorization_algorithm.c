#include <stdio.h>

int main(void) {

  int num = 100;
  int k = 2;
  while (num != 1) {
    if (num%k==0){	//나머지가 0이면 나누기
      printf("%d ",k);
      num /= k;
    }
    else
      k++;
  }
  return 0;
}
