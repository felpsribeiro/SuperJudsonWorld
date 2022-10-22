#include "Hud.h"
#include "SuperJudsonWorld.h"

Hud::Hud()
{
	fonte = new Font("Resources/Agency30.png");
	fonte->Spacing("Resources/Agency30.dat");

	time = 100;

	timer.Start();
	float delta = 24.0f;
	float init = -24.0f;
	for (int i = 0; i < 5; i++) {
		heart[i] = new Heart(window->CenterX() + init , 47);
		init += delta;
	}

}

Hud::~Hud()
{
	delete fonte;
	for(int i = 0; i < 5; i++)
		delete heart[i];
}

void Hud::Update()
{
	if (!stopped && timer.Elapsed() > 1.0f) {
		time--;
		timer.Reset();

		if (time < 0)
			time = 0;
	}	

}

void Hud::Draw() {

	text.str("");
	text << "Tempo";
	fonte->Draw(window->Width() - 48.0f, 30.0f, text.str());

	text.str("");
	text.width(3);
	text.fill('0');
	text << time;
	fonte->Draw(window->Width() - 35.0f, 60.0f, text.str());

	for (int i = 0; i < SuperJudsonWorld::player->vida; i++)
		heart[i]->Draw();

	text.str("");
	text << "Pontuação";
	fonte->Draw(40.0f, 30.0f, text.str());

	text.str("");
	text.width(4);
	text.fill('0');
	text << SuperJudsonWorld::pontos;
	fonte->Draw(60.0f, 60.0f, text.str());
}

void Hud::ResetTime()
{
	stopped = false;
	timer.Start();
	time = 100;
}

uint Hud::Time(){
	return time;
}