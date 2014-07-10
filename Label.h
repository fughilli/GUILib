#ifndef LABEL_H
#define LABEL_H

#include "Energia.h"
#include "GUI.h"

#define LABEL_BACKGROUND_COLOR blackColour
#define LABEL_TEXT_COLOR       whiteColour

class Label : public GUIElement
{
protected:
    uint16_t textColor;
    bool checkBounds(uint16_t touchX, uint16_t touchY);

    void injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType);

    void draw(bool clearBeforeDraw);

    void initialize(void);

public:
    char * label;
    Label(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, char * _label);

    void registerTouchEventCallback(void (*onTouchCallback)(void));

    void setColor(uint16_t _color);

    uint16_t getWidth(void);
    uint16_t getHeight(void);

    uint16_t getPosX(void);
    uint16_t getPosY(void);

    void setText(char * _label);
};

#endif // LABEL_H
