# include "iGraphics.h"
#include<string.h>
#include<stdio.h>
#include<iostream>

#define shipwidth 75
#define shiplength 220
#define movexy 35
#define screenwidth 1200
#define screenlentgh 800
#define maxlife 4
#define data_x 1060
#define differ 30

/// definition of structure

typedef struct coordinate
{
    int x;
    int y;
} coordinate;

typedef struct ice
{
    coordinate ice1;
    coordinate ice2;
    coordinate ice3;
} ice;
ice pattern[9];

/// score & highscore variable
FILE *score;
float scr=0,temp=0;
char highscore[10],scorestring[10];
void plsound();


/// pause variable
FILE *pause;
int pause_state;

/// common variable
int shipx=427,shipy=0,tempcontrol;
float t=0,t1,t2,t3;
unsigned char key;


/// game window control variable
char condition='h';
int backgr_y;

/// game option control variable
int controlkey=1;
int timer_state=0;
int temp_back_control;
int exit_var=0;

/// mode control
int mode=2;
int finish_mark=1;

/// background variable
int background=2;

/// sound variable
int sound_var=1;

///life variable
int lifecount=4;
float lifex,lifey;
int life_image_state;

///wind
int wind_var;
int wind_x,wind_y;
int wind_count=0;
int wind_image_state=0;

