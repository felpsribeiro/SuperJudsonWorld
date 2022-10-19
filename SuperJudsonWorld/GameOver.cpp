#include "Engine.h"
#include "GameOver.h"
#include "SuperJudsonWorld.h"
#include "Home.h"

// ----------------------------------------------------------------------

void GameOver::Init()
{
    SuperJudsonWorld::lost = false;
    backg = new Sprite("Resources/GameOver.png");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_RETURN))
        SuperJudsonWorld::NextLevel<Home>();
}
