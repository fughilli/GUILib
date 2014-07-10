#include "Slider.h"

Slider::Slider(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, SliderOrientation_t _orientation, uint16_t _length)
{
    posX = _posX;
    posY = _posY;
    zDepth = _zDepth;

    orientation = _orientation;
    length = _length;

    value = 0;

    hasTouchEventCallback = false;
    invalid = true;
}

void Slider::initialize(void)
{
    if(orientation == VERTICAL)
    {
        width = SLIDER_HANDLE_HEIGHT;
        height = length + SLIDER_HANDLE_WIDTH;
    }
    else
    {
        height = SLIDER_HANDLE_HEIGHT;
        width = length + SLIDER_HANDLE_WIDTH;
    }
}

bool Slider::checkBounds(uint16_t touchX, uint16_t touchY)
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

void Slider::injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType)
{
    GUIElement::injectTouch(touchX, touchY, touchType);

    invalid = true;

    if(orientation == VERTICAL)
    {
        value = constrain((int16_t)length - (touchY - posY) + SLIDER_HANDLE_WIDTH/2, 0, length);
    }
    else
    {
        value = constrain((int16_t)touchX - posX - SLIDER_HANDLE_WIDTH/2, 0, length);
    }

    if(hasTouchEventCallback)
        onTouchCallback();
}

void Slider::draw(bool clearBeforeDraw)
{
    if(clearBeforeDraw)
    {
        guiController->screen->setPenSolid();
        guiController->screen->dRectangle(posX, posY, width, height, SLIDER_BACKGROUND_COLOR);
        guiController->screen->setPenSolid(false);
    }

    if(orientation == VERTICAL)
    {
        guiController->screen->dRectangle(posX + (width-SLIDER_LINE_THICKNESS)/2, posY + (height-length)/2, SLIDER_LINE_THICKNESS, length, SLIDER_LINE_COLOR);
        guiController->screen->setPenSolid();
        guiController->screen->dRectangle(posX, posY + length - value, SLIDER_HANDLE_HEIGHT, SLIDER_HANDLE_WIDTH, SLIDER_HANDLE_COLOR);
        guiController->screen->setPenSolid(false);
    }
    else
    {
        guiController->screen->dRectangle(posX + (width-length)/2, posY + (height-SLIDER_LINE_THICKNESS)/2, length, SLIDER_LINE_THICKNESS, SLIDER_LINE_COLOR);
        guiController->screen->setPenSolid();
        guiController->screen->dRectangle(posX + value, posY, SLIDER_HANDLE_WIDTH, SLIDER_HANDLE_HEIGHT, SLIDER_HANDLE_COLOR);
        guiController->screen->setPenSolid(false);
    }

    invalid = false;
}

void Slider::registerTouchEventCallback(void (*_onTouchCallback)(void))
{
    hasTouchEventCallback = true;
    onTouchCallback = _onTouchCallback;
}

uint16_t Slider::getWidth(void)
{
    return width;
}

uint16_t Slider::getHeight(void)
{
    return height;
}

uint16_t Slider::getPosX(void)
{
    return posX;
}

uint16_t Slider::getPosY(void)
{
    return posY;
}

uint16_t Slider::getValue(void)
{
    return value;
}

void Slider::setValue(uint16_t _value)
{
    invalid = true;
    value = constrain(_value, 0, length);
}
