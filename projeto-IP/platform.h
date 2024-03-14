#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"

#define PLATFORM_SPEED_X 5
#define PLATFORM_SPEED_Y 0

#define PLATFORMS_NUMBER 1000


typedef struct
{
    Vector2 platformPos;
    Rectangle platformHitbox;
    Vector2 platformSpeed;
    Texture2D platformText;
    Texture2D specialPlatformText;
    bool coin_platform;
    bool isMoving;
    bool isSpecial;
} Platform;

void initPlatforms(Platform *platform);
void drawPlatforms(Platform *platforms);
void generatePlatforms(Platform *platforms);
void CreateMovingPlatforms(Platform *platforms, int numPlatforms);
void movePlatforms(Platform *platforms, int numPlatforms);
void CreateSpecialPlatforms(Platform *platforms, int numPlatforms);


#endif
