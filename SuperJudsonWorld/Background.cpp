#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background(string path)
{
    // cria sprites do plano de fundo
    backg = new Sprite(path);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete backg;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f);
}

// -------------------------------------------------------------------------------