void iDraw()
{

    if(condition=='c')
    {
        iPauseTimer(0);
        iShowBMP(0,0,".\\tcrash_message.bmp");
        PlaySound("life_reduction.wav",NULL,SND_SYNC|SND_LOOP);

        iSetColor(255,0,0);
        iText(70,700,"YOU HAVE LOST ONE LIFE",GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(data_x-50,100,".\\tcontinue.bmp");

    }


    if(condition=='n')
    {
        condition='g';
        wind_x=0;
        wind_y=0;
        pattern[controlkey-1].ice1.y=pattern[controlkey-1].ice2.y=pattern[controlkey-1].ice3.y=850;
        controlkey=(rand()%9)+1;

        iResumeTimer(0);
        //sound_var=1;
        plsound();
    }


    if(condition=='f')
    {
        iClear();
        iPauseTimer(0);

        PlaySound("Game_over.wav",NULL,SND_SYNC|SND_LOOP);

        score=fopen("Highscore","r");
        fscanf(score,"%f",&temp);
        fclose(score);

        if(scr>temp)
        {
            score=fopen("Highscore","w");
            fprintf(score,"%.0f",scr);
            fclose(score);
            itoa(scr,highscore,10);
        }
        else
        {
            itoa(temp,highscore,10);
        }

        iSetColor(0,0,0);
        iFilledRectangle(0,0,1200,800);
        iSetColor(255,255,255);
        iText(300,500,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,400,"YOUR SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,350,scorestring,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,250,"HIGH SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,200,highscore,GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if(condition=='r')
    {
        scr=0;

        iClear();
        t=0;
        t1=0;
        t2=0;
        t3=0;
        wind_x=0;
        wind_y=0;
        condition='g';
        controlkey=rand()%9+1;
        lifecount=maxlife;
        finish_mark=1;
        iResumeTimer(0);

    }

    if(condition=='h')
    {

        iShowBMP(0,0,"tfront_background.bmp");

        if(lifecount>0&&pause_state==1)
        {
            iShowBMP(70,600,"tplay_game.bmp");
        }
        iShowBMP(70,500,"tNew_game.bmp");
        iShowBMP(70,400,"toption.bmp");
        iShowBMP(70,300,"tHigh_score.bmp");
        iShowBMP(70,200,"tinstruction.bmp");
        iShowBMP(70,100,"texit.bmp");
    }

    if(condition=='i')
    {
        iShowBMP(0,0,".\\tgame_instruction.bmp");
    }

    if(condition=='o')
    {
        iShowBMP(0,0,"toption_background.bmp");
        iShowBMP(300,100,"tbackground.bmp");
        iShowBMP(300,325,"tsound_on_off.bmp");
        iShowBMP(300,550,"tmode.bmp");
    }


    if(condition=='m')
    {
        iShowBMP(0,0,"tmode_background.bmp");
        iShowBMP(300,200,".\\teasy.bmp");
        iShowBMP(300,350,".\\tmedium.bmp");
        iShowBMP(300,500,".\\thard.bmp");
    }

    if(condition=='u')
    {
        iShowBMP(0,0,".\\tsound_background.bmp");
        iShowBMP(300,200,".\\ton.bmp");
        iShowBMP(300,400,".\\toff.bmp");
    }

    if(condition=='v')
    {
        iShowBMP(0,0,".\\t_changebackground.bmp");
        iShowBMP(300,500,".\\tbackground_1.bmp");
        iShowBMP(300,300,".\\tbackground_2.bmp");
    }

    if(condition=='s')
    {
        iSetColor(0,0,0);
        iFilledRectangle(0,0,1200,800);
        iSetColor(255,0,0);
        iText(450,350,"HIGH SCORE",GLUT_BITMAP_TIMES_ROMAN_24);

        score=fopen("Highscore","r");
        fscanf(score,"%f",&temp);
        fclose(score);
        itoa(temp,highscore,10);
        iSetColor(255,255,255);
        iText(450,300,highscore,GLUT_BITMAP_TIMES_ROMAN_24);

    }



    if(condition=='g')
    {
        if(pause_state==1) iResumeTimer(0);
        if(background==1)
        {
            iShowBMP(0,0,".\\waterbackground.bmp");
        }
        if(background==2)
        {
            iShowBMP(0,0,".\\waterbackground2.bmp");
        }


        if(controlkey==1)
        {
            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[0].ice1.x,pattern[0].ice1.y,".\\tice2.bmp",0x00ffffff);
            iShowBMP2(pattern[0].ice2.x,pattern[0].ice2.y,".\\tice4.bmp",0x00ffffff);
            iShowBMP2(pattern[0].ice3.x,pattern[0].ice3.y,".\\tice6.bmp",0x00ffffff);

            if(shipx>=(pattern[0].ice1.x-shipwidth)&&shipx<=(pattern[0].ice1.x+100)&&shipy>=(pattern[0].ice1.y-shiplength)&&shipy<=(pattern[0].ice1.y=+73))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);

                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }


            if(shipx>=(pattern[0].ice2.x-shipwidth)&&shipx<=(pattern[0].ice2.x+135)&&shipy>=(pattern[0].ice2.y-shiplength)&&shipy<=(pattern[0].ice2.y+106))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);

                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[0].ice3.x-shipwidth)&&shipx<=(pattern[0].ice3.x+105)&&shipy>=(pattern[0].ice3.y-shiplength)&&shipy<=(pattern[0].ice3.y+110))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);

                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }


        if(controlkey==2)
        {
            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[1].ice1.x,pattern[1].ice1.y,".\\tice7.bmp",0x00ffffff);
            iShowBMP2(pattern[1].ice2.x,pattern[1].ice2.y,".\\tice8.bmp",0x00ffffff);
            iShowBMP2(pattern[1].ice3.x,pattern[1].ice3.y,".\\tice9.bmp",0x00ffffff);

            if(shipx>=(pattern[1].ice1.x-shipwidth)&&shipx<=(pattern[1].ice1.x+116)&&shipy>=(pattern[1].ice1.y-shiplength)&&shipy<=(pattern[1].ice1.y+90))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[1].ice2.x-shipwidth)&&shipx<=(pattern[1].ice2.x+80)&&shipy>=(pattern[1].ice2.y-shiplength)&&shipy<=(pattern[1].ice2.y+57))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[1].ice3.x-shipwidth)&&shipx<=(pattern[1].ice3.x+80)&&shipy>=(pattern[1].ice3.y-shiplength)&&shipy<=(pattern[1].ice3.y+59))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }


        if(controlkey==3)
        {
            pattern[2].ice1.x=150,pattern[2].ice2.x=350,pattern[2].ice3.x=770;

            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[2].ice1.x,pattern[2].ice1.y,".\\tice10.bmp",0x00ffffff);
            iShowBMP2(pattern[2].ice2.x,pattern[2].ice2.y,".\\tice11.bmp",0x00ffffff);
            iShowBMP2(pattern[2].ice3.x,pattern[2].ice3.y,".\\tice12.bmp",0x00ffffff);

            if(shipx>=(pattern[2].ice1.x-shipwidth)&&shipx<=(pattern[2].ice1.x+73)&&shipy>=(pattern[2].ice1.y-shiplength)&&shipy<=(pattern[2].ice1.y+73))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[2].ice2.x-shipwidth)&&shipx<=(pattern[2].ice2.x+80)&&shipy>=(pattern[2].ice2.y-shiplength)&&shipy<=(pattern[2].ice2.y+71))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[2].ice3.x-shipwidth)&&shipx<=(pattern[2].ice3.x+86)&&shipy>=(pattern[2].ice3.y-shiplength)&&shipy<=(pattern[2].ice3.y+64))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }

        if(controlkey==4)
        {

            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[3].ice1.x,pattern[3].ice1.y,".\\tice24.bmp",0x00ffffff);
            iShowBMP2(pattern[3].ice2.x,pattern[3].ice2.y,".\\tice24.bmp",0x00ffffff);
            iShowBMP2(pattern[3].ice3.x,pattern[3].ice3.y,".\\tice15.bmp",0x00ffffff);

            if(shipx>=(pattern[3].ice1.x-shipwidth)&&shipx<=(pattern[3].ice1.x+90)&&shipy>=(pattern[3].ice1.y-shiplength)&&shipy<=(pattern[3].ice1.y+88))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[3].ice2.x-shipwidth)&&shipx<=(pattern[3].ice2.x+90)&&shipy>=(pattern[3].ice2.y-shiplength)&&shipy<=(pattern[3].ice2.y+88))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[3].ice3.x-shipwidth)&&shipx<=(pattern[3].ice3.x+119)&&shipy>=(pattern[3].ice3.y-shiplength)&&shipy<=(pattern[3].ice3.y+88))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }

        if(controlkey==5)
        {

            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[4].ice1.x,pattern[4].ice1.y,".\\tice16.bmp",0x00ffffff);
            iShowBMP2(pattern[4].ice2.x,pattern[4].ice2.y,".\\tice17.bmp",0x00ffffff);
            iShowBMP2(pattern[4].ice3.x,pattern[4].ice3.y,".\\tice24.bmp",0x00ffffff);

            if(shipx>=(pattern[4].ice1.x-shipwidth)&&shipx<=(pattern[4].ice1.x+100)&&shipy>=(pattern[4].ice1.y-shiplength)&&shipy<=(pattern[4].ice1.y+87))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[4].ice2.x-shipwidth)&&shipx<=(pattern[4].ice2.x+120)&&shipy>=(pattern[4].ice2.y-shiplength)&&shipy<=(pattern[4].ice2.y+100))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[4].ice3.x-shipwidth)&&shipx<=(pattern[4].ice3.x+95)&&shipy>=(pattern[4].ice3.y-shiplength)&&shipy<=(pattern[4].ice3.y+91))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }

        if(controlkey==6)
        {
            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[5].ice1.x,pattern[5].ice1.y,".\\tice24.bmp",0x00ffffff);
            iShowBMP2(pattern[5].ice2.x,pattern[5].ice2.y,".\\tice20.bmp",0x00ffffff);
            iShowBMP2(pattern[5].ice3.x,pattern[5].ice3.y,".\\tice21.bmp",0x00ffffff);

            if(shipx>=(pattern[5].ice1.x-shipwidth)&&shipx<=(pattern[5].ice1.x+90)&&shipy>=(pattern[5].ice1.y-shiplength)&&shipy<=(pattern[5].ice1.y+88))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[5].ice2.x-shipwidth)&&shipx<=(pattern[5].ice2.x+80)&&shipy>=(pattern[5].ice2.y-shiplength)&&shipy<=(pattern[5].ice2.y+74))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[5].ice3.x-shipwidth)&&shipx<=(pattern[5].ice3.x+90)&&shipy>=(pattern[5].ice3.y-shiplength)&&shipy<=(pattern[5].ice3.y+70))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }
        if(controlkey==7)
        {
            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[6].ice1.x,pattern[6].ice1.y,".\\tice22.bmp",0x00ffffff);
            iShowBMP2(pattern[6].ice2.x,pattern[6].ice2.y,".\\tice23.bmp",0x00ffffff);
            iShowBMP2(pattern[6].ice3.x,pattern[6].ice3.y,".\\tice24.bmp",0x00ffffff);

            if(shipx>=(pattern[6].ice1.x-shipwidth)&&shipx<=(pattern[6].ice1.x+110)&&shipy>=(pattern[6].ice1.y-shiplength)&&shipy<=(pattern[6].ice1.y+80))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[6].ice2.x-shipwidth)&&shipx<=(pattern[6].ice2.x+100)&&shipy>=(pattern[6].ice2.y-shiplength)&&shipy<=(pattern[6].ice2.y+130))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[6].ice3.x-shipwidth)&&shipx<=(pattern[6].ice3.x+90)&&shipy>=(pattern[6].ice3.y-shiplength)&&shipy<=(pattern[6].ice3.y+88))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }

        if(controlkey==8)
        {

            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[7].ice1.x,pattern[7].ice1.y,".\\tice25.bmp",0x00ffffff);
            iShowBMP2(pattern[7].ice2.x,pattern[7].ice2.y,".\\tice26.bmp",0x00ffffff);
            iShowBMP2(pattern[7].ice3.x,pattern[7].ice3.y,".\\tice27.bmp",0x00ffffff);

            if(shipx>=(pattern[7].ice1.x-shipwidth)&&shipx<=(pattern[7].ice1.x+100)&&shipy>=(pattern[7].ice1.y-shiplength)&&shipy<=(pattern[7].ice1.y+105))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[7].ice2.x-shipwidth)&&shipx<=(pattern[7].ice2.x+86)&&shipy>=(pattern[7].ice2.y-shiplength)&&shipy<=(pattern[7].ice2.y+80))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[7].ice3.x-shipwidth)&&shipx<=(pattern[7].ice3.x+54)&&shipy>=(pattern[7].ice3.y-shiplength)&&shipy<=(pattern[7].ice3.y+70))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }

        if(controlkey==9)
        {

            iShowBMP2(shipx,shipy,".\\tship2.bmp",0x00ffffff);
            iShowBMP2(pattern[8].ice1.x,pattern[8].ice1.y,".\\tice5.bmp",0x00ffffff);
            iShowBMP2(pattern[8].ice2.x,pattern[8].ice2.y,".\\tice6.bmp",0x00ffffff);
            iShowBMP2(pattern[8].ice3.x,pattern[8].ice3.y,".\\tice13.bmp",0x00ffffff);

            if(shipx>=(pattern[8].ice1.x-shipwidth)&&shipx<=(pattern[8].ice1.x+100)&&shipy>=(pattern[8].ice1.y-shiplength)&&shipy<=(pattern[8].ice1.y+85))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[8].ice2.x-shipwidth)&&shipx<=(pattern[8].ice2.x+105)&&shipy>=(pattern[8].ice2.y-shiplength)&&shipy<=(pattern[8].ice2.y+109))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }

            if(shipx>=(pattern[8].ice3.x-shipwidth)&&shipx<=(pattern[8].ice3.x+97)&&shipy>=(pattern[8].ice3.y-shiplength)&&shipy<=(pattern[8].ice3.y+84))
            {
                iShowBMP2(shipx-70,shipy+40,".\\tcollision.bmp",0x00ffffff);
                condition='c';
                lifecount--;
                if(lifecount<=0)
                {
                    condition='f';
                }
            }
        }

        if(controlkey!=0)
        {
            iSetColor(0,0,0);
            iFilledRectangle(1000,0,200,800);
            iSetColor(255,0,0);
            iText(data_x,700,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,0,0);
            iText(data_x,650,scorestring,GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(0,255,0);
            iText(data_x,470,"LIFE",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,255,0);
            iText(data_x-differ-27,300,"WIND STRUGGLE",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,0,0);
            iRectangle(data_x-differ,220,120,50);
            iSetColor(255,0,0);
            iLine(data_x-differ+40,220,data_x-differ+40,220+50);
            iSetColor(255,0,0);
            iLine(data_x-differ+80,220,data_x-differ+80,220+50);

            if(lifecount==1)
            {
                iShowBMP(data_x-differ,400,".\\tlife_img.bmp");
            }

            if(lifecount==2)
            {
                iShowBMP(data_x-differ,400,".\\tlife_img.bmp");
                iShowBMP(data_x-differ+40,400,".\\tlife_img.bmp");
            }

            if(lifecount==3)
            {
                iShowBMP(data_x-differ,400,".\\tlife_img.bmp");
                iShowBMP(data_x-differ+40,400,".\\tlife_img.bmp");
                iShowBMP(data_x-differ+40*2,400,".\\tlife_img.bmp");
            }

            if(lifecount>=4)
            {
                iShowBMP(data_x-differ,400,".\\tlife_img.bmp");
                iShowBMP(data_x-differ+40,400,".\\tlife_img.bmp");
                iShowBMP(data_x-differ+40*2,400,".\\tlife_img.bmp");
                iShowBMP(data_x-differ+40*3,400,".\\tlife_img.bmp");
            }

            if(wind_count==2)
            {
                iSetColor(255,0,0);
                iFilledRectangle(data_x-differ,220,40,50);
            }

            if(wind_count==1)
            {
                iSetColor(255,255,0);
                iFilledRectangle(data_x-differ,220,40,50);
                iFilledRectangle(data_x-differ+41,220,40,50);
            }

            if(wind_count==0)
            {
                iSetColor(0,255,0);
                iFilledRectangle(data_x-differ,220,40,50);
                iFilledRectangle(data_x-differ+41,220,40,50);
                iFilledRectangle(data_x-differ+82,220,40,50);
            }
        }

        if(life_image_state==1)
        {
            iShowBMP(lifex,lifey,".\\tlife_img.bmp");
            if(shipx>=(lifex-shipwidth)&&shipx<=(lifex+shipwidth+70)&&shipy>=(lifey-shiplength)&&shipy<=(lifey+40))
            {
                if(lifecount<4) lifecount++;
                life_image_state=0;
            }
        }

        if(wind_image_state==1)
        {
            iShowBMP2(wind_x,wind_y,".\\twind2.bmp",0x00ffffff);
            iShowBMP2(wind_x,wind_y,".\\twind3.bmp",0x00ffffff);

            if(shipx>=(wind_x-shipwidth)&&shipx<=(wind_x+shipwidth+35)&&shipy>=(wind_y-shiplength)&&shipy<=(wind_y+35))
            {
                wind_count++;
                wind_image_state=0;

            }
            if(wind_count==3)
            {
                lifecount--;
                wind_count=0;
                condition='c';
            }
        }


        // if(wind_var==2){
        //   iShowBMP2(wind_x,wind_y,".\\twind3.bmp",0x00ffffff);}

    }

    if(condition=='s'||condition=='g'||condition=='o'||condition=='m'||condition=='v'||condition=='u'||condition=='i'||condition=='f')
    {
        iShowBMP(data_x,100,".\\tmenu.bmp");
    }

}


