#include "SuperJudsonWorld.h"
#include "Home.h"
#include "Level2.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

#include "Enemy2.h"
#include "Coin.h"

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Level2::scene = nullptr;

// ------------------------------------------------------------------------------

void Level2::Init()
{
    SuperJudsonWorld::hud->ResetTime();
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background("Resources/Level2.png");
    scene->Add(backg, STATIC);


    // adiciona jogador na cena
    scene->Add(SuperJudsonWorld::player, MOVING);

    Platform* plat;
    Enemy2* en;
    float posX, posY;
    uint  platType;
    Color white{ 1,1,1,1 };
    int cont = 0;
    Coin* coin;

    ifstream fin;
    fin.open("Level2.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // l� linha com informa��es da plataforma
            fin >> posY; fin >> platType;

            plat = new Platform(posX, posY, platType, white);
            scene->Add(plat, STATIC);

            if (cont == 2 || cont == 3) {
                float x = plat->X() - (plat->Width() * 0.25f) / 2;
                float y = plat->Y() - (plat->Height() * 0.25f) / 2;

                en = new Enemy2(x, y);
                scene->Add(en, MOVING);

                coin = new Coin(plat->X(), plat->Y() - 50);
                scene->Add(coin, STATIC);
            }
            cont++;
        }
        else
        {
            // ignora coment�rios
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;

        coin = new Coin(500, 432);
        scene->Add(coin, STATIC);
    }
    fin.close();

    // ----------------------

    // inicia com m�sica
    //SuperJudsonWorld::audio->Frequency(MUSIC, 0.94f);
    //SuperJudsonWorld::audio->Frequency(TRANSITION, 1.0f);
    //SuperJudsonWorld::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level2::Update()
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
    else
    {
        scene->Update();
        scene->CollisionDetection();

        if (SuperJudsonWorld::hud->Time() == 0) {
            SuperJudsonWorld::audio->Stop(MUSIC);
            SuperJudsonWorld::player->Reset();
            SuperJudsonWorld::NextLevel<GameOver>();
        }
    }
}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (SuperJudsonWorld::viewBBox)
        scene->DrawBBox();

    SuperJudsonWorld::hud->Draw();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    scene->Remove(SuperJudsonWorld::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
