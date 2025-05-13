#include <raylib.h>
#include "bullet.h"
#include "math.h"


Bullet bullet[10];

Color bulletBlue = (Color){70, 130, 180, 255}; // steel blue  
Color bulletRed = (Color){220, 20, 60, 255}; // crimson  

void setBullet(){
    for(int i = 0; i < 10; i++){
        bullet[i].active = false;
    }
}

void bulletInit(Player* player, int playerNum){
    for(int i = 0; i < 10; i++){

        if(!bullet[i].active){
            bullet[i].pos = (Vector2){player->turretRec.x, player->turretRec.y};
            float radians = player->turretRotation * (PI/180.0f);
            bullet[i].direction = (Vector2){sinf(radians), -cosf(radians)};
            bullet[i].active = true;
            bullet->player = playerNum;
            break;
        }
    } 
}

void fireBullet(){
    for(int i = 0; i < 10; i++){
        if(bullet[i].active){
            bullet[i].pos.x += bullet[i].direction.x * 10.0f;
            bullet[i].pos.y += bullet[i].direction.y * 10.0f;

            if(bullet[i].pos.x < 0 || bullet[i].pos.x > 1500 || bullet[i].pos.y < 0 || bullet[i].pos.y > 1000){
                bullet[i].active = false;
            }
        }
    }
}

void drawBullet(){
    for(int i = 0; i < 10; i++){
        if(bullet[i].active){
            if(bullet[i].player == 1){
                DrawCircleV(bullet[i].pos, 10, bulletBlue);
                DrawCircleLinesV(bullet[i].pos, 10, BLACK);
            }
            else if(bullet[i].player == 2){
                DrawCircleV(bullet[i].pos, 10, bulletRed);
                DrawCircleLinesV(bullet[i].pos, 10, BLACK);
            }   
            
        }
    }
}

void bulletCollisions(Player *player, int level[20][30], int playerNum){
    for(int i = 0; i < 10; i++){
        if(bullet[i].active){
            if(CheckCollisionCircles(bullet[i].pos, 10, player->circleOne, player->circleRadius) || (CheckCollisionCircles(bullet[i].pos, 10, player->circleTwo, player->circleRadius))){
                //Checks if bullet is fired by oponent and disables it
                if(bullet->player == playerNum){
                    bullet->active = false;
                    player->alive = false;
                }
            }
        }
        
    }
}