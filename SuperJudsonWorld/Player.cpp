#include "Player.h"
#include "SuperJudsonWorld.h"
#include "Platform.h"
#include "Level1.h"
#include "Level2.h"

// ---------------------------------------------------------------------------------

Player::Player()
{

    tileset = new TileSet("Resources/Player.png", 50, 80, 3, 6);
    anim = new Animation(tileset, 0.540f, true);

    // sequ�ncias de anima��o do player
    uint walkerLeft[2]  = { 0, 1 };
    uint jumpLeft[2]    = { 0, 2 };
    uint stillLeft[1]   = { 0 };
    uint walkerRight[2] = { 3, 4 };
    uint jumpRight[2]   = { 3, 5 };
    uint stillRight[1]  = { 3 };
    
    anim->Add(LEFT_W, walkerLeft, 2);
    anim->Add(LEFT_J, jumpLeft, 2);
    anim->Add(LEFT_S, stillLeft, 1);
    anim->Add(RIGHT_W, walkerRight, 2);
    anim->Add(RIGHT_J, jumpRight, 2);
    anim->Add(RIGHT_S, stillRight, 1);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    // posição inicial
    MoveTo(49.0f, 432.0f, Layer::FRONT);
    anim->Select(RIGHT_S);
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
    MoveTo(49.0f, 432.0f, Layer::FRONT);
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    Rect* player = (Rect*)BBox();

    if (obj->Type() == COIN) {
        if (SuperJudsonWorld::n_level == 1) 
            Level1::scene->Delete(obj, STATIC);
        else if (SuperJudsonWorld::n_level == 2) 
            Level2::scene->Delete(obj, STATIC);
        SuperJudsonWorld::pontos += 250;
    }
    else if (obj->Type() == ENEMY1 || obj->Type() == ENEMY2) {
        //pulo - mata o inimigo
        //de frente - morre

        Rect* enemy = (Rect*)obj->BBox();

        if (enemy->Left() > player->Left() && enemy->Right() < player->Right() && 
            player->Bottom() > enemy->Top() && player->Bottom() < enemy->Bottom()) {
            if (SuperJudsonWorld::n_level == 1) Level1::scene->Delete(obj, MOVING);
            else if (SuperJudsonWorld::n_level == 2) Level1::scene->Delete(obj, MOVING);
            SuperJudsonWorld::pontos += 100;
        }
        else {
            SuperJudsonWorld::lost = true;
        }
    }
    else if (obj->Type() == PLAT_RED || obj->Type() == PLAT_GRAY) {
        Platform* plat = (Platform*)obj;
        Rect* platform = (Rect*)obj->BBox();

        if (player->Left() < platform->Right() && player->Right() > platform->Left() && player->Top() < platform->Top())
        {
            // mant�m personagem em cima da plataforma
            vector = STOPPED;
            MoveTo(x, platform->Top());
        }
    }
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    if (window->KeyPress(VK_SPACE) && vector == STOPPED)
    {
        vector = UP;
    }
    else if (window->KeyDown(VK_RIGHT) && window->KeyDown(VK_LEFT))
    {
        switch (state)
        {
        case LEFT_W:
        case LEFT_J:
        case LEFT_S:
        {
            state = LEFT_S;
            break;
        }
        case RIGHT_W:
        case RIGHT_J:
        case RIGHT_S:
        {
            state = RIGHT_S;
            break;
        }
        }
    }
    else if (window->KeyDown(VK_LEFT))
    {
         if (vector == UP)
             state = LEFT_S;
         else if (vector == DOWN)
             state = LEFT_J;
         else
             state = LEFT_W;

        Translate(-speed * gameTime, 0);
    } 
    else if (window->KeyDown(VK_RIGHT))
    {
         if (vector == UP)
             state = RIGHT_S;
         else if (vector == DOWN)
             state = RIGHT_J;
         else
             state = RIGHT_W;

        Translate(speed * gameTime, 0);
    }

    // mantém personagem dentro da tela
    if (x + tileset->TileWidth() / 2.0f > window->Width())
        MoveTo(window->Width() - tileset->TileWidth() / 2.0f, y);

    else if (x - tileset->TileWidth() / 2.0f < 0)
        MoveTo(tileset->TileWidth() / 2.0f, y);

    else if (y - tileset->Height() / 2.0f < 0)
        MoveTo(x, tileset->Height() / 2.0f);

    else if (y > 432.0f)
    {
        vector = STOPPED;
        MoveTo(x, 432.0f);
    }

    // controla a gravidade do personagem
    if (vector == UP)
    {
        speed -= gravit;
        Translate(0, -speed * gameTime);
            
        if (speed < 0.0f)
            vector = DOWN;
    }
    else if (vector == DOWN)
    {
        if (state == LEFT_W || state == LEFT_S)
            state = LEFT_J;
        else if (state == RIGHT_W || state == RIGHT_S)
            state = RIGHT_J;
        
        speed += gravit;
        Translate(0, speed * gameTime);
    }
    else if (vector == STOPPED)
    {
        speed = maxSpeed;

        if (y < 432.0f)
            vector == DOWN;
    }

    // atualiza animação
    anim->Select(state);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------