void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n",mx,my);
}



void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf("x = %d, y= %d\n",mx,my);
        shipx += movexy;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        shipx -= movexy;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=70&&mx<=320&&my>=100&&my<=166)
    {
        exit(0);
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=70&&mx<=320&&my>=200&&my<=266&&condition=='h')
    {
        condition='i';
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=70&&mx<=320&&my>=300&&my<=366&&condition=='h')
    {
        condition='s';
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=70&&mx<=320&&my>=400&&my<=475&&condition=='h')
    {
        condition='o';
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=70&&mx<=320&&my>=500&&my<=566&&condition=='h')
    {
        condition='r';
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=70&&mx<=320&&my>=600&&my<=666&&condition=='h'&&pause_state==1)
    {
        iResumeTimer(0);
        pause_state=0;
        condition='g';
    }


    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=data_x&&mx<=(data_x+90)&&my>=100&&my<=145&&(condition=='s'||condition=='o'||condition=='m'||condition=='v'||condition=='u'||condition=='i'||condition=='f'))
    {
        condition='h';
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=data_x&&mx<=(data_x+90)&&my>=100&&my<=145&&condition=='g')
    {
        if(lifecount>0)
        {
            pause_state=1;
            iPauseTimer(0);
        }
        condition='h';
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=687&&my>=100&&my<=200&&condition=='o')
    {
        condition='v';
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=687&&my>=550&&my<=650&&condition=='o')
    {
        condition='m';
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=687&&my>=250&&my<=650&&condition=='o')
    {
        condition='u';
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=(data_x-50)&&mx<=1196&&my>=100&&my<=181&&condition=='c')
    {
        condition='n';
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=685&&my>=200&&my<=285&&condition=='u')
    {
        sound_var=1;
        plsound();
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=685&&my>=400&&my<=485&&condition=='u')
    {
        sound_var=0;
        plsound();
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=650&&my>=200&&my<=350&&condition=='m')
    {
        mode=1;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=650&&my>=350&&my<=460&&condition=='m')
    {
        mode=2;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=650&&my>=500&&my<=490&&condition=='m')
    {
        mode=3;
    }


    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=666&&my>=300&&my<=400&&condition=='v')
    {
        background=2;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&& mx>=300&&mx<=666&&my>=500&&my<=600&&condition=='v')
    {
        background=1;
    }

}


