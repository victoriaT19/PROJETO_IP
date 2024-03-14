#include <stdio.h>
#include "gamewin.h"

void GameWin(int screenWidth,int screenHeight){
    
        Texture2D frames[27]={
        LoadTexture("assets/YouWin-01.png"),
        LoadTexture("assets/YouWin-02.png"),
        LoadTexture("assets/YouWin-03.png"),
        LoadTexture("assets/YouWin-04.png"),
        LoadTexture("assets/YouWin-05.png"),
        LoadTexture("assets/YouWin-06.png"),
        LoadTexture("assets/YouWin-07.png"),
        LoadTexture("assets/YouWin-08.png"),
        LoadTexture("assets/YouWin-09.png"),
        LoadTexture("assets/YouWin-10.png"),
        LoadTexture("assets/YouWin-11.png"),
        LoadTexture("assets/YouWin-12.png"),
        LoadTexture("assets/YouWin-13.png"),
        LoadTexture("assets/YouWin-14.png"),
        LoadTexture("assets/YouWin-15.png"),
        LoadTexture("assets/YouWin-16.png"),
        LoadTexture("assets/YouWin-17.png"),
        LoadTexture("assets/YouWin-18.png"),
        LoadTexture("assets/YouWin-19.png"),
        LoadTexture("assets/YouWin-20.png"),
        LoadTexture("assets/YouWin-21.png"),
        LoadTexture("assets/YouWin-22.png"),
        LoadTexture("assets/YouWin-23.png"),
        LoadTexture("assets/YouWin-24.png"),
        LoadTexture("assets/YouWin-25.png"),
        LoadTexture("assets/YouWin-26.png"),
        LoadTexture("assets/YouWin-27.png"),
    };
    int currentFrame=0;
    int frameCounter=0;
    int frameSpeed=8;


    //MOSTRAR A JANELA POR UM TEMPO
    for(int temp=0;temp<150;temp++){
         frameCounter++;
        if (frameCounter >= (30 / frameSpeed)) {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame >= 27) currentFrame = 0;
        }
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(frames[currentFrame], screenWidth / 2 - frames[currentFrame].width / 2, screenHeight / 2 - frames[currentFrame].height / 2, WHITE);
        

        EndDrawing();
    }
     for (int i = 0; i < 27; i++) {
        UnloadTexture(frames[i]);
    }
}   
