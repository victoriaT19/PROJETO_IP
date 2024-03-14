#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "collision.h"
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
    InitWindow(screenWidth, screenHeight, "JOGUINHO");
    SetTargetFPS(30);
    double startTime=GetTime();

    // INICIALIZANDO PLAYER(tentar colocar em uma função depois)
    initPlayer(&player);


    //INICIALIZANDO PLATAFORMAS
    generatePlatforms(platforms);
    initPlatforms(platforms);
    CreateMovingPlatforms(platforms, PLATFORMS_NUMBER);
    CreateSpecialPlatforms(platforms,PLATFORMS_NUMBER);


    //INICIALIZANDO AUDIO
    InitAudioDevice();
    music = LoadMusicStream("assets/musiquinha.mp3");

    // Configurações da música
    PlayMusicStream(music); // Inicia a reprodução da música
    SetMusicVolume(music, 0.5f); // Define o volume da música


    // INICIALIZANDO A CAMERA
    camera.offset = (Vector2){300, 400};
    camera.target = player.playerPos;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    

    while (!WindowShouldClose())
    {
        double currentTime=GetTime();
        // atualizar player
        movePlayer(&player);
        playerJump(&player, platforms);

        // plataformas moveis
        movePlatforms(platforms, PLATFORMS_NUMBER);
        
        //plataformas pwrjump
        playerPwrJump(&player,platforms);

        // Atualizar posição da câmera para seguir o jogador
        camera.target.y = player.playerPos.y;

        //Atualizar musica
        UpdateMusicStream(music);

        // COMEÇANDO A DESENHAR COISAS NA TELA
        BeginDrawing();
        drawTimer(currentTime,startTime);
        drawGame();

        // TERMINAR O DESENHO
        EndDrawing();

        //O JOGADOR PERDEU
        if(player.playerHitbox.y>1200||(currentTime-startTime)>30.0){
            closeGame();
            GameOver(screenWidth,screenHeight);
            CloseWindow();
        }

        //O JOGADOR GANHOU 
        playerAttScore(&player, platforms);
        if(player.playerScore>=100){
            
            closeGame();
            GameWin(screenWidth,screenHeight);
            CloseWindow();
        }
    }
    // DESCARREGANDO AS TEXTURAS E FECHANDO O JOGO
    closeGame();
    CloseWindow();
    
    return 0;
}

void drawGame(){
    ClearBackground(BLUE);
    drawScore(player);
    BeginMode2D(camera); // desenha camera

    // Desenhar as plataformas com a textura
    drawPlatforms(platforms);

    // DESENHAR O PLAYER
    drawPlayer(player);
        
    EndMode2D(); // termina a camera
}

void closeGame(){

    CloseAudioDevice();
    unloadEffects();
    UnloadMusicStream(music);
    UnloadTexture(player.playerText);
    UnloadTexture(platforms->platformText);
    UnloadTexture(platforms->specialPlatformText);

}
