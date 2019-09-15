//유클리드_호제법
#include <stdio.h>

int gcd_algo(int a, int b);
int main(void){
  int num1 = 10;
  int num2 = 20;
  int gcd = gcd_algo(num1,num2);

  printf("최대공약수 : %d\n", gcd);
  printf("최소 공배수 : %d\n", num1*num2/gcd);
  return 0;
}

int gcd_algo(int a,int b) {
  //if b>a swap(a,b);
  int r = 0;
  while (b!=0) {      //작은 걸로 큰걸나눠서 0이 되면 작은것이 최대공약수
    r = a%b;	      //작은수를 큰수 쪽으로 집어넣고 나머지값을 작은 수에 넣음
    a = b;	      //마지막에는 결국 나머지가 0이 됨(그때의 나눈값이 최대공약수)
    b = r;
  }
  return a;
}

/*
재귀로 풀기
int gcd_algo(int a, int b){
  if (b>a) swap(a,b);
  if (b==0) return a;
  return gcd_algo(b, a%b);
}
*/
