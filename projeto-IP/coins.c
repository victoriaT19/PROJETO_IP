#include "raylib.h"
#include "platform.h"
#include "coins.h"
#include "player.h"
#include "collision.h"

Coin coins[COIN_MAX];

//FUNÇÃO PARA INICIALIZAR AS MOEDAS
void inicializeCoins(){
   Texture2D coinTexture= LoadTexture("assets/moeda.png");

   for(int i=0;i<COIN_MAX;i++){
    coins[i].coinText= coinTexture;
    coins[i].coin_active=false;

   }
}

//FUNÇÃO PARA DESENHAR AS MOEDAS
void drawCoins(){
    for(int i=0;i<COIN_MAX;i++){
        if(coins[i].coin_active==true){
            DrawTexture(coins[i].coinText, coins[i].coinPos.x, coins[i].coinPos.y, WHITE);
        }
    }
}

//FUNÇÃO PARA GERAR AS MOEDAS
void generateCoins(Platform *platforms, int numPlatforms){
    int CoinX;
    int CoinY;
    for(int i=0;i<numPlatforms;i++){
        //CHANCE DE 20%
        if(GetRandomValue(0,100)<20){
          CoinX= platforms[i].platformHitbox.x -5 ;
          CoinY = platforms[i].platformHitbox.y-50;
        
        for(int j=0;j<COIN_MAX;j++){
            if(!coins[j].coin_active){
                coins[j].coin_active=true;
                coins[j].coinPos=(Vector2){CoinX,CoinY};
                /// Atualizar a posição da hitbox para corresponder à posição das moedas
                coins[j].coinHitbox.x=CoinX;
                coins[j].coinHitbox.y=CoinY;
                coins[j].coinHitbox.height=coins[j].coinText.height;
                coins[j].coinHitbox.width=coins[j].coinText.width;
                break;
            }
        }
        }
    }
}
//VERIFICAR SE O PLAYER PEGOU A MOEDA(ATUALIZA O SCORE)
void playeronCoin(Player *player, Coin *coins) {
    for(int i = 0; i < COIN_MAX; i++) {
        if(coins[i].coin_active && checkCoinCollision(&player, &coins[i])) {
            player->playerScore++;
        }
    }
}
