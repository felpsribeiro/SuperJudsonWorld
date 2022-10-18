#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Font.h"
#include <sstream>

using std::stringstream;

// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite * title = nullptr;       // tela de fim

    Font* font = nullptr;
    stringstream text;

public:
    void Init();                    // inicializa��o do n�vel
    void Update();                  // l�gica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finaliza��o do n�vel
};

// ------------------------------------------------------------------------------

#endif