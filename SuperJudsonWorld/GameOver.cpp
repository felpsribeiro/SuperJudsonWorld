#include "Engine.h"
#include "GameOver.h"
#include "SuperJudsonWorld.h"
#include "Home.h"

// ----------------------------------------------------------------------

void GameOver::Init()
{
    SuperJudsonWorld::lost = false;

    title = new Sprite("Resources/Tela Game Over.png");
    font = new Font("Resources/Agency30.png");
    font->Spacing("Resources/Agency30.dat");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN)) {
        SuperJudsonWorld::player->Reset();
        SuperJudsonWorld::NextLevel<Home>();
        SuperJudsonWorld::pontos = 0;
    }
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
    text.str("");
    text << "Pontuação";
    font->Draw(window->CenterX() - 15, window->CenterY() - 20, text.str());

    text.str("");
    text.width(4);
    text.fill('0');
    text << SuperJudsonWorld::pontos;
    font->Draw(window->CenterX(), window->CenterY() + 20, text.str());


    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
    delete title;
}

// ----------------------------------------------------------------------

