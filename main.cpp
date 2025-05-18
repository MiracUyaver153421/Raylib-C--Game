#include <iostream>
#include <stdlib.h>
#include "raylib.h"
using namespace std;
#define SCREENWIDTH 1300
#define SCREENHEIGHT 800
#include <vector>
#define RECTCOUNT 8
#define  RECTHEIGHT (SCREENHEIGHT/RECTCOUNT)
#define BORDER 100
Texture2D soldier;
class gameObject{
    public:
    Texture2D soldier;
    Vector2 position;
    Rectangle source;

    int currentFrame;
    int lastFrame;
    float frameWidth;
    float frameHeihgt;
    float frameTime ;
    float timer;
};


class Enemies: public gameObject{
    public:
    int enemyCounterBorder=0;
    public:
    void initialize(){

        position = {SCREENWIDTH,0};
        Image Image = LoadImage("robosheetreverse.png");
        ImageFormat(&Image, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        Color backgroundColor = GetImageColor(Image,10,10);
        ImageColorReplace(&Image,backgroundColor,BLANK);
        soldier = LoadTextureFromImage(Image);
            lastFrame=0;
            currentFrame=6;
            frameWidth = 49.5f;
            frameHeihgt = soldier.height/11.f;
            frameTime = 0.08f;
            timer=0.f;
            if (soldier.width == 0 || soldier.height == 0) {
    std::cout << "DİKKAT: Düşman sprite yüklenemedi!" << std::endl;
}
    }

    void draw(){
        source = {currentFrame * frameWidth+183.5,soldier.height/11.0f,(float)(soldier.width-38.f)/9.0f,(float)1.0f*(soldier.height/11.0f)};//part of photo
        DrawTextureRec(soldier,source,position,RED);


        timer += GetFrameTime();
        if(timer>=frameTime){
            timer =0;
            currentFrame--;
            source.x = currentFrame*frameWidth;
            position.x-=10;
            if(currentFrame==lastFrame)currentFrame=6;
            if(position.x>SCREENWIDTH){

            };
        }
    }


};



class Soldiers:public gameObject{

    public:
    void initialize(){
    position={0,0};
    Image Image = LoadImage("robosheet.png");
    ImageFormat(&Image, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color backgroundColor = GetImageColor(Image,10,10);
    ImageColorReplace(&Image,backgroundColor,BLANK);
    soldier = LoadTextureFromImage(Image);

        lastFrame=7;
        currentFrame=0;
        frameWidth = 49.5f;
        frameHeihgt = soldier.height/11.f;
        frameTime = 0.02f;
        timer=0.f;
    }

    void draw(){
        source = {currentFrame * frameWidth,soldier.height/11.0f,(float)(soldier.width-38.f)/9.0f,(float)1.0f*(soldier.height/11.0f)};//part of photo
        DrawTextureRec(soldier,source,position,WHITE);


        timer += GetFrameTime();
        if(timer>=frameTime){
            timer =0;
            currentFrame++;
            source.x = currentFrame*frameWidth;
            position.x+=10;
            if(currentFrame==lastFrame)currentFrame=0;
            if(position.x>SCREENWIDTH){

            };
        }
    }

};
vector<Soldiers> soldierList;
vector<Enemies> enemyList;

int main()
{
    bool isDrawing = false;
    int remainderS = 0;
    int remainderE = 0;
    int roboCounter =0;
    int enemyCounter =0;
    int collaptionCounter =0;
    int crossBorderCounter=0;
    InitWindow(SCREENWIDTH,SCREENHEIGHT,"Protect The Border");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();

        Color color;

        for (int i = 0; i < RECTCOUNT; i++) {
            color = (i%2==0)? WHITE:GRAY;
            DrawRectangle(0, i * RECTHEIGHT,SCREENWIDTH, RECTHEIGHT, color);
        }

        DrawRectangle(BORDER,0,10,SCREENHEIGHT,RED);//border of our soldiers
         if(IsWindowReady()&&enemyCounter<25){
            Enemies e;
            e.initialize();
            e.position.y = GetRandomValue(0,800);
            remainderE = e.position.y/RECTHEIGHT;
            e.position.y = remainderE*RECTHEIGHT;
            enemyList.push_back(e);cout << "Enemy eklendi! Sayı: " << enemyList.size() << std::endl;

            enemyCounter++;


        }
        for (auto &e : enemyList) {
                e.draw();

        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&roboCounter<25) {

            Soldiers s;
            s.initialize();
            s.position.y = GetMouseY();
            remainderS = s.position.y/RECTHEIGHT;
            s.position.y = remainderS * RECTHEIGHT;
            soldierList.push_back(s);
            string text = "Robot Sayısı: " + to_string(roboCounter);
            DrawText(text.c_str(),0,0,8,BLACK);
            roboCounter++;
        }

            for (auto &s : soldierList) {
                s.draw();
            }

        for (int i = 0; i < soldierList.size(); i++) {
            Rectangle soldierRect = {
            soldierList[i].position.x,
            soldierList[i].position.y,
            soldierList[i].frameWidth,
            soldierList[i].frameHeihgt
            };

            for (int j = 0; j < enemyList.size(); j++) {
                Rectangle enemyRect = {
                enemyList[j].position.x,
                enemyList[j].position.y,
                enemyList[j].frameWidth,
                enemyList[j].frameHeihgt
                };

                if (CheckCollisionRecs(soldierRect, enemyRect)) {
                    soldierList.erase(soldierList.begin() + i);
                    enemyList.erase(enemyList.begin() + j);
                    i--;
                    collaptionCounter++;


                break;
                }
            }
        }
        for (int i = 0; i < enemyList.size(); i++) {
            if (enemyList[i].position.x <= BORDER) {
                enemyList.erase(enemyList.begin() + i);
                crossBorderCounter++;
                i--;
            }
        }


        if (crossBorderCounter >= 3 ) {
            BeginDrawing();
                ClearBackground(BLACK);  // Ekranı siyaha boyamak istersen
                DrawText("GAME OVER", SCREENWIDTH/2 - 100, SCREENHEIGHT/2, 40, RED);
            EndDrawing();

            WaitTime(5.0f);
            CloseWindow();
        }
        if(collaptionCounter >= 23){
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("GAME COMPLETED", SCREENWIDTH/2 - 100, SCREENHEIGHT/2, 40, GREEN);
            EndDrawing();

            WaitTime(5.0f);
            CloseWindow();
        }
        EndDrawing();

    }
    UnloadTexture(soldier);
    CloseWindow();


    return 0;
}
