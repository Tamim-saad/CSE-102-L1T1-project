#include<stdio.h>

 int main(){
 FILE *from;
 FILE *to;
 from=fopen("toyfile","r");
   if(from==NULL){
        printf("Error");
        exit(1);}
 to=fopen("dst","w");
   if(to==NULL){
        printf("Error");
        exit(1);}
 char c;//=fputc(c,to);
  /*while(1){
  //while((c=fgetc(from))!=EOF){
  c=fgetc(from);
   if(c==EOF) break;
    fputc(c,to);
 }*/
 while(!feof(from)){
    c=fgetc(from);
    if(ferror(from)){
        printf("From file error");
        exit(1);}
     if(!feof(from)){
    fputc(c,to);}
     if(ferror(to)){
        printf("to file error");
        exit(1);}
 }


 fclose(from);
 fclose(to);
 return 0;
 }
