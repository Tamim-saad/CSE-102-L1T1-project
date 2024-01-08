#include<stdio.h>
 int main(){
  FILE *fp;
  char str[]="my name is tamim hasan saad";
  fp=fopen("toyfile","w");
  if(fp==NULL){
    printf("File doesn't exist");
  }
  int i=0;
  while(str[i]){
    printf("%c is written\n",str[i]);
    fputc(str[i],fp);
    //if(ret==-1) printf("Error");
    i++;
  }
 return 0;
 }

