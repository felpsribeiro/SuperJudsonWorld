#include "Engine.h"
#include "SuperJudsonWorld.h"
#include "Transition.h"
#include "Home.h"
#include "Level2.h"

// ------------------------------------------------------------------------------

void Transition::Init()
{
    backg = new Sprite("Resources/fundo.png");
    menu = new Sprite("Resources/pontuacao.png");

    if (SuperJudsonWorld::n_level == 1)
    {
        tileset = new TileSet("Resources/planet_1.png", 100, 100, 15, 15);
    }
    else if (SuperJudsonWorld::n_level == 2)
    {
        tileset = new TileSet("Resources/planet_2.png", 100, 100, 15, 15);
    }

    anim = new Animation(tileset, 0.180f, true);

    SuperJudsonWorld::audio->Play(TRANSITION, true);
    
}

// ------------------------------------------------------------------------------

void Transition::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        SuperJudsonWorld::audio->Stop(TRANSITION);

        if (SuperJudsonWorld::n_level == 1)
            SuperJudsonWorld::NextLevel<Level2>();
        if (SuperJudsonWorld::n_level == 2)
            SuperJudsonWorld::NextLevel<Home>();
    }
    else
        anim->NextFrame();
}

// ------------------------------------------------------------------------------

void Transition::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    menu->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(window->CenterX(), window->CenterY() + 55.0f);
}

// ------------------------------------------------------------------------------

void Transition::Finalize()
{
    delete backg;
    delete menu;
    delete anim;
    delete tileset;
}

// ------------------------------------------------------------------------------