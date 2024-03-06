#include "raylib.h"
#include "player.h"
#include "coins.h"
#include "collision.h"
#include "platform.h"

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

    if (playerOnPlatform(&player, platforms)  && !player->isJumping)
    {
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
