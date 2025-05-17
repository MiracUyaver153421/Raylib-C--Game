#include <iostream>
#include <stdlib.h>
#include "raylib.h"
using namespace std;
#define SCREENWIDTH 1000
#define SCREENHEIGHT 800
#include <vector>


 class Object{



};

class Enemies: Object{

};


class Soldiers: Object{



};



int main()
{


    InitWindow(SCREENWIDTH,SCREENHEIGHT,"Calhanoglu's Goal");
    SetTargetFPS(60);

    Image soldierImage = LoadImage("robosheet.png");
    ImageFormat(&soldierImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color backgroundColor = GetImageColor(soldierImage,10,10);
    ImageColorReplace(&soldierImage,backgroundColor,BLANK);

    Texture2D soldier = LoadTextureFromImage(soldierImage);
    Rectangle source = {0,soldier.height/11.0f,(float)(soldier.width-38.f)/9.0f,(float)1.0f*(soldier.height/11.0f)};//part of photo
    Vector2 position = {0,0};//position in window


    int rectCount = 8;
    int rectHeight = SCREENHEIGHT / rectCount;
    int currentFrame=0;
    int currentCount=7;
    float frameWidth = 49.5;
    float frameHeihgt = soldier.height/11;
    float frameTime = 0.02f;
    float timer=0.f;


    while(!WindowShouldClose()){
        BeginDrawing();

        Color color;

        for (int i = 0; i < rectCount; i++) {
            color = (i%2==0)? WHITE:GRAY;
            DrawRectangle(0, i * rectHeight/*80*/ ,SCREENWIDTH, rectHeight, color);
        }

        DrawRectangle(100,0,10,SCREENHEIGHT,RED);//border of our soldiers

        DrawTextureRec(soldier,source,position,WHITE);
        timer += GetFrameTime();
        if(timer>=frameTime){
            timer =0;
            currentFrame++;
            source.x = currentFrame*frameWidth;
            position.x+=10;
            if(currentFrame==currentCount)currentFrame=0;
            if(position.x>SCREENWIDTH)position.x=0;
        }


        WaitTime(0.02);
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
