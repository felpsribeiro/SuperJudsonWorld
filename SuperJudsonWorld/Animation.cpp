/**********************************************************************************
// Animation (C�digo Fonte)
// 
// Cria��o:     28 Set 2011
// Atualiza��o: 08 Set 2021
// Compilador:  Visual C++ 2019z
//
// Descri��o:   Classe para animar sequ�ncias em folha de sprites
//
**********************************************************************************/

#include "Engine.h"
#include "Animation.h"
#include "Renderer.h"

// ---------------------------------------------------------------------------------

Animation::Animation(TileSet * tiles, float delay, bool repeat) : 
    tileSet(tiles), 
    animDelay(delay), 
    animLoop(repeat)
{
    // sempre inicia a anima��o pelo primeiro quadro
    frame = iniFrame = 0;

    // o �ltimo quadro � sempre um a menos que o n�mero de quadros
    endFrame = tileSet->Size() - 1;

    // configura sprite
    sprite.scale     = 1.0f;
    sprite.rotation  = 0.0f;
    sprite.width     = tileSet->TileWidth();
    sprite.height    = tileSet->TileHeight();
    sprite.texSize.x = float(tileSet->TileWidth())  / tileSet->Width();
    sprite.texSize.y = float(tileSet->TileHeight()) / tileSet->Height();
    sprite.texture   = tileSet->View();
    
    // anima��o iniciada (come�a a contar o tempo)
    timer.Start();                

    // nenhuma sequ�ncia selecionada
    sequence = nullptr;
}

// --------------------------------------------------------------------------------

Animation::~Animation()
{
    if (!table.empty())
    {
        // liberando mem�ria dos vetores din�micos de sequ�ncias
        for (const auto & [id,seq] : table)
            delete seq.first;
    }
}

// --------------------------------------------------------------------------------

void Animation::Add(uint id, uint * seq, uint seqSize)
{
    // cria nova sequ�ncia de anima��o
    AnimSeq newSeq(new uint[seqSize], seqSize);

    // copia vetor com a sequ�ncia de quadros
    memcpy(newSeq.first, seq, sizeof(uint) * seqSize);

    // insere nova sequ�ncia
    table[id] = newSeq;

    // seleciona sequ�ncia rec�m inserida
    sequence = newSeq.first;

    // inicia anima��o pelo primeiro quadro da sequ�ncia
    iniFrame = frame = 0;

    // o �ltimo quadro � sempre um a menos que o n�mero de quadros
    endFrame = seqSize - 1;
}

// --------------------------------------------------------------------------------

void Animation::Select(uint id)
{
    const auto & [seq, size] = table[id];

    // se uma nova sequ�ncia for selecionada
    if (sequence != seq)
    {
        // aponta para nova sequ�ncia
        sequence = seq;

        // reinicia a sequ�ncia
        iniFrame = 0;
        endFrame = size - 1;

        // se o frame atual est� fora da sequ�ncia
        if (frame > endFrame)
            frame = 0;
    }
}


// ---------------------------------------------------------------------------------

void Animation::NextFrame()
{
    // passa para o pr�ximo quadro ap�s espa�o de tempo estipulado em animDelay
    if (timer.Elapsed(animDelay))
    {
        frame++;

        // se chegou ao fim da anima��o
        if (frame > endFrame)
        {
            // se a anima��o estiver em loop
            if (animLoop)
            {
                // volta ao primeiro quadro 
                frame = 0;
                timer.Start();
            }
            else
            {
                // fica no �ltimo quadro
                frame = endFrame;
            }
        }
        else
        {
            // come�a a contar o tempo do novo frame
            timer.Start();
        }
    }
}

// ---------------------------------------------------------------------------------

void Animation::Draw(uint aFrame, float x, float y, float z, Color color)
{
    // configura dados b�sicos
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;
    sprite.color = color;

    // configura coordenadas da textura do sprite
    sprite.texCoord.x = (aFrame % tileSet->Columns()) * sprite.texSize.x;
    sprite.texCoord.y = (aFrame / tileSet->Columns()) * sprite.texSize.y;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}

// --------------------------------------------------------------------------------