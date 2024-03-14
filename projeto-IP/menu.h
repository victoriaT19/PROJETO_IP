#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct Button {
    Rectangle bounds;
    Texture2D platformText;
    Color color; //substitui por textura
    const char *text;
} Button;

void createButton(Button *button, float x, float y, float width, float height, Color color, const char *text);
bool isMouseOverButton(Button *button);
bool isButtonClicked(Button *button);
void drawButton(Button *button);

#endif