#include "player.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "bullet.h"

float bulletTime = 0.0f;
float bulletDelay = 1.0f;

Color pastelBlue = (Color){137, 207, 240, 255};
Color turretBlue = (Color){ 100, 149, 237, 255}; 
Color pastelRed = (Color){255,160,160,255};
Color turretRed = (Color){ 255, 105, 97, 255 };

Vector2 circleOne;
Vector2 circleTwo;


void playerInit(Player* player, int id){

    if(id == 1){
        player->alive = true;
        player->pos = (Vector2){250, 750};
        player->rec = (Rectangle){250, 750, 50, 75};
        player->turretRec = (Rectangle){500, 500, 20, 40};
        player->speed = 2.5f;
        player->rotation = 0.0f;
        player->turretRotation = 0.0f;
        player->keyUp = KEY_W;
        player->keyRight = KEY_D;
        player->keyLeft = KEY_A;
        player->turretLeft = KEY_N;
        player->turretRight = KEY_M;
        player->keyShoot = KEY_SPACE;
        player->bulletTime = GetTime();
        player->circleOne = player->pos;
        player->circleTwo = player->pos;
        player->direction = (Vector2){0,0};
        player->circleRadius = 22.5;
        player->canMoveUp = true;
        player->oldPos = player->pos;
    }
    else if(id == 2){
        player->alive = true;
        player->pos = (Vector2){1000, 750};
        player->rec = (Rectangle){1000, 750, 50, 75};
        player->turretRec = (Rectangle){750, 750, 20, 40};
        player->speed = 2.5f;
        player->rotation = 0.0f;
        player->turretRotation = 0.0f;
        player->keyUp = KEY_UP;
        player->keyRight = KEY_RIGHT;
        player->keyLeft = KEY_LEFT;
        player->turretLeft = MOUSE_LEFT_BUTTON;
        player->turretRight = MOUSE_RIGHT_BUTTON;
        player->keyShoot = MOUSE_MIDDLE_BUTTON;
        player->bulletTime = GetTime();
        player->circleOne = player->pos;
        player->circleTwo = player->pos;
        player->direction = (Vector2){0,0};
        player->circleRadius = 22.5;
        player->canMoveUp = true;
        player->oldPos = player->pos;
        }   
}

void drawPlayer(Player* player, int id){

    //Only Draws player if they are alive
    if(player->alive){
        drawBullet();

        Rectangle shadowRec = {player->rec.x, player->rec.y, player->rec.width + 2, player->rec.height + 2};
        DrawRectanglePro(shadowRec, (Vector2){26, 38.5}, player->rotation, BLACK);

        Rectangle turretRec = {player->turretRec.x, player->turretRec.y, player->turretRec.width+2, player->turretRec.height+2};

        if(id == 1){
            DrawRectanglePro(player->rec, (Vector2){25, 37.5}, player->rotation, pastelBlue);
            DrawRectanglePro(turretRec, (Vector2){11, 41}, player->turretRotation, BLACK);
            DrawRectanglePro(player->turretRec, (Vector2){10, 40}, player->turretRotation, turretBlue);
        }
        else if(id == 2){
            DrawRectanglePro(player->rec, (Vector2){25, 37.5}, player->rotation, pastelRed);
            DrawRectanglePro(turretRec, (Vector2){11, 41}, player->turretRotation, BLACK);
            DrawRectanglePro(player->turretRec, (Vector2){10, 40}, player->turretRotation, turretRed);
        }

        DrawCircleLinesV(player->circleOne, player->circleRadius, BLACK);
        DrawCircleLinesV(player->circleTwo, player->circleRadius, BLACK);
    }

    


    
}

void playerMovement(Player* player){
    player->rec.x = player->pos.x;
    player->rec.y = player->pos.y;

    //Set old pos before movement
    player->oldPos = player->pos;

    //Update turret position
    player->turretRec.x = player->rec.x;
    player->turretRec.y = player->rec.y;

    float radians = player->rotation * (PI/180.0f);
    player->direction = (Vector2){sinf(radians), -cosf(radians)};
    
    
    //Rotate movement
    if(IsKeyDown(player->keyRight)){
        player->rotation += 1.0f;
    }
    else if(IsKeyDown(player->keyLeft)){
        player->rotation -= 1.0f;
    }

    //Up Movement
    if(IsKeyDown(player->keyUp) && player->canMoveUp){
        player->pos.x += player->direction.x * player->speed;
        player->pos.y += player->direction.y * player->speed;
    }

    //Turret Rotation
    if(IsKeyDown(player->turretLeft) || IsMouseButtonDown(player->turretLeft)){
        player->turretRotation -= 1.5f;
    }
    else if(IsKeyDown(player->turretRight) || IsMouseButtonDown(player->turretRight)){
        player->turretRotation += 1.5f;
    }
   

    if((IsKeyPressed(player->keyShoot)||IsMouseButtonPressed(player->keyShoot)) && GetTime() - player->bulletTime >= bulletDelay){
        
        //Player 1 bullet
        if(player->keyShoot == KEY_SPACE){
            bulletInit( player, 1);
        }
        else if(player->keyShoot == MOUSE_MIDDLE_BUTTON){
            bulletInit(player, 2);
        }
        
        
        player->bulletTime = GetTime();
    }

    fireBullet();

}

void playerCollissions(Player* player, int level[20][30]){
    //Update player collision circles based on direction facing
    player->circleOne.x = player->pos.x - (20 * player->direction.x);
    player->circleOne.y = player->pos.y - (20 * player->direction.y);

    player->circleTwo.x = player->pos.x + (20 * player->direction.x);
    player->circleTwo.y = player->pos.y + (20 * player->direction.y);


    for(int i =  0; i < 20; i++){
        for(int j = 0; j < 30; j++){
            if(level[i][j] == 1){
                if(CheckCollisionCircleRec((player->circleTwo), player->circleRadius, (Rectangle){j * 50, i * 50, 50, 50})){
                    if(player->oldPos.x != player->pos.x || (player->oldPos.y != player->pos.y) ){
                        player->pos = player->oldPos;
                    }
                    else{
                        player->oldPos = player->pos;
                    }
                }
            }   
            
        }
    }

    //Check Bullet 
}