void iKeyboard( unsigned char key)
{
    if(key == 'x') exit(0);
    if(key == 'p') iPauseTimer(0);
    if(key == 'r') iResumeTimer(0);

    if(key == ' ')
    {
        if(sound_var==0)
        {
            sound_var=1;
            plsound();
        }
        else
        {
            sound_var=0;
            plsound();
        }
    }
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_RIGHT&&shipx<=(1000-80))
    {
        shipx+=movexy;
    }
    if(key == GLUT_KEY_LEFT&&shipx>=10)
    {
        shipx-=movexy;
    }
    if(key == GLUT_KEY_UP&&shipy<=395-2*movexy)
    {
        shipy+=movexy;
    }
    if(key == GLUT_KEY_DOWN&&shipy>=movexy)
    {
        shipy-=movexy;
    }

}

void timecontrol()
{

    if(mode==2)
    {
        t=t+.001;
        t1+=.001;
        t2+=.002;
        t3+=.003;
    }
    if(mode==1)
    {
        t=t+.01;
        t1+=.001;
        t2+=.002;
        t3+=.003;
    }
    if(mode==3)
    {
        t=t+.0001;
        t1+=.001;
        t2+=.002;
        t3+=.003;
    }
    scr=scr+t;

    wind_x+=5;
    wind_y-=5;
    if(wind_y<=0)
    {
        wind_var=0;
    }

    if(controlkey<1||controlkey>9)
    {
        controlkey=rand()%9+1;
    }


    if(life_image_state==1)
    {
        lifey-=5;
        if(lifey<=0)life_image_state=0;
    }
    itoa(scr,scorestring,10);


    if(controlkey==1)
    {
        pattern[0].ice1.y-=t1+t ;
        pattern[0].ice2.y-=t3+t ;
        pattern[0].ice3.y-=t2+t ;
        if(pattern[0].ice1.y<=0&&pattern[0].ice2.y<=0&&pattern[0].ice3.y<=0)
        {
            pattern[0].ice1.y=pattern[0].ice2.y=pattern[0].ice3.y=850;

            pattern[0].ice1.x=rand()%240;
            pattern[0].ice2.x=rand()%300+300;
            pattern[0].ice3.x=rand()%400+610;

            controlkey=rand()%9;
        }
    }

    if(controlkey==2)
    {
        pattern[1].ice1.y-=t2+t ;
        pattern[1].ice2.y-=t3+t ;
        pattern[1].ice3.y-=t1+t ;

        if(pattern[1].ice1.y<=0&&pattern[1].ice2.y<=0&&pattern[1].ice3.y<=0)
        {
            pattern[1].ice1.y=pattern[1].ice2.y=pattern[1].ice3.y=850;

            pattern[1].ice1.x=rand()%240;
            pattern[1].ice2.x=rand()%300+300;
            pattern[1].ice3.x=rand()%400+610;

            controlkey=(rand()%9);

        }
    }


    if(controlkey==3)
    {
        pattern[2].ice1.y-=t3+t ;
        pattern[2].ice2.y-=t2+t ;
        pattern[2].ice3.y-=t1+t ;
        if(pattern[2].ice1.y<=0&&pattern[2].ice2.y<=0&&pattern[2].ice3.y<=0)
        {
            pattern[2].ice1.y=pattern[2].ice2.y=pattern[2].ice3.y=850;

            pattern[2].ice1.x=rand()%240;
            pattern[2].ice2.x=rand()%300+300;
            pattern[2].ice3.x=rand()%400+610;
            controlkey=(rand()%9);

        }
    }

    if(controlkey==4)
    {
        pattern[3].ice1.y-=t2+t ;
        pattern[3].ice2.y-=t3+t ;
        pattern[3].ice3.y-=t1+t ;

        if(pattern[3].ice1.y<=0&&pattern[3].ice2.y<=0&&pattern[3].ice3.y<=0)
        {
            pattern[3].ice1.y=pattern[3].ice2.y=pattern[3].ice3.y=850;

            pattern[3].ice1.x=rand()%240;
            pattern[3].ice2.x=rand()%300+300;
            pattern[3].ice3.x=rand()%400+610;

            controlkey=(rand()%9);
        }

    }

    if(controlkey==5)
    {
        pattern[4].ice1.y-=t2+t ;
        pattern[4].ice2.y-=t3+t ;
        pattern[4].ice3.y-=t1+t ;
        if(pattern[4].ice1.y<=0&&pattern[4].ice2.y<=0&&pattern[4].ice3.y<=0)
        {
            pattern[4].ice1.y=pattern[4].ice2.y=pattern[4].ice3.y=850;
            controlkey=(rand()%9);
            pattern[4].ice1.x=rand()%240;
            pattern[4].ice2.x=rand()%300+300;
            pattern[4].ice3.x=rand()%400+610;
        }
    }

    if(controlkey==6)
    {
        pattern[5].ice1.y-=t2+t ;
        pattern[5].ice2.y-=t3+t ;
        pattern[5].ice3.y-=t1+t ;
        if(pattern[5].ice1.y<=0&&pattern[5].ice2.y<=0&&pattern[5].ice3.y<=0)
        {
            pattern[5].ice1.y=pattern[5].ice2.y=pattern[5].ice3.y=850;

            controlkey=(rand()%9);
            pattern[5].ice1.x=rand()%240;
            pattern[5].ice2.x=rand()%300+300;
            pattern[5].ice3.x=rand()%400+610;
        }

    }

    if(controlkey==7)
    {
        pattern[6].ice1.y-=t2+t ;
        pattern[6].ice2.y-=t3+t ;
        pattern[6].ice3.y-=t1+t ;
        if(pattern[6].ice1.y<=0&&pattern[6].ice2.y<=0&&pattern[6].ice3.y<=0)
        {
            pattern[6].ice1.y=pattern[6].ice2.y=pattern[6].ice3.y=850;

            controlkey=(rand()%9);

            pattern[6].ice1.x=rand()%240;
            pattern[6].ice2.x=rand()%300+300;
            pattern[6].ice3.x=rand()%400+610;

        }
    }

    if(controlkey==8)
    {
        pattern[7].ice1.y-=t2+t ;
        pattern[7].ice2.y-=t3+t ;
        pattern[7].ice3.y-=t1+t ;
        if(pattern[7].ice1.y<=0&&pattern[7].ice2.y<=0&&pattern[7].ice3.y<=0)
        {
            pattern[7].ice1.y=pattern[7].ice2.y=pattern[7].ice3.y=850;

            controlkey=(rand()%9);
            pattern[7].ice1.x=rand()%240;
            pattern[7].ice2.x=rand()%300+300;
            pattern[7].ice3.x=rand()%400+610;
        }
    }

    if(controlkey==9)
    {
        pattern[8].ice1.y-=t2+t ;
        pattern[8].ice2.y-=t3+t ;
        pattern[8].ice3.y-=t1+t ;
        if(pattern[8].ice1.y<=0&&pattern[8].ice2.y<=0&&pattern[8].ice3.y<=0)
        {
            pattern[8].ice1.y=pattern[8].ice2.y=pattern[8].ice3.y=850;

            controlkey=(rand()%9);
            pattern[8].ice1.x=rand()%240;
            pattern[8].ice2.x=rand()%300+300;
            pattern[8].ice3.x=rand()%400+610;
        }
    }
}

