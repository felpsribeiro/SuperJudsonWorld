#include "SuperJudsonWorld.h"
#include "Home.h"
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

Scene* Level2::scene = nullptr;

// ------------------------------------------------------------------------------

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    Color dark{ 0.4f, 0.4f, 0.4f, 1.0f };
    backg = new Background(dark);
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(SuperJudsonWorld::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    float posX, posY;
    uint  platType;

    ifstream fin;
    fin.open("Level2.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // l� linha com informa��es da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType, dark);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora coment�rios
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    // ----------------------

    SuperJudsonWorld::audio->Frequency(MUSIC, 1.00f);
    SuperJudsonWorld::audio->Frequency(TRANSITION, 0.85f);
}

// ------------------------------------------------------------------------------

void Level2::Update()
{
    if (window->KeyPress(VK_ESCAPE) || SuperJudsonWorld::player->Level() == 2 || window->KeyPress('N'))
    {
        SuperJudsonWorld::audio->Stop(MUSIC);
        SuperJudsonWorld::NextLevel<Home>();
        SuperJudsonWorld::player->Reset();
    }
    else if (SuperJudsonWorld::player->Bottom() < 0 || SuperJudsonWorld::player->Top() > window->Height())
    {
        SuperJudsonWorld::audio->Stop(MUSIC);
        SuperJudsonWorld::NextLevel<GameOver>();
        SuperJudsonWorld::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (SuperJudsonWorld::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    scene->Remove(SuperJudsonWorld::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
