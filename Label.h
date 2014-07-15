#ifndef LABEL_H
#define LABEL_H

#include "Energia.h"
#include "GUI.h"

#define LABEL_DEFAULT_BACKGROUND_COLOR GUI_DEFAULT_BACKGROUND_COLOR
#define LABEL_DEFAULT_TEXT_COLOR       GUI_DEFAULT_FOREGROUND_COLOR

#define LABEL_DEFAULT_TEXT_SIZE               SMALL

typedef enum
{
    SMALL,
    MEDIUM,
    LARGE,
    XLARGE
}
TextSize_e;

class Label : public GUIElement
{
protected:
    TextSize_e textSize;
    uint16_t textColor;
    bool checkBounds(int16_t touchX, int16_t touchY);

    void injectTouch(int16_t touchX, int16_t touchY, TouchType_e touchType);

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

    void setTextSize(TextSize_e _textSize);

    void setText(char * _label);
};

#endif // LABEL_H
