#include<stdio.h>
#include<stdlib.h>

int main(){
    char str[50];
 FILE *fp;
 fp=fopen("toyfile","r");
   if(fp==NULL){
    printf("File doesn't exist");
    exit(1);
  }
 while(!feof(fp)){
    fgets(str,4,fp);
    //if(!feof(fp))
    printf("%s\n",str);

 }

fclose(fp);
return 0;
}
