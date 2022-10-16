#ifndef _ELEMENT_H_
#define _ELEMENT_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos espec?ficos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------

class Element : public Object
{
private:
    Sprite* platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    Element(float posX, float posY,
        uint platType,
        Color tint);                   // construtor    
    ~Element();                            // destrutor

    void Update();                          // atualiza??o do objeto
    void Draw();                            // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun??o Membro Inline

inline void Element::Draw()
{
    platform->Draw(x, y, z, 1.0f, 0.0f, color);
}

// ---------------------------------------------------------------------------------

#endif
