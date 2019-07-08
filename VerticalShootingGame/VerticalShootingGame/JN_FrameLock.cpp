
#include "JN_FrameLock.h"

// SDL_Delay(ms)
#include <SDL.h>

// Sleep(ms)
//#include "windows.h"

#include <iostream>


JN_FrameLock::JN_FrameLock(int fps, int& _rFps): rFps(_rFps)
{
	start = std::chrono::system_clock::now();

	// Requested delta time
	wantedDeltaTime = 1000 / fps;

	actualDeltaTime = -1;
}

JN_FrameLock::~JN_FrameLock()
{
	actualDeltaTime = CalculateDeltaTime();

	WaitForMs((int)std::fmax(wantedDeltaTime - actualDeltaTime, 0));

	actualDeltaTime = CalculateDeltaTime();

	if (actualDeltaTime > 0)
	{
		rFps = 1000 / actualDeltaTime;
	}
}

int JN_FrameLock::CalculateDeltaTime()
{
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<float, std::milli> span = end - start;

	return (int)span.count();
}


void JN_FrameLock::WaitForMs(int ms)
{
	SDL_Delay(ms);
}