#include "Hud.h"
#include "SuperJudsonWorld.h"

Hud::Hud() {
	fonte = new Font("Resources/Agency30.png");
	fonte->Spacing("Resources/Agency30.dat");

	time = 100;

	timer.Start();
}

Hud::~Hud() {
	delete fonte;
}

void Hud::Update() {
	if (timer.Elapsed() > 1.0f) {
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

	text.str("");
	text << "Pontuação";
	fonte->Draw(40.0f, 30.0f, text.str());

	text.str("");
	text.width(4);
	text.fill('0');
	text << SuperJudsonWorld::pontos;
	fonte->Draw(60.0f, 60.0f, text.str());
}

void Hud::ResetTime() {
	time = 100;
}

uint Hud::Time() {
	return time;
}