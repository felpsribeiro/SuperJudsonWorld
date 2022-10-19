#ifndef _PLAYER_H_
#define _PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites

// ------------------------------------------------------------------------------

enum State { LEFT_W, LEFT_J, LEFT_S, RIGHT_W, RIGHT_J, RIGHT_S };
enum Direction { UP, DOWN };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    Animation * anim;                   // anima��o do personagem
    State       state = RIGHT_S;
    float       maxSpeed = 200.0f;
    float       speed = maxSpeed;
    const float gravit = 0.1f;
    uint        direction = DOWN;

public:
    uint level;

    Player();                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo

    void OnCollision(Object * obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline float Player::Bottom()
{ return y + tileset->TileHeight()/2; }

inline float Player::Top()
{ return y - tileset->TileHeight()/2; }

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif