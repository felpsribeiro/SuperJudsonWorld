#ifndef _PLATFORM_H_
#define _PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos espec�ficos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

// ---------------------------------------------------------------------------------

enum PLATTYPES { RED, GRAY };

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    Platform(float posX, float posY, 
             uint platType, 
             Color tint);                   // construtor    
    ~Platform();                            // destrutor

    void Update();                          // atualiza��o do objeto
    void Draw();                            // desenho do objeto
    float Width();
    float Height();
}; 

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Platform::Draw()
{ platform->Draw(x, y, z, 0.25f, 0.0f, color); }

inline float Platform::Width() {
   return platform->Width();
}

inline float Platform::Height() {
   return platform->Height();
}

// ---------------------------------------------------------------------------------

#endif