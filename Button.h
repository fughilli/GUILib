#ifndef BUTTON_H
#define BUTTON_H

#include "Energia.h"
#include "GUI.h"

#define BUTTON_DEFAULT_BACKGROUND_COLOR GUI_DEFAULT_BACKGROUND_COLOR
#define BUTTON_DEFAULT_FOREGROUND_COLOR GUI_DEFAULT_FOREGROUND_COLOR
#define BUTTON_DEFAULT_TEXT_COLOR       GUI_DEFAULT_FOREGROUND_COLOR
#define BUTTON_DEFAULT_MARGIN           4

class Button : public GUIElement
{
private:
    uint16_t textWidth, textHeight;
    bool autoResize;
protected:
    bool checkBounds(uint16_t touchX, uint16_t touchY);

    void injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType);

    void draw(bool clearBeforeDraw);

    void initialize(void);

public:
    char * label;
    Button(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, char * _label,
           uint16_t _width = 0, uint16_t _height = 0,
           uint16_t bg_color = BUTTON_DEFAULT_BACKGROUND_COLOR,
           uint16_t fg_color = BUTTON_DEFAULT_FOREGROUND_COLOR,
           uint16_t tx_color = BUTTON_DEFAULT_TEXT_COLOR);

    void registerTouchEventCallback(void (*onTouchCallback)(void));

    uint16_t getWidth(void);
    uint16_t getHeight(void);

    uint16_t getPosX(void);
    uint16_t getPosY(void);

    void setText(char * _label);
};

#endif // BUTTON_H
