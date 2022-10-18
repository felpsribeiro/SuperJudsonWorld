#include "Coin.h"
#include "SuperJudsonWorld.h"


// ---------------------------------------------------------------------------------

Coin::Coin(float x_init, float y_init)
{
    tileset = new TileSet("Resources/cpp.png", 32, 32, 2, 2);

    anim = new Animation(tileset, 0.120f, true);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    // posi��o inicial
    MoveTo(x_init, y_init, Layer::FRONT);

    type = COIN;
}

// ---------------------------------------------------------------------------------

Coin::~Coin()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Coin::OnCollision(Object* obj)
{

}

// ---------------------------------------------------------------------------------

void Coin::Update()
{
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------