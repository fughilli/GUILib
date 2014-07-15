#ifndef GUI_H
#define GUI_H

#include "Energia.h"
#include "../LCDSuite/LCD_screen.h"
#include "../LCDSuite/LCD_screen_font.h"

#define MAX_GUI_ELEMENTS 32
#define CLEAR_BEFORE_DRAW true

#define GER_OK                  0
#define GER_FAIL_OUT_OF_BOUNDS  1
#define GER_FAIL_NO_SPACE       2

#define GUI_DEFAULT_BACKGROUND_COLOR        whiteColour
#define GUI_DEFAULT_FOREGROUND_COLOR        blackColour
#define GUI_DEFAULT_ACCENT_COLOR            redColour

//struct TouchEvent_t
//{
//    int16_t x;
//    int16_t y;
//};

// Type of touch being injected
enum TouchType_e
{
    TOUCH_DOWN,
    TOUCHING,
    TOUCH_UP
};

class GUIElement;
class GUIController;

class GUIController
{
protected:
    // Number of GUIElement managed by this controller
    uint16_t guiElementUsedCount;

    // Internal GUIElement management data type
    struct GUIElement_t
    {
        GUIElement * ptr;
        bool used;
    } elements[MAX_GUI_ELEMENTS];

    uint16_t backgroundColor;

public:

    LCD_screen_font * screen;

    GUIController(LCD_screen_font& _screen, uint16_t bg_color = GUI_DEFAULT_BACKGROUND_COLOR);

    void begin(void);

    void draw(void);

    bool injectTouch(int16_t touchX, int16_t touchY, TouchType_e touchType);

    uint8_t registerGUIElement(GUIElement& newElement);
};

class GUIElement
{
protected:
    bool pressed;
    bool invalid;
    bool hasTouchEventCallback;
    void (*onTouchCallback)(void);

    uint16_t width, height, posX, posY, zDepth;

    GUIController * guiController;

    virtual bool checkBounds(int16_t touchX, int16_t touchY);

    virtual void injectTouch(int16_t touchX, int16_t touchY, TouchType_e touchType);

    virtual void draw(bool clearBeforeDraw);

    virtual void initialize(void);

public:

    virtual void registerTouchEventCallback(void (*_onTouchCallback)(void));

    virtual uint16_t getWidth(void);
    virtual uint16_t getHeight(void);

    virtual uint16_t getPosX(void);
    virtual uint16_t getPosY(void);

    virtual bool setPos(uint16_t x, uint16_t y);

    friend class GUIController;
};

#endif // GUI_H
