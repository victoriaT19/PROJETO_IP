#include <stdio.h>
#include "raylib.h"
void GameOver(int screenWidth,int screenHeight){

        Texture2D frames[14]={
        LoadTexture("assets/GameOver-01.png"),
        LoadTexture("assets/GameOver-02.png"),
        LoadTexture("assets/GameOver-03.png"),
        LoadTexture("assets/GameOver-04.png"),
        LoadTexture("assets/GameOver-05.png"),
        LoadTexture("assets/GameOver-06.png"),
        LoadTexture("assets/GameOver-07.png"),
        LoadTexture("assets/GameOver-08.png"),
        LoadTexture("assets/GameOver-09.png"),
        LoadTexture("assets/GameOver-10.png"),
        LoadTexture("assets/GameOver-11.png"),
        LoadTexture("assets/GameOver-12.png"),
        LoadTexture("assets/GameOver-13.png"),
        LoadTexture("assets/GameOver-14.png"),
        
    };
    int currentFrame=0;
    int frameCounter=0;
    int frameSpeed=8;


    //MOSTRAR A JANELA POR UM TEMPO
    for(int temp=0;temp<100;temp++){
         frameCounter++;
        if (frameCounter >= (30 / frameSpeed)) {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame >= 14) currentFrame = 0;
        }
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(frames[currentFrame], screenWidth / 2 - frames[currentFrame].width / 2, screenHeight / 2 - frames[currentFrame].height / 2, WHITE);
        

        EndDrawing();
    }
     for (int i = 0; i < 14; i++) {
        UnloadTexture(frames[i]);
    }

 }
