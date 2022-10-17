#include "Enemy.h"
#include "SuperJudsonWorld.h"

// ---------------------------------------------------------------------------------

Enemy::Enemy(float x_init, float y_init)
{
    tileset = new TileSet("Resources/enemy_1.png", 31.59, 30.49, 3, 6); 

    uint left[3] = { 0,1,2 };
    uint right[3] = { 3,4,5 };

    anim = new Animation(tileset, 0.120f, true);

    anim->Add(LEFT, left, 3);
    anim->Add(RIGHT, right, 3);


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

Enemy::~Enemy()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Enemy::OnCollision(Object* obj)
{
 
}

// ---------------------------------------------------------------------------------

void Enemy::Update()
{
    if (X() + 23 > window->Width()) {
        MoveTo(window->Width() - 23, Y());
        direction = LEFT;
    }
    else if (X() - 23 < 0) {
        MoveTo(23, Y());
        direction = RIGHT;
    }

    if (direction == RIGHT) {
        Translate(200 * gameTime, 0);
        anim->Select(RIGHT);
    }
    else {
        Translate(-200 * gameTime, 0);
        anim->Select(LEFT);
    }

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------