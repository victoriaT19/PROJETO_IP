#include "raylib.h"
#include "platform.h"

void initPlatforms(Platform *platforms){
    (*platforms).platformText = LoadTexture("assets/darkBluePlatform.png");
    (*platforms).specialPlatformText= LoadTexture("assets/blueSpecialPlatform.png");
     
}

void drawPlatforms(Platform *platforms){
    for (int i = 0; i < PLATFORMS_NUMBER; i++)
        {   if(platforms[i].isSpecial){
             DrawTexture((*platforms).specialPlatformText, platforms[i].platformHitbox.x, platforms[i].platformHitbox.y, WHITE);
            }
            else{
            DrawTexture((*platforms).platformText, platforms[i].platformHitbox.x, platforms[i].platformHitbox.y, WHITE);
            }
        }
}

void generatePlatforms(Platform *platforms)
{
    int maxPlatformHeight = 1000;
    for (int i=0 ; i < PLATFORMS_NUMBER; i++)
    {
        Rectangle tempRandomPlatform = { GetRandomValue(0, 600), maxPlatformHeight -= 50, 70, 10};
        platforms[i].platformHitbox = tempRandomPlatform;
        platforms[i].isSpecial= false;
    }
}
// TORNAR ALGUMAS PLATAFORMAS MOVEIS
void CreateMovingPlatforms(Platform *platforms, int numPlatforms){
    for (int i = 0; i < numPlatforms; i++)
    {
        if(GetRandomValue(0,100) == 13){
            platforms[i].platformSpeed.x = PLATFORM_SPEED_X;
            platforms[i].platformSpeed.y = PLATFORM_SPEED_Y;
            platforms[i].isMoving = true; 

        }
        else
        {
            platforms[i].isMoving = false;
        }
    }
    
}
//MOVIMENTOS DAS PLATAFORMAS MOVEIS
void movePlatforms(Platform *platforms, int numPlatforms)
{
    for (int i = 0; i < numPlatforms; i++)
    {
        if (platforms[i].isMoving)
        {
            // Atualiza a posição apenas se a plataforma estiver marcada como móvel
            platforms[i].platformPos.x += platforms[i].platformSpeed.x;

            // Verifica se a plataforma ultrapassou os limites
            if (platforms[i].platformPos.x < 0 || platforms[i].platformPos.x + platforms[i].platformHitbox.width >= 600) {
                platforms[i].platformSpeed.x *= -1;
            }

            // Atualiza a posição da hitbox para corresponder à posição da plataforma
            platforms[i].platformHitbox.x = platforms[i].platformPos.x;
            
        }
    }
}
//TORNAR ALGUMAS PLATAFORMAS ESPECIAIS(PWR-UPS)
void CreateSpecialPlatforms(Platform *platforms, int numPlatforms){
    for (int i = 0; i < numPlatforms; i++)
    {  
        if(GetRandomValue(0,100)<20){
            platforms[i].isSpecial = true; 

        }
    }
    
}

