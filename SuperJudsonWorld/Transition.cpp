#include "Engine.h"
#include "SuperJudsonWorld.h"
#include "Transition.h"
#include "Level2.h"

// ------------------------------------------------------------------------------

void Transition::Init()
{
    backg = new Sprite("Resources/planet_1.png");
    /*tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);*/
    SuperJudsonWorld::audio->Play(MENU, true);

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
        SuperJudsonWorld::n_level = 1;

        SuperJudsonWorld::audio->Stop(MENU);

        SuperJudsonWorld::NextLevel<Level2>();
    }
    else
    {
        // anim->NextFrame();
    }
}

// ------------------------------------------------------------------------------

void Transition::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    //anim->Draw(545, 275);
}

// ------------------------------------------------------------------------------

void Transition::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
}

// ------------------------------------------------------------------------------