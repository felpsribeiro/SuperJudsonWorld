#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite * backg = nullptr;       // tela de fim

public:
    void Init();                    // inicializa��o do n�vel
    void Update();                  // l�gica da tela de fim
    void Draw() 
    { 
        backg->Draw(window->CenterX(), window->CenterY());  
    };                              // desenho da tela
    void Finalize() 
    {
        delete backg;
    };                              // finaliza��o do n�vel
};

// ------------------------------------------------------------------------------

#endif