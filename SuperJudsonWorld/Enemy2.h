#ifndef _ENEMY2_H_
#define _ENEMY2_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Platform.h"

// ------------------------------------------------------------------------------
         
enum { LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Enemy2 : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // anima��o do personagem
    uint direction;

public:
    Enemy2(float x_init, float y_init);  // construtor
    ~Enemy2();                          // destrutor

    int Level();                        // �ltimo n�vel finalizado
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo

    void OnCollision(Object* obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline float Enemy2::Bottom()
{
    return y + tileset->Height() / 2;
}

inline float Enemy2::Top()
{
    return y - tileset->Height() / 2;
}

inline void Enemy2::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif