#include "system_state_single.h"

#include <set>

#include "component.h"
#include "component_player.h"
#include "component_motion.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

void SystemStateSingle::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// Is the level in freeze state?
		if (freeze_time == 0)
		{
			// TODO: Check if the ball has dropped. If so, freeze the game for
			// 1.2 seconds and reset all velocities. Determine the winner and
			// update the context accordingly.

		}
		else
		{
			// TODO: Decrease freeze time by one. If it becomes zero and one
			// of the players scored seven points, update the context as to
			// end the level gracefully. Wait for user input: spacebar to
			// continue to next level (if won) or retry (if lost), ESC to quit
			// (handled by input system already). If the game is not finished
			// yet, update the context and reset player and ball positions.

		}
	}
}

bool SystemStateSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
