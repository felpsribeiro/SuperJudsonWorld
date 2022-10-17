#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType)
    {
        case RED:  platform = new Sprite("Resources/platform_1.png"); type = RED; break;
        case GRAY: platform = new Sprite("Resources/platform_2.png"); type = GRAY; break;
    }
    
    BBox(new Rect(-platform->Width()/2.0f, 
                  -platform->Height()/2.0f, 
                   platform->Width()/2.0f, 
                   platform->Height()/2.0f));

    MoveTo(posX, posY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    // move plataforma apenas no eixo x
    //Translate(-200.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------
