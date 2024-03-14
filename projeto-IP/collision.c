#include "collision.h"
#include "player.h"



//FUNÇÃO PARA VERIFICAR SE O PLAYER ESTÁ NA PLATAFORMA
bool playerOnPlatform(Player **player, Platform *platforms)
{
    for (int i = 0; i < PLATFORMS_NUMBER; i++)
    {
        if (CheckCollisionRecs((*(*player)).playerHitbox, platforms[i].platformHitbox))
        {
            // SE TIVER RETORNAR VERDADEIRO
            return true;
        }
    }
    return false;
}


bool playerOnSpecialPlatform(Player **player, Platform *platforms)
{
    for (int i = 0; i < PLATFORMS_NUMBER; i++)
    {
        if (platforms[i].isSpecial && CheckCollisionRecs((*(*player)).playerHitbox, platforms[i].platformHitbox))
        {
            
            // SE TIVER RETORNAR VERDADEIRO
            return true;
        }
    }
    return false;
}



