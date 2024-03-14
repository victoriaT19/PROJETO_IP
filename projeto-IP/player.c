#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "collision.h"
#include "platform.h"


const int screenWidth = 600;
const int screenHeight = 800;
Sound jumpSound;

//FUNÇÃO PARA INICIALIZAR O PLAYER
void initPlayer(Player *player){
    (*player).playerText = LoadTexture("assets/player.png");
    (*player).playerPos = (Vector2){screenWidth / 2, screenHeight / 2};
    (*player).playerScore=0;

    // Definindo a hitbox do jogador
    (*player).playerHitbox.x = (*player).playerPos.x;
    (*player).playerHitbox.y = (*player).playerPos.y;
    (*player).playerHitbox.width = (*player).playerText.width;   // largura da textura
    (*player).playerHitbox.height = (*player).playerText.height; // altura da textura
}
//FUNÇÃO PARA O TIMER
void drawTimer(double currentTime,double startTime){
     double elapsedTime=currentTime-startTime;
     DrawText(TextFormat("Timer: %.2f",elapsedTime),10,35,20,BLACK);
}

//FUNÇÃO PARA O SCORE
void drawScore(Player player){
    char Scoretext[20];
    sprintf(Scoretext, "Score: %d", player.playerScore);
    DrawText(Scoretext, 10, 10, 20, BLACK);
}

//FUNÇÃO PARA DESENHAR O PLAYER
void drawPlayer(Player player){
     DrawTexture(player.playerText, player.playerHitbox.x, player.playerHitbox.y, WHITE);
}
void movePlayer(Player *player)
{
    // MOVIMENTOS DO JOGADOR
    // ESQUERDA
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        (*player).playerPos.x -= 20;
    }
    // DIREITA
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        (*player).playerPos.x += 20;
    }
    // CASO O JOGADOR ULTRAPASSE A BORDA DIREITA
    if ((*player).playerPos.x > 600)
    {
        (*player).playerPos.x = 0; // teleporta para a esquerda
    }
    // CASO O JOGADOR ULTRAPASSE A BORDA ESQUERDA
    if ((*player).playerPos.x  < 0)
    {
        (*player).playerPos.x = 600; // teleporta para a direita
    }

    // Atualizar a posição da hitbox para corresponder à posição do jogador
    (*player).playerHitbox.x = (*player).playerPos.x;
    (*player).playerHitbox.y = (*player).playerPos.y;
}

// FUNÇÃO PARA PULO

void playerJump(Player *player, Platform *platforms)
{
    const float jumpSpeed = 18.0f; // Velocidade inicial do pulo   // Gravidade

    if (playerOnPlatform(&player, platforms)  && !player->isJumping){   

        //efeito sonoro de pulo
        jumpSound = LoadSound("assets/jump.mp3");
        PlaySound(jumpSound);
        SetSoundVolume(jumpSound, 0.5f);

        player->isJumping = true;
        player->playerSpeed = jumpSpeed; // Define a velocidade inicial do pulo
    }
    if (player->isJumping)
    {
        // Aplica a velocidade do pulo ao jogador
        player->playerPos.y -= player->playerSpeed;

        // Aplica a gravidade para diminuir a velocidade do pulo ao longo do tempo
        player->playerSpeed -= GRAVITY/5;
        

        // Verifica se o jogador atingiu o ponto mais alto do pulo
        if (player->playerSpeed <= 0)
        {
            player->isJumping = false;
        }
    }
    else
    {
        // Aplica a gravidade para fazer o jogador cair
        player->playerPos.y += GRAVITY;
    }

    // Atualiza a posição da hitbox do jogador
    player->playerHitbox.y = player->playerPos.y;
}

//FUNCAO PARA PLATFORMAS ESPECIAIS
void playerPwrJump(Player *player, Platform *platforms)
{   
    const float jumpSpeedNormal = 18.0f;
    const float jumpSpeedSpecial = 22.0f;
    bool isOnSpecialPlatform = playerOnSpecialPlatform(&player, platforms);

    if (isOnSpecialPlatform && !player->isJumping) {

        //efeito sonoro de pulo
        jumpSound = LoadSound("assets/jump.mp3");
        PlaySound(jumpSound);
        SetSoundVolume(jumpSound, 0.5f);

        player->isJumping = true;
        player->playerSpeed = jumpSpeedSpecial; // Define a velocidade inicial do pulo
    }

    if (player->isJumping) {
        // Aplica a velocidade do pulo ao jogador
        player->playerPos.y -= player->playerSpeed;

        // Aplica a gravidade para diminuir a velocidade do pulo ao longo do tempo
        player->playerSpeed -= (GRAVITY/6+0.1);

        // Verifica se o jogador atingiu o ponto mais alto do pulo
        if (player->playerSpeed <= 0) {
            player->isJumping = false;
        }
    } else {
        // Se não estiver em uma plataforma especial, usa a velocidade normal do pulo
        player->playerSpeed = jumpSpeedNormal;
    }
}

//FUNÇAO PARA VER SE TÁ NA PLATAFORMA
bool playerPlat(Player *player,Platform *platforms) {
    if(playerOnPlatform(&player,platforms)) {
       return true;
    }       
   return false;
    
}

//FUNÇÂO PARA ATT SCORE
void playerAttScore(Player *player,Platform *platforms) {
    for(int i=0;i<PLATFORMS_NUMBER;i++){
        if(playerPlat(player, platforms)){
            (*player).playerScore++;
            break;
        }
    }
}

void unloadEffects(){
    UnloadSound(jumpSound);
}


   
  
  
   
  
  
