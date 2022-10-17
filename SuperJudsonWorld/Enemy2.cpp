#include "Enemy2.h"
#include "SuperJudsonWorld.h"


// ---------------------------------------------------------------------------------

Enemy2::Enemy2(float x_init, float y_init, Platform* plat)
{
    tileset = new TileSet("Resources/enemy_2.png", 44, 62, 2, 4);
    platform = plat;

    uint left[2] = { 0, 1 };
    uint right[2] = { 2, 3 };

    anim = new Animation(tileset, 0.120f, true);

    anim->Add(LEFT, left, 2);
    anim->Add(RIGHT, right, 2);


    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    // posi��o inicial
    MoveTo(x_init, y_init, Layer::FRONT);

    direction = RIGHT;
}

// ---------------------------------------------------------------------------------

Enemy2::~Enemy2()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Enemy2::OnCollision(Object* obj)
{

}

// ---------------------------------------------------------------------------------

void Enemy2::Update()
{
    float width = platform->Width() * 0.25f;
    float plat_x = platform->X();

    if (X() + 23 > plat_x + width / 2) {
        MoveTo(plat_x + width / 2 - 23, Y());
        direction = LEFT;
    }
    else if (X() - 23 < plat_x - width / 2) {
        MoveTo(plat_x - width / 2 + 23, Y());
        direction = RIGHT;
    }

    if (direction == RIGHT) {
        Translate(70 * gameTime, 0);
        anim->Select(RIGHT);
    }
    else {
        Translate(-70 * gameTime, 0);
        anim->Select(LEFT);
    }

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------