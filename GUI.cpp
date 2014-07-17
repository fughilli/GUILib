#include "GUI.h"
#include "../LCDSuite/LCD_screen.h"
#include "../LCDSuite/LCD_screen_font.h"

// Initialize GUIController, clearing all element slots
// Clear screen
GUIController::GUIController(LCD_screen_font& _screen, uint16_t bg_color)
{
    guiElementUsedCount = 0;

    backgroundColor = bg_color;

    screen = &_screen;

    for(int i = 0; i < MAX_GUI_ELEMENTS; i++)
    {
        elements[i].used = false;
    }
}

void GUIController::begin(void)
{
    screen->clear(backgroundColor);
    screen->setOrientation(1);
}


void GUIController::draw(void)
{
    uint16_t guicount = 0;

    for(int i = 0; i < MAX_GUI_ELEMENTS; i++)
    {
        if(elements[i].used && elements[i].ptr->invalid)
        {
            elements[i].ptr->draw(CLEAR_BEFORE_DRAW);
            guicount++;
        }
        if(guicount == guiElementUsedCount)
        {
            break;
        }
    }
}

// Check to see whether or not the new element fits in the GUI
// Register the new element in a free slot
uint8_t GUIController::registerGUIElement(GUIElement& newElement)
{
    if
    (
        (newElement.posX + newElement.width > screen->screenSizeX()) ||
        (newElement.posY + newElement.height > screen->screenSizeY())
    )
    {
        return GER_FAIL_OUT_OF_BOUNDS;
    }

    for(int i = 0; i < MAX_GUI_ELEMENTS; i++)
    {
        if(!elements[i].used)
        {
            elements[i].ptr = &newElement;
            elements[i].used = true;
            elements[i].ptr->guiController = this;
            elements[i].ptr->initialize();
            guiElementUsedCount++;
            return GER_OK;
        }
    }

    return GER_FAIL_NO_SPACE;
}

bool GUIController::injectTouch(int16_t touchX, int16_t touchY, TouchType_e touchType)
{
    GUIDebugPrint("injectTouch: ");
    GUIDebugPrint(touchX);
    GUIDebugPrint("\t");
    GUIDebugPrintln(touchY);

    uint8_t maxZDepth = 0;
    int maxZDepthIndex = -1;

    for(int i = 0; i < MAX_GUI_ELEMENTS; i++)
    {
        if(
            // Is the element used? (Is there a GUIElement at this index?)
            elements[i].used &&
            // Does its AABB contain the touch point?
            ((GUIElement*)(elements[i].ptr))->checkBounds(touchX - elements[i].ptr->getPosX(),
                    touchY - elements[i].ptr->getPosY()) &&
            // Do its true bounds contain the touch point?
            elements[i].ptr->checkBounds(touchX - elements[i].ptr->getPosX(),
                                         touchY - elements[i].ptr->getPosY()) &&
            // Is it higher in z-depth than any elements whose bounding boxes also matched?
            (elements[i].ptr->zDepth >= maxZDepth)
        )
        {
            maxZDepth = elements[i].ptr->zDepth;
            maxZDepthIndex = i;
        }
    }

    if(maxZDepthIndex == -1)
    {
        return false;
    }
    else
    {
        GUIDebugPrintln("touching something...");
        elements[maxZDepthIndex].ptr->injectTouch(touchX - elements[maxZDepthIndex].ptr->getPosX(),
                touchY - elements[maxZDepthIndex].ptr->getPosY(), touchType);
        return true;
    }
}

void GUIElement::injectTouch(int16_t touchX, int16_t touchY, TouchType_e touchType)
{
    switch(touchType)
    {
    case TOUCH_DOWN:
        pressed = true;
        break;
    case TOUCH_UP:
        pressed = false;
        break;
    }
}

bool GUIElement::setPos(uint16_t x, uint16_t y)
{
    if(((width + x) <= guiController->screen->screenSizeX()) &&
            ((height + y) <= guiController->screen->screenSizeY()) &&
            (x >= 0) && (y >= 0))
    {
        posX = x;
        posY = y;
    }
}

bool GUIElement::checkBounds(int16_t touchX, int16_t touchY)
{
    if
    (
        (touchX >= 0) && (touchX <= width) &&
        (touchY >= 0) && (touchY <= height)
    )
    {
        return true;
    }
    return false;
}
