#include "Engine.h"
#include "SuperJudsonWorld.h"
#include "Home.h"
#include "GameOver.h"

// ------------------------------------------------------------------------------

// inicializa membros est�ticos da classe
Game*   SuperJudsonWorld::level = nullptr;
Player* SuperJudsonWorld::player = nullptr;
Audio*  SuperJudsonWorld::audio = nullptr;
bool    SuperJudsonWorld::viewBBox = false;
float   SuperJudsonWorld::pontos = 0.0f;
Hud*    SuperJudsonWorld::hud = nullptr;
int SuperJudsonWorld::n_level = 0;
bool SuperJudsonWorld::lost = false;

// ------------------------------------------------------------------------------

void SuperJudsonWorld::Init() 
{
    // cria sistema de �udio
    audio = new Audio();
    audio->Add(HOME, "Resources/Home.wav");
    audio->Add(MUSIC1, "Resources/Fase1.wav");
    audio->Add(MUSIC2, "Resources/Fase2.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");

    // bounding box n�o vis�vel
    viewBBox = false;

    hud = new Hud();

    // cria jogador
    player = new Player();

    // inicializa n�vel de abertura do jogo
    
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void SuperJudsonWorld::Update()
{
    // habilita/desabilita visualiza��o da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza n�vel
    level->Update();
    hud->Update();
} 

// ------------------------------------------------------------------------------

void SuperJudsonWorld::Draw()
{
    // desenha n�vel
    level->Draw();
} 

// ------------------------------------------------------------------------------

void SuperJudsonWorld::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WS_POPUP);
    engine->window->Size(1000, 500);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Super Judson World");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new SuperJudsonWorld());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

