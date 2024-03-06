#include <stdio.h>
#include "gamewin.h"

void GameWin(int screenWidth,int screenHeight){
    int fontSize = 30;
    int textWidth = MeasureText("Parabens!Você fez 10 pontos e venceu!!", fontSize);
    int textX = (screenWidth - textWidth) / 2;
    int textY = screenHeight / 2;

    //MOSTRAR A JANELA POR UM TEMPO
    for(int temp=0;temp<50;temp++){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Parabens!Você fez 10 pontos e venceu!!", textX, textY, fontSize, RED);
        EndDrawing();
    }
}   