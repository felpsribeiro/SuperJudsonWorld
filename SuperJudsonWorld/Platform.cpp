#include "Platform.h"
#include "SuperJudsonWorld.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType) 
    {
        case PLAT_RED:  
            platform = new Sprite("Resources/platform_1.png"); type = PLAT_RED; 

            BBox(new Rect(-(platform->Width() * 0.25f) / 2.0f,
                -(platform->Height() * 0.25f) / 2.0f,
                (platform->Width() * 0.25f) / 2.0f,
                (platform->Height() * 0.25f) / 2.0f));

            break;

        case PLAT_GRAY: 
            platform = new Sprite("Resources/platform_2.png"); type = PLAT_GRAY; 
            //bbox menor pra simplificar a colisão
            BBox(new Rect(-(platform->Width() * 0.25f) / 2.0f,
                -(platform->Height() * 0.25f) / 4.0f,
                (platform->Width() * 0.25f) / 2.0f,
                (platform->Height() * 0.25f) / 4.0f));

            break;
    }

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
