#include "Player.h"
#include "SuperJudsonWorld.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/Player.png", 50, 80, 3, 6);
    anim = new Animation(tileset, 0.120f, false);

    // sequ�ncias de anima��o do player
    uint left[3]  = {0,1,2};
    uint right[3] = {3,4,5};

    anim->Add(LEFT, left, 3);
    anim->Add(RIGHT, right, 3);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    // posi��o inicial
    MoveTo(49.0f, 432.0f, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(49.0f, 392.0f, Layer::FRONT);
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    //if (obj->Type() == FINISH)
    //{
    //    // chegou ao final do n�vel
    //    level++;
    //}
    //else
    //{
    //    // mant�m personagem em cima da plataforma
    //    if (gravity == NORMAL)
    //        MoveTo(window->CenterX(), obj->Y() - 32);
    //    else
    //        MoveTo(window->CenterX(), obj->Y() + 32);
    //}

    //// ----------------------------------------------------------
    //// Processa teclas pressionadas
    //// ----------------------------------------------------------
    //// jogador s� pode alterar a gravidade enquanto estiver
    //// em cima de uma plataforma, n�o � poss�vel a mudan�a no ar
    //// ----------------------------------------------------------

    //if (window->KeyPress(VK_SPACE))
    //{
    //    gravity = !gravity;

    //    // toca efeito sonoro
    //    SuperJudsonWorld::audio->Play(TRANSITION);

    //    // tira player da plataforma para evitar 
    //    // detec��o de colis�o no quadro seguinte
    //    if (gravity == NORMAL)
    //        Translate(0, 12);
    //    else
    //        Translate(0 , -12);
    //}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    //// a��o da gravidade sobre o personagem
    //if (gravity == NORMAL)    
    //    Translate(0, 300 * gameTime);
    //else
    //    Translate(0, -300 * gameTime);

    //// atualiza anima��o
    anim->Select(RIGHT);
    //anim->NextFrame();
}

// ---------------------------------------------------------------------------------