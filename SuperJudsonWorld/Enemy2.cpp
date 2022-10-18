#include "Enemy2.h"
#include "SuperJudsonWorld.h"


// ---------------------------------------------------------------------------------

Enemy2::Enemy2(float x_init, float y_init)
{
    type = ENEMY;

    tileset = new TileSet("Resources/enemy_2.png", 44, 62, 2, 4);

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
    if (obj->Type() == GRAY) {
        Platform* plat = (Platform*) obj;
        Rect* p = (Rect*) plat->BBox();

        Rect* e = (Rect*) BBox();
        
        if(e->Left() < p->Right() && e->Right() > p->Left() && e->Top() < p->Top())
            // mant�m personagem em cima da plataforma
            MoveTo(X(), plat->Y() - (plat->Height() * 0.25f) / 2);
    }
}

// ---------------------------------------------------------------------------------

void Enemy2::Update()
{
    if (X() + 23 > window->Width()) {
        MoveTo(window->Width() - 23, Y());
        direction = LEFT;
    }
    else if (X() - 23 < 0) {
        MoveTo(23, Y());
        direction = RIGHT;
    }

    if (Y() + 31 > 472.0f) {
        MoveTo(X(), 472.0f - 31);
    }

    if (direction == RIGHT) {
        Translate(100 * gameTime, 200 * gameTime);
        anim->Select(RIGHT);
    }
    else {
        Translate(-100 * gameTime, 200 * gameTime);
        anim->Select(LEFT);
    }

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------