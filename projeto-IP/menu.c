#include "raylib.h"
#include "menu.h"


void createButton(Button *button, float x, float y, float width, float height, Color color, const char *text) {
    (*button).bounds = (Rectangle){x, y, width, height};
    (*button).color = color; //substitui por textura
    (*button).text = text;
}

bool isMouseOverButton(Button *button) {
    Vector2 mousePos = GetMousePosition();
    return (mousePos.x >= (*button).bounds.x && mousePos.x <= (*button).bounds.x + (*button).bounds.width &&
            mousePos.y >= (*button).bounds.y && mousePos.y <= (*button).bounds.y + (*button).bounds.height);
}

bool isButtonClicked(Button *button) {
    return isMouseOverButton(button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void drawButton(Button *button) {
    DrawRectangleRec((*button).bounds, (*button).color);
    DrawText((*button).text, (*button).bounds.x + (*button).bounds.width / 2 - MeasureText((*button).text, 20) / 2,
            (*button).bounds.y + (*button).bounds.height / 2 - 10, 20, WHITE);
}

