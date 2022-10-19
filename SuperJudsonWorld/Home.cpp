#include "Engine.h"
#include "SuperJudsonWorld.h"
#include "Home.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    backg = new Sprite("Resources/Home.png");
    player = new Player();

    SuperJudsonWorld::audio->Play(HOME, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();
    
    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {   
        SuperJudsonWorld::audio->Stop(HOME);
        SuperJudsonWorld::NextLevel<Level1>();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
    delete player;
}

// ------------------------------------------------------------------------------