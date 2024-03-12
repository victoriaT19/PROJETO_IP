#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "coins.h"
#include "collision.h"
#include "gameover.h"

#include "gamewin.h"

void drawScore(Player player){
    char Scoretext[20];
    sprintf(Scoretext, "Score: %d", player.playerScore);
    DrawText(Scoretext, 10, 10, 20, BLACK);
}

int main()
{
    // INICIALIZANDO TELA DO JOGO
    const int screenWidth = 600;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "JOGUINHO");
    SetTargetFPS(30);

    // INICIALIZANDO PLAYER(tentar colocar em uma função depois)
    Player player;
    player.playerText = LoadTexture("assets/player.png");
    player.playerPos = (Vector2){screenWidth / 2, screenHeight / 2};
    player.playerScore=0;

    // Definindo a hitbox do jogador
    player.playerHitbox.x = player.playerPos.x;
    player.playerHitbox.y = player.playerPos.y;
    player.playerHitbox.width = player.playerText.width;   // largura da textura
    player.playerHitbox.height = player.playerText.height; // altura da textura

    //INICIALIZANDO PLATAFORMAS
    Platform platforms[PLATFORMS_NUMBER];
    Texture2D platformText = LoadTexture("assets/PlatformPlaceHolder.png");
    generatePlatforms(platforms);
    CreateMovingPlatforms(platforms, PLATFORMS_NUMBER);
    


    // INICIALIZANDO A CAMERA
    Camera2D camera;
    camera.offset = (Vector2){300, 400};
    camera.target = player.playerPos;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    // INICIALIZANDO AS MOEDAS
    Coin coins[COIN_MAX];
    inicializeCoins();
    generateCoins(platforms,PLATFORMS_NUMBER);

    while (!WindowShouldClose())
    {
        // atualizar player
        movePlayer(&player);
        playerJump(&player, platforms);

        // plataformas moveis
        movePlatforms(platforms, PLATFORMS_NUMBER);

        // Atualizar posição da câmera para seguir o jogador
        camera.target.y = player.playerPos.y;

        // COMEÇANDO A DESENHAR COISAS NA TELA
        BeginDrawing();
        ClearBackground(BLUE);
        drawScore(player);
        BeginMode2D(camera); // desenha camera

        // Desenhar as plataformas com a textura
        for (int i = 0; i < PLATFORMS_NUMBER; i++)
        {
            DrawTexture(platformText, platforms[i].platformHitbox.x, platforms[i].platformHitbox.y, WHITE);
        }
        // DESENHAR O PLAYER
        DrawTexture(player.playerText, player.playerHitbox.x, player.playerHitbox.y, WHITE);
        
        //DESENHAR AS MOEDAS
        drawCoins();

        EndMode2D(); // termina a camera
       
        // TERMINAR O DESENHO
        EndDrawing();

        //O JOGADOR PERDEU
        if(player.playerHitbox.y>1200){
           UnloadTexture(player.playerText);
           UnloadTexture(platformText);
           UnloadTexture(coins->coinText);
           GameOver(screenWidth,screenHeight);
           CloseWindow();
        }
        //JOGADOR GANHOU(SCORE=10- PD MUDAR ISSO DPS)
        
        playeronCoin(&player,coins);
        if(player.playerScore>=10){
            UnloadTexture(player.playerText);
            UnloadTexture(platformText);
            UnloadTexture(coins->coinText);
            //MUDAR DPS O GAMEWIN PRA FICAR MAIS BONITO
            GameWin(screenWidth,screenHeight);
            CloseWindow();
        }
    }
    // DESCARREGANDO AS TEXTURAS E FECHANDO O JOGO
    UnloadTexture(player.playerText);
    UnloadTexture(platformText);
    UnloadTexture(coins->coinText);
    CloseWindow();
    
    return 0;
}

