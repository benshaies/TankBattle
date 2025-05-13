#include <raylib.h>
#include <stdio.h>
#include "player.h"
#include "bullet.h"


const int screenWidth = 1500;
const int screenHeight = 1000;

//Create player variables
Player player1;
Player player2;


int level[20][30] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void drawLevel(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j++){
            if(level[i][j] == 1){
                int x = 50 * j;
                int y = 50 * i;
                DrawRectangle(x, y, 50, 50, (Color){  200, 200, 220, 255});
                
            }
        }
    }
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j++){
            if(level[i][j] == 1){
                int x = 50 * j;
                int y = 50 * i;
                DrawRectangleLines(x, y, 50, 50, (Color){ 60, 70, 80, 255 });
            }
        }
    }
}

void draw(){
    BeginDrawing();

    
    drawLevel();

    ClearBackground((Color){ 250, 245, 235, 255 });

    drawPlayer(&player1, 1);
    drawPlayer(&player2, 2);

    DrawFPS(0,0);

    EndDrawing();
}

void init(){
    ClearWindowState(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Raylib Sample Project");
    SetTargetFPS(60);

    //Player init
    playerInit(&player1, 1);
    playerInit(&player2, 2);
    //Initialize bullet array
    setBullet();
    
}

int main(void){
    
    init();
    while(!WindowShouldClose()){
        
        playerMovement(&player1);
        playerMovement(&player2);
        playerCollissions(&player1, level);
        playerCollissions(&player2, level);
        bulletCollisions(&player1, level, 2);
        bulletCollisions(&player2, level, 1);
        draw();
    }
}