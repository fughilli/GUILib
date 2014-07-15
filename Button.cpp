#include "Button.h"

Button::Button(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, char * _label,
               uint16_t _width, uint16_t _height,
               uint16_t bg_color,
               uint16_t fg_color,
               uint16_t tx_color)
{
    posX = _posX;
    posY = _posY;
    zDepth = _zDepth;

    label = _label;

    autoResize = ((_width == 0)&&(_height == 0));

    if(!autoResize)
    {
        width = _width;
        height = _height;
    }

    hasTouchEventCallback = false;
    invalid = true;
}

void Button::initialize(void)
{
    textWidth = strlen(label)*guiController->screen->fontSizeX();
    textHeight = guiController->screen->fontSizeY();

    if(autoResize)
    {
        height = 2*BUTTON_DEFAULT_MARGIN + textHeight;
        width = 2*BUTTON_DEFAULT_MARGIN + textWidth;
    }
}

bool Button::checkBounds(int16_t touchX, int16_t touchY)
{
    return true;
}

void Button::injectTouch(int16_t touchX, int16_t touchY, TouchType_e touchType) :
    injectTouch(touchX, touchY, touchType)
{

    if(hasTouchEventCallback)
        onTouchCallback();
}

void Button::draw(bool clearBeforeDraw)
{
    if(clearBeforeDraw)
    {
        guiController->screen->setPenSolid();
        guiController->screen->dRectangle(posX, posY, width, height, BUTTON_DEFAULT_BACKGROUND_COLOR);
        guiController->screen->setPenSolid(false);
    }

    guiController->screen->dRectangle(posX, posY, width, height, BUTTON_DEFAULT_FOREGROUND_COLOR);

    guiController->screen->dRectangle(posX+BUTTON_DEFAULT_MARGIN,
                                      posY+BUTTON_DEFAULT_MARGIN,
                                      width-(BUTTON_DEFAULT_MARGIN*2),
                                      height-(BUTTON_DEFAULT_MARGIN*2),
                                      BUTTON_DEFAULT_FOREGROUND_COLOR);

    guiController->screen->gText(posX+((width - textWidth)/2),
                                 posY+((height - textHeight)/2), label, BUTTON_DEFAULT_TEXT_COLOR);

    invalid = false;
}

void Button::registerTouchEventCallback(void (*_onTouchCallback)(void))
{
    hasTouchEventCallback = true;
    onTouchCallback = _onTouchCallback;
}

void Button::setText(char * _label)
{
    invalid = true;

    label = _label;

    initialize();
}

uint16_t Button::getWidth(void)
{
    return width;
}

uint16_t Button::getHeight(void)
{
    return height;
}

uint16_t Button::getPosX(void)
{
    return posX;
}

uint16_t Button::getPosY(void)
{
    return posY;
}
