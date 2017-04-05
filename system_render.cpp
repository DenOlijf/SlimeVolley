#include "system_render.h"

#include <chrono>
#include <iostream>
#include <set>
#include <thread>
#include <vector>

#include "color.h"
#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"
#include "tags.h"

void SystemRender::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Clear screen and draw background
	Graphics::Instance().ClearScreen();
	Graphics::Instance().DrawBackground();

	// TODO: Iterate over all entities with the sprite component and print to
	// screen. For player slimes, draw the pupils as well.

	Color c(0, 0, 0);

	// TODO: Use an appropriate color for the different backgrounds
	/*if (engine->GetContext()->GetLevel() == ...)
	{
		c = Color(..., ..., ...);
	}*/

	// TODO: Print the current score if it is a singleplayer game

	// TODO: Print the correct instructions at the bottom of the screen,
	// depending on whether there's a regular game or a replay

	int state = engine->GetContext()->GetState();

	// TODO: Print an appropriate message if state != 0, depending on state
	// and current level (1-3 for singleplayer, 0 for multiplayer)

	// Update current frame rate
	fps_accum++;
	t = al_get_time();
	if (t - fps_time >= 1)
	{
		fps = fps_accum;
		fps_accum = 0;
		fps_time = t;
	}
	Graphics::Instance().DrawString(std::to_string(fps), 375, 40, c, Graphics::ALIGN_CENTER);

	// Execute all draws
	Graphics::Instance().ExecuteDraws();
}

bool SystemRender::Initialize()
{
	int level = engine->GetContext()->GetLevel();

	// TODO: Set background according to level

	return true;
}
