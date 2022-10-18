#include "Enemy.h"
#include "SuperJudsonWorld.h"


// ---------------------------------------------------------------------------------

Enemy::Enemy(float x_init, float y_init, Platform* plat)
{
    type = ENEMY;

    tileset = new TileSet("Resources/enemy_1.png", 34, 32, 3, 6); 
    platform = plat;

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
    
    type = ENEMY1;
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