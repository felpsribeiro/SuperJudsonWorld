#ifndef _LEVEL1_H_
#define _LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Sprite* backg = nullptr;   // pano de fundo animado

public:
    static Scene* scene;           // cena do n�vel

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel
};

// -----------------------------------------------------------------------------

#endif