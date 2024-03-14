#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "collision.h"
#include "menu.h"
#include "gameover.h"
#include "gamewin.h"

Music music;
Player player;
Platform platforms[PLATFORMS_NUMBER];
Camera2D camera;

void drawGame();
void closeGame();

int main()
{
    // INICIALIZANDO TELA DO JOGO
    const int screenWidth = 600;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "BUNNY LEAP");
    SetTargetFPS(30);
    double menuExitTime=0.0;

    // INICIALIZANDO PLAYER(tentar colocar em uma função depois)
    initPlayer(&player);

    // INICIALIZANDO PLATAFORMAS
    generatePlatforms(platforms);
    initPlatforms(platforms);
    CreateMovingPlatforms(platforms, PLATFORMS_NUMBER);
    CreateSpecialPlatforms(platforms, PLATFORMS_NUMBER);

    // INICIALIZANDO AUDIO
    InitAudioDevice();
    music = LoadMusicStream("assets/musiquinha.mp3");
    // Configurações da música
    PlayMusicStream(music);      // Inicia a reprodução da música
    SetMusicVolume(music, 0.5f); // Define o volume da música

    // INICIALIZANDO A CAMERA
    camera.offset = (Vector2){300, 400};
    camera.target = player.playerPos;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
   
    Texture2D backgroundTexture=LoadTexture("assets/sky_day.png");
    Texture2D nameText=LoadTexture("assets/EmptyButton.png");
    
    Button playButton;
    createButton(&playButton, 200, 300, 200, 50, GREEN, "Play");
    Button exitButton;
    createButton(&exitButton, 200, 400, 200, 50, MAROON, "Sair");
    bool gameRunning = false;

    while (!WindowShouldClose())
    {
       
        if (!gameRunning){
        
            // Verifica se o botão "Play" foi clicado
            if (isButtonClicked(&playButton))
            {
                gameRunning = true;
                menuExitTime=GetTime();
            }

            // Verifica se o botão "Sair" foi clicado
            if (isButtonClicked(&exitButton))
            {
                break;
            }

            // Altera a cor do botão "Play" quando o mouse está sobre ele
            if (isMouseOverButton(&playButton))
            {
                playButton.color = DARKGREEN;
            }
            else
            {
                playButton.color = GREEN;
            }

            // Altera a cor do botão "Sair" quando o mouse está sobre ele
            if (isMouseOverButton(&exitButton))
            {
                exitButton.color = MAROON;
            }
            else
            {
                exitButton.color = RED;
            }
            
            BeginDrawing();

            ClearBackground(RAYWHITE);
            //Desenha o background do menu
            for (int x = 0; x < screenWidth; x += backgroundTexture.width)
            {
                for (int y = 0; y < screenHeight; y += backgroundTexture.height)
                {
                    DrawTexture(backgroundTexture, x, y, WHITE);
                }
            }
            
            //Controles e Instruções
            DrawText("Instruções:", 20, 615, 20, BLACK);
            DrawText("Ajude o coelho Cacau a pular por plataformas de doces instáveis na \nfábrica de chocolate! Ele precisa fazer 100 pontos antes que o tempo \nde 30 segundos acabe", 20, 640, 15, BLACK);
            DrawText("Controles:", 20, 690, 20, BLACK);
            DrawText("-Aperte A ou <- para mover para esquerda", 20, 715, 15, BLACK);
            DrawText("-Aperte D ou -> para mover para direita", 20, 735, 15, BLACK);

            // Desenha os botões
            
           DrawTexturePro(nameText, (Rectangle){ 0, 0, nameText.width, nameText.height },
                           (Rectangle){ screenWidth / 2 - nameText.width / 4, screenHeight / 8, nameText.width / 2, nameText.height / 2 }, 
                           (Vector2){ 0, 0 }, 0, BLACK);

            // Desenha o texto "MENU" centralizado na parte superior do menu
            DrawText("BUNNY LEAP", screenWidth / 2 - MeasureText("BUNNY LEAP", 40) / 2, screenHeight/6, 40, BLACK);
             
            
            drawButton(&playButton);
            drawButton(&exitButton);

            EndDrawing();

        }
        else {

            double currentTime = GetTime();
            
            // atualizar player
            movePlayer(&player);
            playerJump(&player, platforms);

            // plataformas moveis
            movePlatforms(platforms, PLATFORMS_NUMBER);

            // plataformas pwrjump
            playerPwrJump(&player, platforms);

            // Atualizar posição da câmera para seguir o jogador
            camera.target.y = player.playerPos.y;

            // Atualizar musica
            UpdateMusicStream(music);

       
            
            // COMEÇANDO A DESENHAR COISAS NA TELA
            BeginDrawing();
            drawGame();
            drawTimer(currentTime,menuExitTime);

            // TERMINAR O DESENHO
            EndDrawing();

            // O JOGADOR PERDEU
            if (player.playerHitbox.y > 1200||(currentTime-menuExitTime)>30.0)
            {
                closeGame();
                GameOver(screenWidth, screenHeight);
                CloseWindow();
            }
             
            //O JOAGADOR GANHOU
            playerAttScore(&player, platforms);
            if(player.playerScore>=100){

                closeGame();
                GameWin(screenWidth, screenHeight);
                CloseWindow();
            }
        }
    }
    
    // DESCARREGANDO AS TEXTURAS E FECHANDO O JOGO
    closeGame();
    UnloadTexture(nameText);
    UnloadTexture(backgroundTexture);

    CloseWindow();

    return 0;
}

void drawGame()
{ 
   const int screenWidth = 600;
   const int screenHeight = 800;
    //Desenhar o background
   Texture2D backgameText=LoadTexture("assets/background.png");
   ClearBackground(RAYWHITE);
   for (int x = 0; x < screenWidth; x += backgameText.width)
    {
        for (int y = 0; y < screenHeight; y += backgameText.height)
            {
                DrawTexture(backgameText, x, y, WHITE);
            }
    }
    drawScore(player);
    BeginMode2D(camera); // desenha camera

    // Desenhar as plataformas com a textura
    drawPlatforms(platforms);

    // DESENHAR O PLAYER
   
    drawPlayer(player);
    UnloadTexture(backgameText);
    EndMode2D(); // termina a camera
}

void closeGame()
{

    CloseAudioDevice();
    unloadEffects();
    UnloadMusicStream(music);
    UnloadTexture(player.playerText);
    UnloadTexture(platforms->platformText);
    UnloadTexture(platforms->specialPlatformText);
}

