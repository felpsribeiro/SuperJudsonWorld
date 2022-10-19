#include "Engine.h"
#include "SuperJudsonWorld.h"
#include "Transition.h"
#include "Home.h"
#include "Level2.h"

// ------------------------------------------------------------------------------

void Transition::Init()
{
    backg = new Sprite("Resources/transicao.png");

    fonte = new Font("Resources/Agency30.png");
    fonte->Spacing("Resources/Agency30.dat");
    

    if (SuperJudsonWorld::n_level == 1)
    {
        tileset = new TileSet("Resources/planet_1.png", 100, 100, 15, 15);
    }
    else if (SuperJudsonWorld::n_level == 2)
    {
        tileset = new TileSet("Resources/planet_2.png", 100, 100, 15, 15);
    }

    anim = new Animation(tileset, 0.120f, true);

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
        else if (SuperJudsonWorld::n_level == 2)
            SuperJudsonWorld::NextLevel<Home>();
    }
    else
        anim->NextFrame();
}

// ------------------------------------------------------------------------------

void Transition::Draw()
{
    text << "Pontuação: " << SuperJudsonWorld::pontos;
    fonte->Draw(window->CenterX() - 40.0f, window->CenterY() - 50.0f, text.str());
    text.str("");
    text << "Tempo: " << 100 - SuperJudsonWorld::hud->Time() << '\n';
    fonte->Draw(window->CenterX() - 20.0f, window->CenterY() - 25.0f, text.str());
    text.str("");

    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(window->CenterX(), window->CenterY() + 55.0f);
}

// ------------------------------------------------------------------------------

void Transition::Finalize()
{
    delete backg;
    delete anim;
    delete tileset;
    delete fonte;
}

// ------------------------------------------------------------------------------