#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "platform.h"

#define GRAVITY 5

typedef struct
{
    Vector2 playerPos;
    float playerSpeed;
    Texture2D playerText;
    Rectangle playerHitbox;
    bool isJumping;
    int playerScore;
} Player;

void initPlayer(Player *player);
void drawScore(Player player);
void drawPlayer(Player player);
void playerPwrJump(Player *player, Platform *platforms);
void movePlayer(Player *player);
void playerJump(Player *player, Platform *platforms);
void unloadEffects();


#endif
