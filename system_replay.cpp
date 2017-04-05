#define NOMINMAX

#include "system_replay.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>

#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

void SystemReplay::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: According to toggled keys in context, either:
	//   [ARROW_LEFT] Decrease playout speed by factor 2
	//	 [ARROW_RIGHT] Increase playout speed by factor 2
	//   [ARROW_UP] Go to next point
	//	 [ARROW_DOWN] Go to next level
	//	 [P] Pause playout
	//	 [ESC] Return to menu

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// TODO: Go to the next frame(s), if necessary
	}
}

void SystemReplay::GoToNextFrame()
{
	// TODO: Go to next frame by setting the new coordinates. Set state to:
	//   0 if a normal frame has been found
	//   1 if a frame has been found in which the ball has dropped
	//   2 if there are no coordinates left
	// and update the context whenever necessary

}

void SystemReplay::GoToNextPoint()
{
	while (status < 1)
	{
		GoToNextFrame();
	}
}

void SystemReplay::GoToNextLevel()
{
	while (status < 2)
	{
		GoToNextFrame();
	}
}

bool SystemReplay::Initialize()
{
	// TODO: Read input coordinates from file and push to list

	// TODO: Initialize all component pointers (optional)

	return true;
}
