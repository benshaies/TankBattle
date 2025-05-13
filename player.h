#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

typedef struct{
    bool alive;
    Vector2 pos;
    Rectangle rec;
    Rectangle turretRec;
    float speed;
    float rotation;
    float turretRotation;
    int keyUp, keyRight, keyLeft, turretLeft, turretRight, keyShoot;
    float bulletTime;
    Vector2 circleOne, circleTwo;
    float circleRadius;
    Vector2 direction;
    bool canMoveUp, canRotateLeft, canRotateRight;
    Vector2 oldPos;
    
}Player;

void playerInit(Player* player1, int id);

void drawPlayer(Player* player, int id);

void playerMovement(Player* player);

void playerCollissions(Player* player, int level[20][30]);



#endif