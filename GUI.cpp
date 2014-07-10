#include "GUI.h"
#include "../LCDSuite/LCD_screen.h"
#include "../LCDSuite/LCD_screen_font.h"

// Initialize GUIController, clearing all element slots
// Clear screen
GUIController::GUIController(LCD_screen_font& _screen)
{
    guiElementUsedCount = 0;

    screen = &_screen;

    for(int i = 0; i < MAX_GUI_ELEMENTS; i++)
    {
        elements[i].used = false;
    }
}

void GUIController::begin(void)
{
    screen->clear(BACKGROUND_COLOR);
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

bool GUIController::injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType)
{
    uint8_t maxZDepth = 0;
    int maxZDepthIndex = -1;

    for(int i = 0; i < MAX_GUI_ELEMENTS; i++)
    {
        if(elements[i].used && elements[i].ptr->checkBounds(touchX, touchY) && (elements[i].ptr->zDepth > maxZDepth))
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
        elements[maxZDepthIndex].ptr->injectTouch(touchX, touchY, touchType);
        return true;
    }
}

void GUIElement::injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType)
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
