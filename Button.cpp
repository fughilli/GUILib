#include "Button.h"

Button::Button(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, char * _label, uint16_t _width, uint16_t _height)
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
        height = 2*BUTTON_MARGIN + textHeight;
        width = 2*BUTTON_MARGIN + textWidth;
    }
}

bool Button::checkBounds(uint16_t touchX, uint16_t touchY)
{
    if
    (
        (touchX >= posX) && (touchX <= (posX + width)) &&
        (touchY >= posY) && (touchY <= (posY + height))
    )
    {
        return true;
    }
    return false;
}

void Button::injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType)
{
    GUIElement::injectTouch(touchX, touchY, touchType);

    if(hasTouchEventCallback)
        onTouchCallback(touchType);
}

void Button::draw(bool clearBeforeDraw)
{
    if(clearBeforeDraw)
    {
        guiController->screen->setPenSolid();
        guiController->screen->dRectangle(posX, posY, width, height, BUTTON_BACKGROUND_COLOR);
        guiController->screen->setPenSolid(false);
    }

    guiController->screen->dRectangle(posX, posY, width, height, BUTTON_FOREGROUND_COLOR);
    guiController->screen->dRectangle(posX+BUTTON_MARGIN, posY+BUTTON_MARGIN, width-(BUTTON_MARGIN*2), height-(BUTTON_MARGIN*2), BUTTON_FOREGROUND_COLOR);
    guiController->screen->gText(posX+((width - textWidth)/2), posY+((height - textHeight)/2), label, BUTTON_TEXT_COLOR);

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
