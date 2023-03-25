#include <iostream>

using namespace std;

void merge(int *p,int *q){
  int size = (q-p)*2;
  int*c=p+size;
  for(;q<c;){
    if(*p>*q){
      swap(*p,*q);
      for(int *t=p+1;t!=q;t++){
        swap(*t,*q);
      }
      p++;
      q++;
    }
    else if(*p<*q){
    p++;  
  }
  
}
}

int main() {
  /*
  int a[6]={1,3,5,7,9,11};
  for(int *q=(a+5), *p=a;p<q;p++,q--){
    int c=*p;
    *p=*q;
    *q=c;
  }   
  */
  int a[8]={2,12,18,22,1,3,11,19};
  merge(a,a+4);
}