void life()
{
    lifex=rand()%950;
    lifey=850;
    life_image_state=1;

}


void plsound()
{
    if(sound_var==1)
    {
        PlaySound("music2.wav",NULL,SND_ASYNC|SND_LOOP);
    }
    if(sound_var==0)
    {
        PlaySound(0,0,0);
    }
}

void wind_pos()
{
    wind_image_state=1;
    wind_x=0;
    wind_y=rand()%800;
}

int main()
{
    if(sound_var==1)
    {
        PlaySound("music2.wav",NULL,SND_ASYNC|SND_LOOP);
    }
    pattern[0].ice1.y=pattern[1].ice1.y=pattern[2].ice1.y=pattern[3].ice1.y=pattern[4].ice1.y=pattern[5].ice1.y=pattern[6].ice1.y=pattern[7].ice1.y=pattern[8].ice1.y=pattern[9].ice1.y=900;
    pattern[0].ice2.y=pattern[1].ice2.y=pattern[2].ice2.y=pattern[3].ice2.y=pattern[4].ice2.y=pattern[5].ice2.y=pattern[6].ice2.y=pattern[7].ice2.y=pattern[8].ice2.y=pattern[9].ice2.y=900;
    pattern[0].ice3.y=pattern[1].ice3.y=pattern[2].ice3.y=pattern[3].ice3.y=pattern[4].ice3.y=pattern[5].ice3.y=pattern[6].ice3.y=pattern[7].ice3.y=pattern[8].ice3.y=pattern[9].ice3.y=900;

    pattern[0].ice1.x=20,pattern[0].ice2.x=350,pattern[0].ice3.x=770;
    pattern[1].ice1.x=150,pattern[1].ice2.x=500,pattern[1].ice3.x=700;
    pattern[2].ice1.x=150,pattern[2].ice2.x=350,pattern[2].ice3.x=770;
    pattern[3].ice1.x=0,pattern[3].ice2.x=250,pattern[3].ice3.x=570;
    pattern[4].ice1.x=100,pattern[4].ice2.x=450,pattern[4].ice3.x=670;
    pattern[5].ice1.x=200,pattern[5].ice2.x=490,pattern[5].ice3.x=700;
    pattern[6].ice1.x=150,pattern[6].ice2.x=500,pattern[6].ice3.x=770;
    pattern[7].ice1.x=150,pattern[7].ice2.x=430,pattern[7].ice3.x=650;
    pattern[8].ice1.x=50,pattern[8].ice2.x=300,pattern[8].ice3.x=720;
    pattern[9].ice1.x=0,pattern[9].ice2.x=290,pattern[9].ice3.x=550;


    iSetTimer(5,timecontrol);
    iSetTimer(15000,life);
    iSetTimer(10000,wind_pos);
    iInitialize(screenwidth, screenlentgh, "MISSION ANTARCTICA IMPOSSIBLE");
    return 0;
}
