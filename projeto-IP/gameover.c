#include <stdio.h>
#include "raylib.h"
void GameOver(int screenWidth,int screenHeight){

    int fontSize = 30;
    int textWidth = MeasureText("Game Over!Você perdeu!!!", fontSize);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2;

    //MOSTRAR A JANELA POR UM TEMPO
    for(int temp=0;temp<50;temp++){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Game Over! Você perdeu!!!", textX, textY, fontSize, RED);
        EndDrawing();
    }

 }