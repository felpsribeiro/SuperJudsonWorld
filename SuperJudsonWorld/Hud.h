#ifndef _HUD_H_
#define _HUD_H_

#include "Font.h"
#include "Object.h"
#include "Timer.h"
#include "Heart.h"
#include <sstream>

using std::stringstream;

class Hud : public Object
{
private:
    Font    * fonte;
    Timer     timer;
    Heart * heart[5];
    stringstream text;

    uint time;
    bool stopped;

public:
    Hud();
    ~Hud();

    void Update();
    void Draw();

    void Stop() { stopped = true; };
    void ResetTime();
    uint Time();
};

#endif
