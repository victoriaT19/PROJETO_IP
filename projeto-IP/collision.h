#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "coins.h"

bool playerOnPlatform(Player **player, Platform *platforms);
bool playerOnSpecialPlatform(Player **player, Platform *platforms);
bool checkCoinCollision(Player **player, Coin *coins);

#endif
