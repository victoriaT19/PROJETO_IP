#include "raylib.h"
#include "platform.h"

void generatePlatforms(Platform *platforms)
{
    int maxPlatformHeight = 1000;
    for (int i=0 ; i < PLATFORMS_NUMBER; i++)
    {
        Rectangle tempRandomPlatform = { GetRandomValue(0, 600), maxPlatformHeight -= 50, 50, 10};
        platforms[i].platformHitbox = tempRandomPlatform;
    }
}
/*void generatePlatforms(Platform *platforms)
{
    int maxPlatformHeight = 1000;
    int i = 0; 

        for(i;i<=PLATFORMS_NUMBER;i++){ 
            Rectangle tempRandomPlatform = { GetRandomValue(0, 600), maxPlatformHeight -= 50, 50, 10};
            platforms[i].platformHitbox = tempRandomPlatform;

            if (i >= PLATFORMS_NUMBER) // Resetar o contador se exceder o número máximo de plataformas
             {
                i = 0; // restart
            }
        }
    }
*/


