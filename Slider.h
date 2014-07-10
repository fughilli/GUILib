#ifndef SLIDER_H
#define SLIDER_H

#include "Energia.h"
#include "GUI.h"

#define SLIDER_BACKGROUND_COLOR blackColour
#define SLIDER_LINE_COLOR       whiteColour
#define SLIDER_HANDLE_COLOR     blueColour
#define SLIDER_LINE_THICKNESS   4
#define SLIDER_HANDLE_WIDTH     12
#define SLIDER_HANDLE_HEIGHT    24

enum SliderOrientation_t
{
    VERTICAL,
    HORIZONTAL
};

class Slider : public GUIElement
{
protected:
    SliderOrientation_t orientation;
    uint16_t length;
    uint16_t value;

    bool checkBounds(uint16_t touchX, uint16_t touchY);

    void injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType);

    void draw(bool clearBeforeDraw);

    void initialize(void);

public:
    Slider(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, SliderOrientation_t orient = HORIZONTAL, uint16_t length = 100);

    void registerTouchEventCallback(void (*onTouchCallback)(void));

    uint16_t getWidth(void);
    uint16_t getHeight(void);

    uint16_t getPosX(void);
    uint16_t getPosY(void);

    uint16_t getValue(void);
    void setValue(uint16_t _value);

    uint16_t getPosition(void);
};

#endif // SLIDER_H
