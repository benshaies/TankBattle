#ifndef BULLET_H
#define BULLET_H
#include <raylib.h>
#include "player.h"

typedef struct{
    Vector2 pos;
    bool active;
    Vector2 direction;
    int player;
}Bullet;

void bulletInit( Player* player, int playerNum);

void fireBullet();

void drawBullet();

void setBullet();

void bulletCollisions(Player *player, int level[20][30], int playerNum);





#endif