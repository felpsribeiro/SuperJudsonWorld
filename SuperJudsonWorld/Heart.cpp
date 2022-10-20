#include "Heart.h"
#include "SuperJudsonWorld.h"

// ---------------------------------------------------------------------------------

Heart::Heart(float posX, float posY)
{
    heart = new Sprite("Resources/heart.png");

    MoveTo(posX, posY);

}

// ---------------------------------------------------------------------------------

Heart::~Heart()
{
    delete heart;
}

// -------------------------------------------------------------------------------

void Heart::Update()
{
    // move plataforma apenas no eixo x
    //Translate(-200.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------
