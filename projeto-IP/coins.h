#ifndef COINS_H
#define COINS_H

#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "platform.h"

#define COIN_MAX  1000

typedef struct{
   Vector2 coinPos;
   Texture2D coinText;
   Rectangle coinHitbox;
   bool coin_active;
} Coin;

void inicializeCoins();
void drawCoins();
void generateCoins(Platform *platforms, int numPlatforms);
void playeronCoin(Player *player, Coin *coins);
#endif