#ifndef _TRANSITION_H_
#define _TRANSITION_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class Transition : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo
    TileSet* tileset = nullptr;    // tileset da anima��o
    Animation* anim = nullptr;     // anima��o do planeta
    Font* fonte;
    stringstream text;

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

// -----------------------------------------------------------------------------

#endif
