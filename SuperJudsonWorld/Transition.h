#ifndef _TRANSITION_H_
#define _TRANSITION_H_

// ------------------------------------------------------------------------------
// Inclusões

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
    TileSet* tileset = nullptr;    // tileset da animação
    Animation* anim = nullptr;     // animação do planeta
    Font* fonte;
    stringstream text;

public:
    void Init();                    // inicia nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza nível
};

// -----------------------------------------------------------------------------

#endif
