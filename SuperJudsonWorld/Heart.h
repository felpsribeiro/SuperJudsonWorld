#ifndef _HEART_H_
#define _HEART_H_

#include "Object.h"
#include "Sprite.h"

class Heart : public Object
{
private:
	Sprite * heart = nullptr;
public:
	Heart(float posX, float posY);
	~Heart();

	void Update();
	void Draw();
};

inline void Heart::Draw() { heart->Draw(x, y); }

#endif
