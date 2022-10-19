#include "SuperJudsonWorld.h"
#include "Home.h"
#include "Level2.h"
#include "Transition.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

#include "Enemy2.h"
#include "Coin.h"

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Level2::scene = nullptr;
uint Level2::collectedCoins = 0;

// ------------------------------------------------------------------------------

void Level2::Init()
{
    SuperJudsonWorld::n_level = 2;
    SuperJudsonWorld::pontos = 0;
    SuperJudsonWorld::hud->ResetTime();

    scene = new Scene();

    // pano de fundo do jogo
    backg = new Sprite("Resources/Level2.png");

    // adiciona jogador na cena
    SuperJudsonWorld::player->Reset();
    scene->Add(SuperJudsonWorld::player, MOVING);

    SuperJudsonWorld::audio->Play(MUSIC2, true);

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

    SuperJudsonWorld::audio->Play(MUSIC2);
}

// ------------------------------------------------------------------------------

void Level2::Update()
{
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (window->KeyPress('N') || collectedCoins == 3) {
        collectedCoins = 0;
        SuperJudsonWorld::audio->Stop(MUSIC2);
        SuperJudsonWorld::pontos += 500;
        SuperJudsonWorld::NextLevel<Transition>();
    }

    else
    {
        scene->Update();
        scene->CollisionDetection();

        if (collectedCoins == 2)
        {
            SuperJudsonWorld::audio->Stop(MUSIC2);
            SuperJudsonWorld::NextLevel<Transition>();
        }

        if (SuperJudsonWorld::hud->Time() == 0 || SuperJudsonWorld::lost) {
            SuperJudsonWorld::lost = false;
            SuperJudsonWorld::audio->Stop(MUSIC2);
            SuperJudsonWorld::NextLevel<GameOver>();
        }
    }
}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY());
    scene->Draw();

    if (SuperJudsonWorld::viewBBox)
        scene->DrawBBox();

    SuperJudsonWorld::hud->Draw();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    scene->Remove(SuperJudsonWorld::player, MOVING);
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------
