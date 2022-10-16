#include "SuperJudsonWorld.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene * Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background("Resources/Level1.png");
    scene->Add(backg, STATIC);

    //bg_teste = new Sprite("Resources/bg_teste.jpg");

    // adiciona jogador na cena
    scene->Add(SuperJudsonWorld::player, MOVING);

    // ----------------------

    // inicia com m�sica
    //SuperJudsonWorld::audio->Frequency(MUSIC, 0.94f);
    //SuperJudsonWorld::audio->Frequency(TRANSITION, 1.0f);
    //SuperJudsonWorld::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    if (window->KeyPress(VK_ESCAPE))
    {
        SuperJudsonWorld::audio->Stop(MUSIC);
        SuperJudsonWorld::NextLevel<Home>();
        SuperJudsonWorld::player->Reset();
    }
    //else if (SuperJudsonWorld::player->Bottom() < 0 || SuperJudsonWorld::player->Top() > window->Height())
    //{
    //    SuperJudsonWorld::audio->Stop(MUSIC);
    //    SuperJudsonWorld::NextLevel<GameOver>();
    //    SuperJudsonWorld::player->Reset();
    //}
    //else if (SuperJudsonWorld::player->Level() == 1 || window->KeyPress('N'))
    //{
    //    //SuperJudsonWorld::NextLevel<Level2>();
    //}
    //else
    //{
    //    scene->Update();
    //    scene->CollisionDetection();
    //}    
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw();
    //bg_teste->Draw(window->CenterX(), window->CenterY());
    scene->Draw();

    if (SuperJudsonWorld::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    scene->Remove(SuperJudsonWorld::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
