#include "Player.h"
#include "SuperJudsonWorld.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/SuperJudsonWorld.png", 32, 48, 5, 10);
    anim = new Animation(tileset, 0.120f, true);

    // sequ�ncias de anima��o do player
    uint invert[4] = {6,7,8,9};
    uint normal[4] = {1,2,3,4};

    anim->Add(INVERTED, invert, 4);
    anim->Add(NORMAL, normal, 4);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));
    
    // inicializa estado do player
    gravity = NORMAL;  
    level = 0;

    // posi��o inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
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
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    gravity = NORMAL;
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == FINISH)
    {
        // chegou ao final do n�vel
        level++;
    }
    else
    {
        // mant�m personagem em cima da plataforma
        if (gravity == NORMAL)
            MoveTo(window->CenterX(), obj->Y() - 32);
        else
            MoveTo(window->CenterX(), obj->Y() + 32);
    }

    // ----------------------------------------------------------
    // Processa teclas pressionadas
    // ----------------------------------------------------------
    // jogador s� pode alterar a gravidade enquanto estiver
    // em cima de uma plataforma, n�o � poss�vel a mudan�a no ar
    // ----------------------------------------------------------

    if (window->KeyPress(VK_SPACE))
    {
        gravity = !gravity;

        // toca efeito sonoro
        SuperJudsonWorld::audio->Play(TRANSITION);

        // tira player da plataforma para evitar 
        // detec��o de colis�o no quadro seguinte
        if (gravity == NORMAL)
            Translate(0, 12);
        else
            Translate(0 , -12);
    }
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // a��o da gravidade sobre o personagem
    if (gravity == NORMAL)    
        Translate(0, 300 * gameTime);
    else
        Translate(0, -300 * gameTime);

    // atualiza anima��o
    anim->Select(gravity);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------