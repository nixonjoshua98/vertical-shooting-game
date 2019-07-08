#include <iostream>

#include "JN_Game.h"
#include "JN_FrameLock.h"



JN_Game::JN_Game(std::shared_ptr<JN_SDLRenderer> renderer)
{
	this->renderer = renderer;
	
	turretInput[0] = 'W';
	turretInput[1] = 'A';
	turretInput[2] = 'S';
	turretInput[3] = 'D';

	for (int i = 0; i < 4; i++)
	{
		projectileY[i] = -1;
		enemyY[i] = -1;

		projectileActive[i] = false;
		enemyActive[i] = false;
	}
}


JN_Game::~JN_Game()
{

}


void JN_Game::Run()
{
	while (gameRunning)
	{
		{
			JN_FrameLock lock = JN_FrameLock(60, currentFPS);

			Input();

			Update();

			Render();
		}

		deltaTime = 1.0f / currentFPS;
	}
}


void JN_Game::Input()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;

		case SDL_KEYDOWN:
			frameInput.push_back(e.key.keysym.scancode);
			break;
		}
	}
}


void JN_Game::Update()
{
	enemySpawnTimer -= deltaTime;

	// Enemy Spawn
	if (enemySpawnTimer <= 0.0f)
	{
		// Get available spots for spawning (This could have been an example of the lotto problem)
		std::vector<int> availableSpots;
		for (int i = 0; i < 4; i++) { if (!enemyActive[i]) availableSpots.push_back(i); }

		if (availableSpots.size() > 0)
		{
			enemySpawnTimer = 1.25f - (0.025f * (playerScore / 5));

			std::cout << enemySpawnTimer << std::endl;

			int enemySlot = availableSpots[rand() % availableSpots.size()];

			enemyActive[enemySlot] = true;
			enemyY[enemySlot] = -1;
		}
	}

	// Projectile + Enemy Collision
	for (int i = 0; i < 4; i++)
	{
		if (enemyActive[i] && projectileActive[i])
		{
			if (abs(enemyY[i] - projectileY[i]) <= 5.0f)
			{
				enemyActive[i] = false;
				projectileActive[i] = false;

				playerScore++;
			}
		}
	}

	playerPeakScore = std::fmax(playerScore, playerPeakScore);

	// Projectile + Enemy movement
	for (int i = 0; i < 4; i++)
	{
		if (projectileActive[i])
		{
			if (projectileY[i] <= -5)
				projectileActive[i] = false;
			else
				projectileY[i] -= 150 * deltaTime;
		}

		if (enemyActive[i])
		{
			// Hit the player
			if (enemyY[i] >= 140)
			{
				enemyActive[i] = false;
				playerScore = playerScore - 10 > 0 ? playerScore - 10 : 0;
			}
			else
				enemyY[i] += 50 * deltaTime;
		}

	}

	// Input
	for (int n : frameInput)
	{
		// A - Z on keyboard
		if (n >= 4 && n <= 29)
		{
			std::string keyStr = std::string(1, (char)(n + 61));

			for (int i = 0; i < 4; i++)
			{
				if (turretInput[i] == keyStr)
				{
					if (!projectileActive[i])
					{
						turretInput[i] = std::string(1, (char)(65 + (rand() % 26)));
						projectileY[i] = 150;
						projectileActive[i] = true;
					}
				}
			}
		}
	}

	frameInput.clear();
}


void JN_Game::Render()
{
	renderer->Start();

	renderer->DrawLine(50, 150, 200, 150, { 255, 0, 0 });

	renderer->DrawText(35, 15, 50, 25, 64, { 255, 255, 255 }, "SCORE " + std::to_string(playerScore));
	renderer->DrawText(200, 15, 65, 25, 64, { 255, 255, 255 }, "HI SCORE " + std::to_string(playerPeakScore));

	// Draw turrets and letter trigger
	for (int i = 0; i < 4; i++)
	{
		renderer->DrawTriangle(50 + (i * 50), 200, 20, { 0, 255, 0 });
		renderer->DrawText(50 + (i * 50), 225, 20, 20, 64, { 255, 255, 255 }, turretInput[i]);

		if (projectileActive[i])
			renderer->DrawTriangle(50 + (i * 50), projectileY[i], 5, { 0, 0, 255 });

		if (enemyActive[i])
			renderer->DrawReverseTriangle(50 + (i * 50), enemyY[i], 10, { 255, 0, 0 });
	}

	renderer->End();
}
