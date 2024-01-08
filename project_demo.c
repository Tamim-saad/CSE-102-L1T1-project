
#include "iGraphics.h"
int screenWidth=1231,screenHight=658;
int q;
struct buttonCordinate
{
 int x,y;
}
bCordinate[6];
int mposx,mposy;
char button[5000][5000]={"play_game.bmp","Saved_game.bmp","New_game.bmp","High_score.bmp","Instruction.bmp","exit.bmp"};
char homemanu[500]="shipcrash.bmp";
char Instruction[50]="Inst1.bmp";
char Instruction1[50]="Inst2.bmp";
//char play[15]="hs\\play_game.bmp";
//char New[15]="hs\\New_game.bmp";
//char score[15]="hs\\High_score.bmp";
//char Instructions[15]="hs\\Instruction.bmp";
//char ex[15]="hs\\exit.bmp";
int p=0;
int gamestate=-1;
void exit(void);
//void test();
void iDraw()
{
int i;
iClear();

iShowBMP(100,550,"play_game.bmp");
//iShowBMP(100,450,"New_game.bmp");
//iShowBMP(100,350,"Saved_game.bmp");
//iShowBMP(100,250,"High_score.bmp");
//iShowBMP(100,150,"Instruction.bmp");
//iShowBMP(100,50,"exit.bmp");
//iText(50,50,"Press Enter to go to the next page",GLUT_BITMAP_TIMES_ROMAN_10);
//if(q==1)
  //  iShowBMP(0,0,Instruction1);
if(gamestate==-1){
    iShowBMP(0,0,homemanu);
    iSetColor(0,0,0);
    iText(400,50,"Place the cursor on the desired spot",GLUT_BITMAP_TIMES_ROMAN_10);
for(i=0;i<6;i++)
{
  iShowBMP2(bCordinate[i].x,bCordinate[i].y,button[i],255);
}

}
else if(gamestate==1)//main game page
{

}
else if(gamestate==2)
{

}
else if(gamestate==3)
{

}

else if(gamestate==4)
{
    iSetColor(0,0,0);
    iShowBMP(0,0,Instruction);
    iText(50,50,"Press Enter to go to the next page",GLUT_BITMAP_TIMES_ROMAN_24);
    if(p==1)
    {
        iShowBMP(0,0,Instruction1);
    }

    //next();
}
if(gamestate==5)
{
    exit(0);
}
}
//void next()
//{
//    iKeyboard();
//}

void iKeyboard(unsigned char key)
{

   // if(key=='q')
    //{
      //  int q=1;
        //idraw();
    //}


}
void iSpecialKeyboard(unsigned char key)
{
    if(key=='q')
    {
        int p=1;
    }

        //if(mode==1){

   // if(key=='q')
    //{
      // iShowBMP(0,0,Instruction1);
    //}
   // }

    //if(p==1){
    //if(key==GLUT_KEY_F6)
    //{
      // iShowBMP(0,0,Instruction1);
    //}
    //}


}
void iMouseMove(int mx, int my)
{

}
void iMouse(int button,int state,int mx,int my)

{
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
    {
        int i;
        for(i=0;i<6;i++)
        {

            if(mx>=bCordinate[i].x&&mx<=bCordinate[i].x+250&&my>=bCordinate[i].y&&my<=bCordinate[i].y+67)
            {
              gamestate=i;
            }

        }
    }
    //if(button==GLUT_RIGHT_BUTTON&&state==GLUT_UP)
    //{
      //  iShowBMP(0,0,Instruction1);
    //}

}
void exit(void)
{
   // if(life<=0)
    //{
      //  gamestate==
    }






int main()
{
    int Score=0;

      int sum=50,i;  // PlaySound("ship.wav",NULL,SND_ASYNC|SND_LOOP);
    //place your own initialization codes here.

    for(i=5;i>=0;i--)
    {
        bCordinate[i].x=100;
        bCordinate[i].y=sum;
        sum+=100;
    }
    iInitialize(screenWidth,screenHight, "ANTARCTICA!");


    return 0;
}

