#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"

#define PLATFORMS_NUMBER 1000

typedef struct
{
    Vector2 platformPos;
    Rectangle platformHitbox;
} Platform;

void generatePlatforms(Platform *platforms);

#endif
