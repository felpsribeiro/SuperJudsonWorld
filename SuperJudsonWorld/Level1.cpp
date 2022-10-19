#include "SuperJudsonWorld.h"
#include "Home.h"
#include "Level1.h"
#include "Transition.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

#include "Enemy.h"
#include "Level2.h"
#include "Coin.h"

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene * Level1::scene = nullptr;
uint Level1::collectedCoins = 0;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    SuperJudsonWorld::n_level = 1;
    SuperJudsonWorld::pontos = 0;
    SuperJudsonWorld::hud->ResetTime();

    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Sprite("Resources/Level1.png");

    SuperJudsonWorld::audio->Play(MUSIC1, true);

    // adiciona jogador na cena
    scene->Add(SuperJudsonWorld::player, MOVING);
    
    collectedCoins = 0;

    Platform* plat;
    Enemy* en;
    float posX, posY;
    uint  platType;
    Color white{ 1,1,1,1 };
    int cont = 0;
    Coin* coin;

    ifstream fin;
    fin.open("Level1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // l� linha com informa��es da plataforma
            fin >> posY; fin >> platType;

            plat = new Platform(posX, posY, platType, white);
            scene->Add(plat, STATIC);

            if (cont == 0 || cont == 2 || cont == 3) {
                float x = plat->X() - (plat->Width() * 0.25f) / 2;
                float y = plat->Y() - 32;

                en = new Enemy(x, y, plat);
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

        
    }
    fin.close();
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    scene->Update();
    scene->CollisionDetection();

    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (window->KeyPress('N') || collectedCoins == 3) {
        SuperJudsonWorld::audio->Stop(MUSIC1);
        SuperJudsonWorld::hud->Stop();
        SuperJudsonWorld::NextLevel<Transition>();
    }

    if (SuperJudsonWorld::hud->Time() == 0 || SuperJudsonWorld::lost) {          
        SuperJudsonWorld::audio->Stop(MUSIC1);
        SuperJudsonWorld::NextLevel<GameOver>();
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY());
    scene->Draw();

    if (SuperJudsonWorld::viewBBox)
        scene->DrawBBox();

    SuperJudsonWorld::hud->Draw();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    scene->Remove(SuperJudsonWorld::player, MOVING);
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------
