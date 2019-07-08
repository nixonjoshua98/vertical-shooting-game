#pragma once

#include <memory>
#include <vector>

#include "JN_SDLRenderer.h"

class JN_Game
{
public:
	JN_Game(std::shared_ptr<JN_SDLRenderer>);
	~JN_Game();

	void Run();

private:
	std::shared_ptr<JN_SDLRenderer> renderer;

	std::string turretInput[4];

	float projectileY[4];
	bool projectileActive[4];

	float enemyY[4];
	float enemyActive[4];

	std::vector<int> frameInput;

	bool gameRunning = true;

	int currentFPS = 0;
	int playerScore = 0;
	int playerPeakScore = 0;

	float deltaTime = 0.0f;
	float enemySpawnTimer = 0.0f;

	void Input();
	void Update();
	void Render();
};