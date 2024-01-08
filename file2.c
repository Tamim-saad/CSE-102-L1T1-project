#include<stdio.h>

int main(){
    char st;
 FILE *fp;
 fp=fopen("toyfile","r");
 if(fp==NULL){
        printf("Error");
        exit(1);}
 while(!feof(fp)){
    st=fgetc(fp);
    printf("%c",st);
  }
    fclose(fp);
return 0;
}
